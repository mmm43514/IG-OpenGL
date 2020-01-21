
#include "latapeones.h"

Lata::Lata(){
	MallaRevolPLY * cuerpo = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 30);
	MallaRevolPLY * tapa_sup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 30);
	MallaRevolPLY * tapa_inf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 30);
	NodoGrafoEscena * cuerpo_lata = new NodoGrafoEscena();
	
	Textura * t_cue_lat = new Textura("../recursos/imgs/lata-coke.jpg", mgct_desactivada);
	Material * mat_cue_lat = new Material(t_cue_lat, 0.3, 1, 1, 20);
	
	Material* mat_sup_inf_lat = new Material(0.3, 1, 1, 20);
	
	cuerpo_lata->agregar(mat_cue_lat);
	cuerpo_lata->agregar(cuerpo);

	
	agregar(cuerpo_lata);
	agregar(mat_sup_inf_lat);
	agregar(tapa_sup);
	agregar(tapa_inf);

}

LataPepsi::LataPepsi(){
	MallaRevolPLY * cuerpo = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 30);
	MallaRevolPLY * tapa_sup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 30);
	MallaRevolPLY * tapa_inf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 30);
	NodoGrafoEscena * cuerpo_lata = new NodoGrafoEscena();
	
	Textura * t_cue_lat = new Textura("../recursos/imgs/lata-pepsi.jpg", mgct_desactivada);
	Material * mat_cue_lat = new Material(t_cue_lat, 0.3, 1, 1, 20);
	
	Material* mat_sup_inf_lat = new Material(0.3, 1, 1, 20);
	
	cuerpo_lata->agregar(mat_cue_lat);
	cuerpo_lata->agregar(cuerpo);

	agregar(cuerpo_lata);
	agregar(mat_sup_inf_lat);
	agregar(tapa_sup);
	agregar(tapa_inf);

}

LataUGR::LataUGR(){
	MallaRevolPLY * cuerpo = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 30);
	MallaRevolPLY * tapa_sup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 30);
	MallaRevolPLY * tapa_inf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 30);
	NodoGrafoEscena * cuerpo_lata = new NodoGrafoEscena();
	
	Textura * t_cue_lat = new Textura("../recursos/imgs/window-icon.jpg", mgct_desactivada);
	Material * mat_cue_lat = new Material(t_cue_lat, 0.3, 1, 1, 20);
	
	Material* mat_sup_inf_lat = new Material(0.3, 1, 1, 20);
	
	cuerpo_lata->agregar(mat_cue_lat);
	cuerpo_lata->agregar(cuerpo);
	
	agregar(cuerpo_lata);
	agregar(mat_sup_inf_lat);
	agregar(tapa_sup);
	agregar(tapa_inf);

}

LataPeones::LataPeones(){
	ponerNombre("Lata-Peones");
	ponerIdentificador(-1);
	
	Lata * lata = new Lata();
	lata->ponerNombre("Lata de Coca-Cola");
	lata->ponerIdentificador(7);
	agregar(lata);
	
	// peón madera
	MallaRevolPLY * peon_revol = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon = new NodoGrafoEscena();
	peon->ponerNombre("Peón de madera");
	peon->ponerIdentificador(8);
	peon->agregar(MAT_Traslacion(0,0.28,1));
	peon->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon->agregar(peon_revol);
	
	
	Textura * t_peon_madera = new Textura("../recursos/imgs/text-madera.jpg", mgct_coords_objeto);
	Material * mat_peon_madera = new Material(t_peon_madera, 0.3, 1, 1, 20);
	agregar(mat_peon_madera);
	agregar(peon);
	
	// peón blanco
	MallaRevolPLY * peon_revol2 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon2 = new NodoGrafoEscena();
	peon2->ponerNombre("Peón blanco");
	peon2->ponerIdentificador(9);
	peon2->agregar(MAT_Traslacion(0.5,0.28,1));
	peon2->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon2->agregar(peon_revol2);
	Material* mat_peon_blanco = new Material(0.3, 1, 0, 0);
	Tupla3f blanco(1,1,1);
	peon->ponerColor(blanco);
	agregar(mat_peon_blanco);
	agregar(peon2);    
	
	// peón negro
	MallaRevolPLY * peon_revol3 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon3 = new NodoGrafoEscena();
	peon3->ponerNombre("Peón negro");
	peon3->ponerIdentificador(10);
	peon3->agregar(MAT_Traslacion(1,0.28,1));
	peon3->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon3->agregar(peon_revol3);
	Material* mat_peon_negro = new Material(0.3, 0.1, 1, 20);
	Tupla3f negro(0,0,0);
	peon3->ponerColor(negro);
	agregar(mat_peon_negro);
	agregar(peon3);
	
}

