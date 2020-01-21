#include "modelo-jer.h"

  Material* meta = new Material(0.5, 0.2, 1, 20);
  Material* mate = new Material(0.5, 1, 0, 0);
  
C::C(const float ang_rot_inicial_cil1, const float ang_rot_inicial_cil2, const float tras_sup_inicial, const float tras_hor_inicial, const float rot_arco_inicial){
  ponerNombre("Arco en C - equipo rayos X");
  ponerIdentificador(-1); // por defecto ya -1
  // Comprobaciones de parámetros iniciales
  assert(-30<=ang_rot_inicial_cil1 && ang_rot_inicial_cil1<=30);
  assert(-90<=ang_rot_inicial_cil2 && ang_rot_inicial_cil2<=90);
  assert(0<=tras_sup_inicial && tras_sup_inicial<=0.5*2);
  assert(0<=tras_hor_inicial && tras_hor_inicial<=0.5*2);
  assert(2<=rot_arco_inicial && rot_arco_inicial<=77.0*2);
  
  // Calculamos parámetros necesarios para los v asociados a matriz
  p_rot_arco = acos( (79.0 - rot_arco_inicial)/77.0 );
  p_tras_hor = acos( 1 - tras_hor_inicial/0.5 );
  p_tras_sup = acos( 1 - tras_sup_inicial/0.5 );
  p_ang_rot_cil2 = acos( ang_rot_inicial_cil2/(-90.0) );
  p_ang_rot_cil1 = acos( ang_rot_inicial_cil1/(-30.0) );

  // Construimos el objeto:

  // Creamos base cubica
  BaseArcoC * baseC = new BaseArcoC();
  baseC->ponerNombre("Base del Arco en C");
  baseC->ponerIdentificador(11);
  agregar(mate); // Material
  agregar( baseC );
  Tupla3f blanco (0.973, 0.957, 0.867);
  baseC->ponerColor(blanco);
  // Creamos soporte inferior de la base
  NodoGrafoEscena * base_inf = new BaseBajaArcoC();
  NodoGrafoEscena * base_inf_dcha = new BaseBajaDchaArcoC();
  NodoGrafoEscena * ruedas = new TotalRuedas();
  
  agregar(base_inf);
  agregar(base_inf_dcha);
  agregar(ruedas);

  // Creamos parte superior y añadimos primer movimiento
  NodoGrafoEscena * psup = new NodoGrafoEscena();
  agregar( MAT_Traslacion(0.5, 0.5, 0) );

  // Añadimos movimiento traslación a parte superior
  unsigned ind1 = agregar( MAT_Traslacion(0, tras_sup_inicial, 0) );
  // Añadimos movimiento rotación a parte superior
  unsigned ind2 = psup->agregar( MAT_Rotacion(ang_rot_inicial_cil1 , 0, 1, 0) );
  
  NodoGrafoEscena * cilv = new CilindroV();
  psup->agregar( cilv );

  psup->agregar( MAT_Traslacion(0.2, 0.75, 0) );

  // Creamos soporte y añadimos a parte superior
  NodoGrafoEscena * soportesup = new SoporteSuperior();
  psup->agregar( soportesup );

  // Movimiento/s que afectan al brazo - - Traslación y rotación
  unsigned ind3 = psup->agregar( MAT_Traslacion(tras_hor_inicial, 0, 0) );
  unsigned ind4 = psup->agregar( MAT_Rotacion(ang_rot_inicial_cil2, 1, 0, 0) );

  // Creamos brazo
  NodoGrafoEscena * brazo = new NodoGrafoEscena();
  brazo->agregar( MAT_Traslacion(0.15, 0, 0) );
  // añadimos cilindro al brazo
  NodoGrafoEscena * cilh = new CilindroH();
  brazo->agregar(cilh);
  brazo->agregar( MAT_Traslacion(0.5, 0, 0) );
  
  // añadimos enganche al brazo
  NodoGrafoEscena * enganche_arco = new EngArco();
  brazo->agregar(enganche_arco);

  brazo->agregar( MAT_Traslacion(0.24, 0, 0) );
  
  NodoGrafoEscena * arco = new NodoGrafoEscena();
  arco->agregar( MAT_Traslacion(1.85,-0.1,0) );
  
  NodoGrafoEscena * tambor_arco = new TamborArco();
  NodoGrafoEscena * frente_tambor = new FrenteTambor();
  ArcoR * arco_r = new ArcoR();
  // Añadimos movimiento rotación al arco
  unsigned ind5 = arco->agregar( MAT_Rotacion(rot_arco_inicial, 0, 0, 1) );
  arco->agregar(tambor_arco);
  arco->agregar(frente_tambor);
 
  arco->agregar(arco_r);
  
  brazo->agregar(arco);

  psup->agregar(brazo);
  
  // Agregamos parte superior
  agregar( psup );

  // Asignamos punteros de matrices
  pm_tras_sup = leerPtrMatriz( ind1 );
  pm_ang_rot_cil1 = psup->leerPtrMatriz( ind2 );
  pm_tras_hor = psup->leerPtrMatriz( ind3 );
  pm_ang_rot_cil2 = psup->leerPtrMatriz( ind4 );
  pm_rot_arco = arco->leerPtrMatriz( ind5 );

}

