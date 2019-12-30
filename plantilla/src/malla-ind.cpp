// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


//----------------------------------------------------------------------------
// comprueba que los valores de 'tipo' y 'tabla' son valores legales.

void Comprobar( GLuint tipo, GLuint tabla )
{
   assert( tipo == GL_ARRAY_BUFFER || tipo == GL_ELEMENT_ARRAY_BUFFER );
   if ( tipo == GL_ARRAY_BUFFER )
      assert(  tabla == GL_VERTEX_ARRAY || tabla == GL_COLOR_ARRAY ||
               tabla == GL_NORMAL_ARRAY || tabla == GL_TEXTURE_COORD_ARRAY ) ;
}
//----------------------------------------------------------------------------
// crea un VBO, devuelve:
//  ** 0 si 'num_elems' es 0, o
//  ** el identificador de VBO, si num_elems > 0
//
// deja activado el VBO 0

GLuint CrearVBO( GLuint tipo, GLuint tabla, GLuint cuenta, GLvoid * puntero )
{
   Comprobar( tipo, tabla );
   // COMPLETAR: práctica 1
   // Crear un VBO para esta tabla y enviar datos a la GPU, devolver id de VBO
   // Si 'cuenta' es 0, la tabla está vacía: devuelve 0 y no hace nada.
   // ...
   return 0 ; // sustituir por lo que corresponda ...

}

//----------------------------------------------------------------------------
// Especifica localización y estructura de una tabla

void LocForTabla( GLuint tipo_tabla, GLuint tabla, GLuint id_vbo,
                  GLvoid * p )
{
   // COMPLETAR: práctica 1
   // especificar localización y formato de la tabla
   // ...

}


//----------------------------------------------------------------------------
// habilita o deshabilita una tabla, si la habilita, especifica localización
// y estructura

void RegistrarTabla( GLuint tipo_tabla, GLuint tabla, GLsizei cuenta,
                     GLuint id_vbo, GLvoid * puntero_offset )
{
   // COMPLETAR: Práctica 1: implementar según el comportamiento descrito arriba:
   // usar 'glBindBuffer', 'glEnableClientState', 'glDisableClientState' y 'FijarPunteroTabla'
   // (al llamar a 'FijarPunteroTabla', se asume que el puntero es el offset nulo)
   // ....

}
// -----------------------------------------------------------------------------
// crea todos los VBOs

void MallaInd::crearVBOs()
{
   if ( vbos_creados )
      return ;

   CError();
   // COMPLETAR: práctica 1
   // Crear los VBOs de las 5 tablas posibles (llamar a 'CrearVBO')
   // almacenar los identificadores en las variables de instancia 'id_vbo_...'
   // .....

   CError();

   vbos_creados = true ;
}

// -----------------------------------------------------------------------------
// Registrar tablas en modo inmediato

void MallaInd::registrarTablas_MI()
{
   CError();
   // COMPLETAR: práctica 1
   // registrar las 4 tablas en modo inmediato (llamar a 'RegistrarTabla')
   // .....

   CError();
}

//--------------------------------------------------------------------------------
// Registrar tablas en modo diferido

void MallaInd::registrarTablas_MD()
{
   CError();
   // COMPLETAR: práctica 1
   // crear VBOs y registrar las 5 tablas en modo diferido (llamar a 'RegistrarTabla')
   // .....

   CError();
}



// -----------------------------------------------------------------------------
// crear (si no estaba creado) y activar el VAO para el MI

void MallaInd::crearActivarVAO_MI()
{
   CError();
   // COMPLETAR: práctica 1
   // Crear (si no lo estaba) el VAO del M.I., y activarlo.
   // .....

   CError();
}

// -----------------------------------------------------------------------------
// crear los dos VAOS: 'id_vao_attr' e 'id_vao_geom' , solo si no estaban creados

void MallaInd::crearActivarVAO_MD( )
{
   CError();
   // COMPLETAR: práctica 1
   // Crear (si no lo estaba) el VAO del M.D., y activarlo.
   // .....

   CError();
}



// -----------------------------------------------------------------------------

void MallaInd::visualizarGL_MI_VAO( ContextoVis & cv )
{
   CError();
   using namespace std ;

   // COMPLETAR: Práctica 1: visualizar en modo inmediato (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.I. está creado
   // (usando crearActivarVAO_MI), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto
   // ....

   CError();

}
// ----------------------------------------------------------------------------

void MallaInd::visualizarGL_MD_VAO( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1: visualizar en modo diferido (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.D. está creado
   // (usando crearActivarVAO_MD), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto

}

// -----------------------------------------------------------------------------
// visualizar con begin/end (modo inmediato), enviando normales de triángulos y
// cc.tt. (adecuado para modo de sombreado plano)

void MallaInd::visualizarGL_MI_BE( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1:
   // Visualizacion en modo inmediato usando begin/end
   // usar 'glBegin/glVertex/glEnd'
   // ..........

}
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end                   : usar 'visualizarGL_MI_BE'
   //   ** inmediato con un VAO (glDrawElements) : usar 'visualizarGL_MI_VAO'
   //   ** diferido con un VAO  (glDrawElements) : usar 'visualizarGL_MD_VAO'
   // .....


   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}



// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // llamar a 'calcularNormales' para el cálculo de normales
   // ..........................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}
// -----------------------------------------------------------------------------------------------

