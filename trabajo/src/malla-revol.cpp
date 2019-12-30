// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"
#include "math.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.

//Normales giran en sentido horario
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
  unsigned int num_vertices = perfil.size();
  unsigned int copias_m_1 = num_copias - 1;
  unsigned int vertices_m_1 = num_vertices - 1; 
  
  
  // NORMALES
  // calculamos normales normalizadas aristas
  vector<Tupla3f> normales_vertices;
  vector<Tupla2f> norm_norm_arst; //normal normalizada
  Tupla2f normal(0,0);
  float x, y, x_aux;
  for (int i = 0; i < vertices_m_1; i++){
		// calculamos arista (vector) de v_i a v_(i+1) || v_(i+1) - v_i
		x = perfil[i+1](0) - perfil[i](0);
	  y = perfil[i+1](1) - perfil[i](1);
	  // normalizamos
	  x_aux = x;
	  x = x / sqrt(x*x + y*y);
	  y = y / sqrt(x_aux*x_aux + y*y);
	  // rotamos 90grados en sentido horario en la tupla2f normal
	  normal(0) = y;
	  normal(1) = -x;
	  norm_norm_arst.push_back(normal);
  }
  // calculamos normales de los vértices
  // caso v0
  Tupla3f normal_vertice(norm_norm_arst[0](0),norm_norm_arst[0](1),0);
  normales_vertices.push_back(normal_vertice);
  
  for (int i = 1; i < vertices_m_1; i++){
		// m_(i-1) + m_i
		normal_vertice(0) = norm_norm_arst[i-1](0) + norm_norm_arst[i](0);
		normal_vertice(1) = norm_norm_arst[i-1](1) + norm_norm_arst[i](1);
		normales_vertices.push_back(normal_vertice);
	}
	// caso último vértice
	normal_vertice(0) = norm_norm_arst[vertices_m_1 - 1](0);
	normal_vertice(1) = norm_norm_arst[vertices_m_1 - 1](1);
	normales_vertices.push_back(normal_vertice);
  
  // TEXTURA
  float d[vertices_m_1];
  for (int i = 0; i < vertices_m_1; i++){
		d[i] = sqrt( pow(perfil[i+1](0) - perfil[i](0), 2) + pow(perfil[i+1](1) - perfil[i](1), 2) );
	}
	
	float t[num_vertices];
	float suma_1;
	float suma_2;
	for (int i = 0; i < num_vertices; i++){
		suma_1 = 0.0;
		suma_2 = 0.0;
		for (int j = 0; j < i; j++){
			suma_1 += d[j];
		}
		for (int k = 0; k < vertices_m_1; k++){
			suma_2 += d[k];
		}
		t[i] = suma_1 / suma_2;
	}
	//cout << "t_(n-1) = 1 ?" << t[vertices_m_1] << endl;
	
  // Generación vértices con copias
  double  angulo_rot;
  Tupla3f q; // vértice
  Tupla3f n; // normal
  Tupla2f tex; // textura

  for (int i = 0; i < num_copias; i++){
    angulo_rot = (2*PI*i)/copias_m_1;
    for (int j = 0; j < num_vertices; j++){
      q(0) = perfil[j](0) * cos(angulo_rot) /*+ perfil[j](2) * sin(angulo_rot)*/;
      q(1) = perfil[j](1);
      q(2) = -perfil[j](0) * sin(angulo_rot) /*+ perfil[j](2) * cos(angulo_rot)*/;
      
      vertices.push_back(q);
      
      // añadimos correspondiente normal
      n(0) = normales_vertices[j](0) * cos(angulo_rot);
      n(1) = normales_vertices[j](1);
      n(2) = -normales_vertices[j](0) * sin(angulo_rot);
      nor_ver.push_back(n);
      
      // añadimos coordenadas de textura correspondientes
      tex(0) = (float) i / (num_copias - 1.0);
      tex(1) = 1.0 - t[j];
      cc_tt_ver.push_back(tex);

    }
  }
	// Triángulos
  int k;
  Tupla3i p;

  for (int i = 0; i < copias_m_1; i++){
    for (int j = 0; j < vertices_m_1; j++){
      k = i * num_vertices + j;
      p(0) = k; p(1) = k + num_vertices; p(2) = k + num_vertices + 1;
      triangulos.push_back(p);
      p(0) = k; p(1) = k + num_vertices + 1; p(2) = k + 1;
      triangulos.push_back(p);
    }
  }
  

	
}