VariasLatasPeones::VariasLatasPeones(){
	ponerNombre("Varias-Latas-Peones");
	ponerIdentificador(-1);
	
	NodoGrafoEscena * lata_coke = new NodoGrafoEscena();
	lata_coke->ponerNombre("Lata de Coca-Cola");
	lata_coke->ponerIdentificador(1);
	Lata * lata = new Lata();
	lata_coke->agregar(lata);
	agregar(lata_coke);
	
	NodoGrafoEscena * lata_pepsi = new NodoGrafoEscena();
	lata_pepsi->ponerNombre("Lata de Pepsi");
	lata_pepsi->ponerIdentificador(2);
	LataPepsi * lata2 = new LataPepsi();
	lata_pepsi->agregar(MAT_Traslacion(1,0,0));
	lata_pepsi->agregar(lata2);
	agregar(lata_pepsi);
	
	NodoGrafoEscena * lata_ugr = new NodoGrafoEscena();
	lata_ugr->ponerNombre("Lata de la UGR");
	lata_ugr->ponerIdentificador(3);
	LataUGR * lata3 = new LataUGR();
	lata_ugr->agregar(MAT_Traslacion(2,0,0));
	lata_ugr->agregar(lata3);
	agregar(lata_ugr);
	
	// peón madera
	MallaRevolPLY * peon_revol = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon = new NodoGrafoEscena();
	peon->ponerNombre("Peón de madera");
	peon->ponerIdentificador(4);
	peon->agregar(MAT_Traslacion(0,0.28,1));
	peon->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon->agregar(peon_revol);
	
	Textura * t_peon_madera = new Textura("../recursos/imgs/text-madera.jpg", mgct_coords_objeto);
	Material * mat_peon_madera = new Material(t_peon_madera, 0.3, 1, 1, 20);
	agregar(mat_peon_madera);
	agregar(peon);
	
	// peón blanco
	MallaRevolPLY * peon_revol2 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon2 = new NodoGrafoEscena();
	peon2->ponerNombre("Peón blanco");
	peon2->ponerIdentificador(5);
	peon2->agregar(MAT_Traslacion(0.5,0.28,1));
	peon2->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon2->agregar(peon_revol2);
	Material* mat_peon_blanco = new Material(0.3, 1, 0, 0);
	Tupla3f blanco(1,1,1);
	peon->ponerColor(blanco);
	agregar(mat_peon_blanco);
	agregar(peon2);    
	
	// peón negro
	MallaRevolPLY * peon_revol3 = new MallaRevolPLY("../recursos/plys/peon.ply", 30);
	NodoGrafoEscena * peon3 = new NodoGrafoEscena();
	peon3->ponerNombre("Peón negro");
	peon3->ponerIdentificador(6);
	peon3->agregar(MAT_Traslacion(1,0.28,1));
	peon3->agregar(MAT_Escalado(0.2,0.2,0.2));
	peon3->agregar(peon_revol3);
	Material* mat_peon_negro = new Material(0.3, 0.1, 1, 20);
	Tupla3f negro(0,0,0);
	peon3->ponerColor(negro);
	agregar(mat_peon_negro);
	agregar(peon3);
	
}