unsigned C::leerNumParametros() const{
  return num_param;
}

void C::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
  assert( iParam >= 0 && iParam < num_param );
  
  switch (iParam) {
  case 0:
    v = 0.5 * (1 - cos(2*PI*0.03*t_sec + p_tras_sup));
    *pm_tras_sup = MAT_Traslacion(0, v, 0);
    break;
  case 1:
    v = -30.0 * cos(2*PI*0.03*t_sec + p_ang_rot_cil1);
    *pm_ang_rot_cil1 = MAT_Rotacion(v, 0, 1, 0);
    break;
  case 2:
    v = 0.5 * (1 - cos(2*PI*0.03*t_sec + p_tras_hor));
    *pm_tras_hor = MAT_Traslacion(v, 0, 0);
    break;
  case 3:
    v = -90.0 * cos(2*PI*0.025*t_sec + p_ang_rot_cil2);
    *pm_ang_rot_cil2 = MAT_Rotacion(v, 1, 0, 0);
    break;
  case 4:
    v = 79.0 - 77.0*cos(2*PI*0.02*t_sec + p_rot_arco ) ;
    *pm_rot_arco = MAT_Rotacion(v, 0, 0, 1);
    break;
  default:
    break;
  }
}


CilindroV::CilindroV(){  
  agregar( MAT_Escalado(0.1, 1, 0.1) );
  Cilindro * cilindro = new Cilindro(12, 24, false);
 
  agregar(meta); //Material
  
  cilindro->ponerNombre("Cilindro Vertical");
  cilindro->ponerIdentificador(18);
  
  agregar(cilindro);
  Tupla3f gris (0.639,0.639,0.639);
  this->ponerColor(gris);
}

CilindroH::CilindroH(){  
  agregar( MAT_Rotacion(90, 0, 0, 1) );
  agregar( MAT_Escalado(0.1, 1, 0.1) );

  agregar(meta); //Material
  Cilindro * cilind = new Cilindro(12, 24, false);
  
  cilind->ponerNombre("Cilindro Horizontal");
  cilind->ponerIdentificador(20);
  
  agregar(cilind);
  Tupla3f gris (0.639,0.639,0.639);
  this->ponerColor(gris);
}

SoporteSuperior::SoporteSuperior(){  
  agregar( MAT_Escalado(0.65, 0.25, 0.25) );
  agregar(mate); //Material
  Cubo24 * cubo = new Cubo24();
  
  cubo->ponerNombre("Soporte Superior");
  cubo->ponerIdentificador(19);
  
  agregar( cubo );
  Tupla3f blanco (0.973, 0.957, 0.867);
  this->ponerColor(blanco);
}

EngArco::EngArco(){  
  agregar( MAT_Traslacion(0, -0.1, 0) );
  agregar( MAT_Rotacion(180, 0, 1, 0) );
  agregar( MAT_Rotacion(90, 1, 0, 0) );
  agregar( MAT_Traslacion(-1.85-0.24, 0, 0) );
  agregar(mate); //Material
  EngancheArco * eng = new EngancheArco();
  
  eng->ponerNombre("Enganche del Arco en C");
  eng->ponerIdentificador(21);
  
  agregar(eng);
  Tupla3f blanco (0.973, 0.957, 0.867);
  this->ponerColor(blanco);   
}