//Método inicializar para mallas que el perfil se cierra 
//Normales gira en sentido horario. Generación de texturas no implementada (completar)
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias,  // número de copias del perfil
   const double ang_rev,
   const bool cerrar_obj,
   const bool normales
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
  unsigned int num_vertices = perfil.size();
  unsigned int copias_m_1 = num_copias - 1;
  unsigned int vertices_m_1 = num_vertices - 1;
  

		// NORMALES
		// calculamos normales normalizadas aristas
		vector<Tupla3f> normales_vertices;
	if (normales){
		vector<Tupla2f> norm_norm_arst; //normal normalizada
		Tupla2f normal(0,0);
		float x, y, x_aux;
		for (int i = 0; i < num_vertices; i++){
			// calculamos arista (vector) de v_i a v_(i+1) || v_(i+1) - v_i
			x = perfil[(i+1)%num_vertices](0) - perfil[i](0);
			y = perfil[(i+1)%num_vertices](1) - perfil[i](1);
			// normalizamos
			x_aux = x;
			x = x / sqrt(x*x + y*y);
			y = y / sqrt(x_aux*x_aux + y*y);
			// rotamos 90grados en sentido anti-horario en la tupla2f normal
			normal(0) = y;
			normal(1) = -x;
			norm_norm_arst.push_back(normal);
		}
		// calculamos normales de los vértices
		// caso v0

		Tupla3f normal_vertice(0,0,0);
		normal_vertice(0) = norm_norm_arst[vertices_m_1](0) + norm_norm_arst[0](0);
		normal_vertice(1) = norm_norm_arst[vertices_m_1](1) + norm_norm_arst[0](1);
		normales_vertices.push_back(normal_vertice);
		
		for (int i = 1; i <= vertices_m_1; i++){
			// m_(i-1) + m_i
			normal_vertice(0) = norm_norm_arst[i-1](0) + norm_norm_arst[i](0);
			normal_vertice(1) = norm_norm_arst[i-1](1) + norm_norm_arst[i](1);
			normales_vertices.push_back(normal_vertice);
		}
		// caso último vértice
		/*normal_vertice(0) = norm_norm_arst[vertices_m_1 - 1](0);
		normal_vertice(1) = norm_norm_arst[vertices_m_1 - 1](1);
		normales_vertices.push_back(normal_vertice);*/
	}

  
  //AÑADIMOS
  double  angulo_rot;
  Tupla3f q; // vértice
  Tupla3f n; // normal
  Tupla2f tex; // textura

  for (int i = 0; i < num_copias; i++){
    angulo_rot = (ang_rev*i)/copias_m_1;
    for (int j = 0; j < num_vertices; j++){
      q(0) = perfil[j](0) * cos(angulo_rot) /*+ perfil[j](2) * sin(angulo_rot)*/;
      q(1) = perfil[j](1);
      q(2) = -perfil[j](0) * sin(angulo_rot) /*+ perfil[j](2) * cos(angulo_rot)*/;
      
      vertices.push_back(q);
      // añadimos correspondiente normal
      if (normales) {
				n(0) = normales_vertices[j](0) * cos(angulo_rot);
				n(1) = normales_vertices[j](1);
				n(2) = -normales_vertices[j](0) * sin(angulo_rot);
				nor_ver.push_back(n);
			}
    }
  }

  int k;
  Tupla3i p;
  
  // si hay que cerrar los vértices del objeto a revolucionar:
  if (cerrar_obj){
		// hacemos que el último vértice se conecte con la siguiente cara
		vertices_m_1 += 1;
		// i=0  cerramos la cara en caso j == vertices_m_1 - 1

		// i=0 hasta i=copias_m_1 - 1
		for (int i = 0; i < copias_m_1; i++){
			for (int j = 0; j < vertices_m_1; j++){
				k = i * num_vertices + j;
				p(0) = k; p(1) = k + num_vertices; p(2) = k + num_vertices + 1;
				if (j == vertices_m_1 - 1)
					p(2) -= num_vertices;
				triangulos.push_back(p);
				p(0) = k; p(1) = k + num_vertices + 1; p(2) = k + 1;
				if (j == vertices_m_1 - 1){
					p(2) -= num_vertices;
					p(1) -= num_vertices;
				}
				triangulos.push_back(p);
			}
		}
  }
  else{
    for (int i = 0; i < copias_m_1; i++){
      for (int j = 0; j < vertices_m_1; j++){
        k = i * num_vertices + j;
        p(0) = k; p(1) = k + num_vertices; p(2) = k + num_vertices + 1;
        triangulos.push_back(p);
        p(0) = k; p(1) = k + num_vertices + 1; p(2) = k + 1;
        triangulos.push_back(p);
      }
    }
  }
}

