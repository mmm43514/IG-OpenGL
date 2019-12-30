#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"


// clase para grafo escena
class C : public NodoGrafoEscena{
 protected:
  float v;
  unsigned num_param = 5;
  float p_ang_rot_cil1, p_ang_rot_cil2, p_tras_sup, p_tras_hor, p_rot_arco;
  Matriz4f * pm_tras_sup = 0;
  Matriz4f * pm_ang_rot_cil1 = 0;
  Matriz4f * pm_ang_rot_cil2 = 0;
  Matriz4f * pm_tras_hor = 0;
  Matriz4f * pm_rot_arco = 0;
  
public:
  C(const float ang_rot_inicial_cil1, const float ang_rot_inicial_cil2, const float tras_sup_inicial, const float tras_hor_inicial, const float rot_arco_inicial); // constructor
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};

class CilindroV : public NodoGrafoEscena{
 public:
  CilindroV();
};

class CilindroH : public NodoGrafoEscena{
 public:
  CilindroH();
};

class SoporteSuperior : public NodoGrafoEscena{
 public:
  SoporteSuperior();
};

class EngArco : public NodoGrafoEscena{
 public:
  EngArco();
};

class TamborArco: public NodoGrafoEscena{
 public:
  TamborArco();
};

class FrenteTambor : public NodoGrafoEscena{
 public:
  FrenteTambor();
};

class ArcoR : public NodoGrafoEscena{
 public:
  ArcoR();
};

class BaseBajaArcoC : public NodoGrafoEscena{
 public:
  BaseBajaArcoC();
};

class BaseBajaDchaArcoC : public NodoGrafoEscena{
 public:
  BaseBajaDchaArcoC();
};

class Rueda : public NodoGrafoEscena{
  public:
  Rueda(float x, float y, float z);
};

class TotalRuedas : public NodoGrafoEscena{
  public:
  TotalRuedas();
};

