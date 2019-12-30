
#include "latapeones.h"

Lata::Lata(){

	MallaRevolPLY * cuerpo = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 30);
	MallaRevolPLY * tapa_sup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 30);
	MallaRevolPLY * tapa_inf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 30);
	NodoGrafoEscena * cuerpo_lata = new NodoGrafoEscena();
	
	Textura * t_cue_lat = new Textura("../recursos/imgs/lata-coke.jpg");
	Material * mat_cue_lat = new Material(t_cue_lat, 0.3, 1, 1, 20);
	
	Material* mat_sup_inf_lat = new Material(0.3, 1, 1, 20);
	
	cuerpo_lata->agregar(mat_cue_lat);
	cuerpo_lata->agregar(cuerpo);
	
	//agregar(mat_cue_lat);
	//agregar(cuerpo);
	agregar(cuerpo_lata);
	agregar(mat_sup_inf_lat);
	agregar(tapa_sup);
	//agregar(mat_sup_inf_lat);
	agregar(tapa_inf);
	


}

LataPeones::LataPeones(){
	ponerNombre("Lata-Peones");
	
	Lata * lata = new Lata();
	agregar(lata);
	
	MallaRevolPLY * peon_revol = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon = new NodoGrafoEscena();
	peon->agregar(MAT_Traslacion(0,0.28,1));
	peon->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon->agregar(peon_revol);
	
	Textura * t_peon_madera = new Textura("../recursos/imgs/text-madera.jpg");
	Material * mat_peon_madera = new Material(t_peon_madera, 0.3, 1, 1, 20);
	agregar(mat_peon_madera);
	agregar(peon);
	
	MallaRevolPLY * peon_revol2 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon2 = new NodoGrafoEscena();
	peon2->agregar(MAT_Traslacion(0.5,0.28,1));
	peon2->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon2->agregar(peon_revol2);
	Material* mat_peon_blanco = new Material(0.3, 1, 0, 0);
	Tupla3f blanco(1,1,1);
	peon->ponerColor(blanco);
	agregar(mat_peon_blanco);
	agregar(peon2);    
	
	MallaRevolPLY * peon_revol3 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon3 = new NodoGrafoEscena();
	peon3->agregar(MAT_Traslacion(1,0.28,1));
	peon3->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon3->agregar(peon_revol3);
	Material* mat_peon_negro = new Material(0.3, 0.1, 1, 20);
	Tupla3f negro(0,0,0);
	peon3->ponerColor(negro);
	agregar(mat_peon_negro);
	agregar(peon3);
	
	 /*Textura * textura1=new Textura("../recursos/imgs/text-madera.jpg");
    Material * material1=new Material(textura1, 0.2, 0.8, 0.0, 0.0);
    agregar(material1);
    ponerNombre("Peon de Madera");
    ponerIdentificador(2);
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 20));

    agregar(MAT_Traslacion(0.0, 0.0, 2.0));
    Material * material2=new Material(0.2, 1.0, 0.0, 0.0);
    agregar(material2);
    ponerNombre("Peon blanco");
    ponerIdentificador(3);
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 20));

    agregar(MAT_Traslacion(0.0, 0.0, 2.0));
    Material * material3=new Material(0.0, 0.1, 0.1, 0.0);
    agregar(material3);
    ponerNombre("Peon negro");
    ponerIdentificador(4);
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 20));*/

}