Cilindro::Cilindro (const int num_verts_per, const unsigned nperfiles, const bool poner_tapa){
  ponerNombre("Malla de revolución: Cilindro");
  
  int num_verts_per_1 = num_verts_per - 1;
  vector<Tupla3f> vertices;
  
  Tupla3f t(1.0, 0.0, 0.0);
  if (poner_tapa){
	  t(0) = 0.0; t(1) = -0.5; t(2) = 0.0; vertices.push_back(t);
  }
  t(0) = 1.0; t(1) = 0.0; t(2) = 0.0;
  for (int i = 0; i < num_verts_per; i++){
    t(1) = ((float) i)/num_verts_per_1 - 0.5;
    vertices.push_back(t);
  }
  if (poner_tapa){
    t(0) = 0.0; t(1) = 0.5; t(2) = 0.0; vertices.push_back(t);
  }

  inicializar(vertices, nperfiles);
  
}

  
Cono::Cono(const int num_verts_per, const unsigned nperfiles){
  ponerNombre("Malla de revolución: Cono");
  
  int num_verts_per_1 = num_verts_per - 1;
  vector<Tupla3f> vertices;
  Tupla3f t(0.0, 0.0, 0.0);

  for (int i = num_verts_per_1; i >= 0; i--){
    t(0) = ((float) i)/num_verts_per_1;
    t(1) = -t(0) + 1;
    vertices.push_back(t);
  }

  inicializar(vertices, nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles){
  ponerNombre("Malla de revolución: Esfera");
  
  int num_verts_per_1 = num_verts_per - 1;
  vector<Tupla3f> vertices;
  Tupla3f t(0.0, 0.0, 0.0);

  for (int i = 0; i < num_verts_per; i++){
    t(0) = cos( ( i * PI) / num_verts_per_1 - PI / 2 );
    t(1) = sin( ( i * PI) / num_verts_per_1 - PI / 2 );
    vertices.push_back(t);
  }

  inicializar(vertices, nperfiles);
}

ArcoRect::ArcoRect(const unsigned nperfiles){
  ponerNombre("Malla de revolución: Arco Rectangular");
  
  vector<Tupla3f> vertices;
  Tupla3f t(0.0, 0.0, 0.0);
  /*
  for (int i = 0; i < num_verts_per; i++){
    t(0) = 1.75 + ( cos( ( i * 2*PI) / num_verts_per_1 - PI / 2 ))*0.1;
    t(1) = sin( ( i * 2*PI) / num_verts_per_1 - PI / 2 )*0.1;
    vertices.push_back(t);
    }*/
  t(0) = 1.75 + 0.1; t(1) =  0.1; vertices.push_back(t);
  t(0) = 1.75 - 0.1; t(1) =  0.1; vertices.push_back(t); 
  t(0) = 1.75 - 0.1; t(1) =  -0.1; vertices.push_back(t);
  t(0) = 1.75 + 0.1; t(1) =  -0.1; vertices.push_back(t);

  inicializar(vertices, nperfiles, PI, true, true);

}

EngancheArco::EngancheArco(){
  ponerNombre("Malla de revolución: Enganche de arco en C");

  vector<Tupla3f> vertices;
  Tupla3f t(0.0, 0.0, 0.0);

  
  t(0)=1.85; t(1)= -0.16; vertices.push_back(t);
  t(0)=1.85; t(1)= 0.16; vertices.push_back(t);
   
  inicializar(vertices, 10, PI/8.0, false, false);

  t(0)=1.85+0.24; t(1)=-0.16; this->vertices.push_back(t); // 20
  t(0)=1.85+0.24; t(1)=0.16; this->vertices.push_back(t); // 21
  
  t(0)=1.85+0.24; t(1)=-0.16; t(2)=-0.26; this->vertices.push_back(t); // 22
  t(0)=1.85+0.24; t(1)=0.16; t(2)=-0.26; this->vertices.push_back(t); // 23

  Tupla3i tr(0,20,1);  triangulos.push_back(tr);
  tr(0) = 20; tr(1) = 1; tr(2) = 21; triangulos.push_back(tr);
  tr(0) = 22; tr(1) = 20; tr(2) = 23; triangulos.push_back(tr);
  tr(0) = 20; tr(1) = 21; tr(2) = 23; triangulos.push_back(tr);
  tr(0) = 22; tr(1) = 18; tr(2) = 19; triangulos.push_back(tr);
  tr(0) = 23; tr(1) = 22; tr(2) = 19; triangulos.push_back(tr);

  for (int i = 2; i < 20; i += 2){
    tr(0) = 20; tr(1) = i-2; tr(2) = i; triangulos.push_back(tr);
  }
  tr(0) = 22; tr(1) = 20; tr(2) = 18; triangulos.push_back(tr);
  
  for (int i = 3; i < 21; i += 2){
    tr(0) = 21; tr(1) = i; tr(2) = i-2; triangulos.push_back(tr);
  }
  tr(0) = 23; tr(1) = 19; tr(2) = 21; triangulos.push_back(tr);
  
	calcularNormales();
}

Toro::Toro(const int num_verts_per, const unsigned nperfiles){
	ponerNombre("Malla de revolución: Toro");
	
	vector<Tupla3f> vertices;
	Tupla3f t(0.0, 0.0, 0.0);
	int num_verts_per_1 = num_verts_per - 1;
	
	//t(0) = 0.0; t(1) = -1.0; vertices.push_back(t); 
	
	for (int i = 0; i < num_verts_per; i++){
	  t(0) = 2+cos( ( i * 2*PI) / num_verts_per_1 );
	  t(1) = sin( ( i * 2*PI) / num_verts_per_1 );
	  vertices.push_back(t);
	}
	
	//t(0) = 0.0; t(1) = 1.0; t(2)= 0.0; vertices.push_back(t); 
	
	inicializar(vertices, nperfiles);
}



// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> vertices;
   
   LeerVerticesPLY(nombre_arch, vertices);

   inicializar(vertices, nperfiles);
}