TamborArco::TamborArco(){  
  agregar( MAT_Traslacion(-0.2+1.85,-0.34,0) );
  agregar( MAT_Rotacion(-90,0,0,1) );
  agregar(mate); //Material
  MallaRevolPLY * tamb_arco = new MallaRevolPLY("./plys/TamborArco.ply", 24);
  
  tamb_arco->ponerNombre("Tambor del Arco en C");
  tamb_arco->ponerIdentificador(23);
  
  agregar(tamb_arco);
  Tupla3f blanco (0.973, 0.957, 0.867);
  this->ponerColor(blanco);
}

FrenteTambor::FrenteTambor(){
  agregar( MAT_Traslacion(-1.85,-0.44,0) );
  agregar( MAT_Escalado(0.46,0.44,0.35) );
  agregar(mate); //Material
  Cubo24 * cu_frente_tambor = new Cubo24();
  
  cu_frente_tambor->ponerNombre("Frente del Arco en C");
  cu_frente_tambor->ponerIdentificador(24);
  
  agregar(cu_frente_tambor);
  Tupla3f blanco (0.973, 0.957, 0.867);
  this->ponerColor(blanco);
}

ArcoR::ArcoR(){
  agregar( MAT_Rotacion(90,1,0,0) );
  ArcoRect * arcorect = new ArcoRect(34);
  Tupla3f gris2(0.867, 0.863, 0.855);
  agregar(meta); //Material
  arcorect->ponerColor(gris2);
  
  arcorect->ponerNombre("ArcoR");
  arcorect->ponerIdentificador(22);
  
  agregar(arcorect);
}

BaseBajaArcoC::BaseBajaArcoC(){  
  Cubo24 * cubo = new Cubo24();
  agregar(MAT_Traslacion(0,-1.1,0));
  agregar(MAT_Escalado(1,0.1,1));
  agregar(mate); //Material
  
  cubo->ponerNombre("Base inferior, cuadrada");
  cubo->ponerIdentificador(12);
  
  agregar(cubo);
  
  Tupla3f gris_oscuro (0.41, 0.40, 0.40);
  ponerColor(gris_oscuro);
}

BaseBajaDchaArcoC::BaseBajaDchaArcoC(){  
  BaseInferiorTriangArcoC * base_inf_tri = new BaseInferiorTriangArcoC();
  agregar(MAT_Traslacion(1,-1,0));
  agregar(mate); //Material
  
  base_inf_tri->ponerNombre("Base inferior, triangular");
  base_inf_tri->ponerIdentificador(13);
  
  agregar(base_inf_tri);
  
  Tupla3f gris_oscuro (0.41, 0.40, 0.40);
  ponerColor(gris_oscuro);
}

Rueda::Rueda(float x, float y, float z){
  Cilindro * cil = new Cilindro(12, 24, true);
  agregar( MAT_Traslacion(x, y, z) );
  agregar( MAT_Rotacion(90, 1, 0, 0) );
  agregar( MAT_Escalado(0.125,0.125,0.125) );
  agregar( cil );
  
  Tupla3f gris_muy_oscuro (0.19, 0.19, 0.19);
  ponerColor(gris_muy_oscuro);
}

TotalRuedas::TotalRuedas(){
  agregar(MAT_Traslacion(1,-1,0));
  agregar(mate); //Material
  Rueda * ru1 = new Rueda(1.75,-0.325,0.3625);
  ru1->ponerNombre("Rueda 1");
  ru1->ponerIdentificador(14);
  agregar(ru1);
  Rueda * ru2 = new Rueda(1.75,-0.325,-0.3625);
  ru2->ponerNombre("Rueda 2");
  ru2->ponerIdentificador(15);
  agregar(ru2);
  
  Rueda * ru3 = new Rueda(0.0,-0.325,1.0625);
  ru3->ponerNombre("Rueda 3");
  ru3->ponerIdentificador(16);
  agregar(ru3);
  Rueda * ru4 = new Rueda(0.0,-0.325,-1.0625);
  ru4->ponerNombre("Rueda 4");
  ru4->ponerIdentificador(17);
  agregar(ru4);
}
