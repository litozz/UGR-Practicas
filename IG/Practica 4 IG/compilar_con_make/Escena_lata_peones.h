#ifndef __E_L_P_
#define __E_L_P_

#include "Figura.h"
#include <string>
#include "Dibujable.h"

class Escena_Lata_Peones:public virtual Dibujable{
private:
	Figura * peon;
	Figura * cuerpo_lata;
	Figura * tapa_sup_lata;
	Figura * tapa_inf_lata;
	Figura * tablero;

public:
	Escena_Lata_Peones(){
		peon = new Figura("ply/perfil.ply",1000, 2*PI);
		cuerpo_lata = new Figura("tex/lata-pcue.ply",1000, 2*PI);
		tapa_sup_lata = new Figura("tex/lata-psup.ply",1000, 2*PI);
		tapa_inf_lata = new Figura("tex/lata-pinf.ply",1000, 2*PI);
		tablero = new Figura();
		tablero->modelarTablero(2);
	}


	/*Escena_Lata_Peones(string t_lata, string t_p1, string t_tab){
		peon = new Figura("ply/perfil.ply",1000, 2*PI);
		cuerpo_lata = new Figura("tex/lata-pcue.ply",1000, 2*PI);
		tapa_sup_lata = new Figura("tex/lata-psup.ply",1000, 2*PI);
		tapa_inf_lata = new Figura("tex/lata-pinf.ply",1000, 2*PI);
		tablero = new Figura();
		tablero->modelarTablero(2);
		peon2= new Figura("ply/perfil.ply",1000, 2*PI);
		peon2->setColor(1,1,1);
		peon3= new Figura("ply/perfil.ply",1000, 2*PI);
		peon3->setColor(0,0,0);

		texturas.push_back(t_lata);
		texturas.push_back(t_p1);
		texturas.push_back(t_tab);
	}*/

	void dibujar(int grosor, bool ajedrez){
		glPushMatrix();
			glTranslatef(0,0,-3);
			glScalef(3,3,3);
			tapa_sup_lata->dibujar(grosor,ajedrez);
			tapa_inf_lata->dibujar(grosor,ajedrez);
			cuerpo_lata->dibujar(grosor,ajedrez); 
		glPopMatrix();
		

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();
		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glScalef(10,10,10);
			//glTranslatef(1,1.5,6);
			glRotatef(90,1,0,0);
			tablero->dibujar(grosor,ajedrez);
		glPopMatrix();
	}

	void dibujarSuavizadoPlano(int grosor, bool ajedrez){
		glPushMatrix();
			glTranslatef(0,0,-3);
			glScalef(3,3,3);
			tapa_sup_lata->setComponenteDifusaMaterial(0.19225,0.19225,0.19225, 1);
			tapa_sup_lata->setComponenteEspecularMaterial(0.50754,0.50754,0.50754, 1);
			tapa_sup_lata->setComponenteAmbientalMaterial(0.508273,0.508273,0.508273, 0.1);
			tapa_sup_lata->setComponenteBrilloMaterial(0.4);
			tapa_sup_lata->aplicarMaterial();
			tapa_sup_lata->dibujarSuavizadoPlano(grosor,ajedrez);



			tapa_inf_lata->setComponenteDifusaMaterial(0.19225,0.19225,0.19225, 1);
			tapa_inf_lata->setComponenteEspecularMaterial(0.50754,0.50754,0.50754, 1);
			tapa_inf_lata->setComponenteAmbientalMaterial(0.508273,0.508273,0.508273, 0.1);
			tapa_inf_lata->setComponenteBrilloMaterial(0.4);
			tapa_inf_lata->aplicarMaterial();
			tapa_inf_lata->dibujarSuavizadoPlano(grosor,ajedrez);




			cuerpo_lata->setComponenteDifusaMaterial(0.25 ,0.25,0.25,1);
			cuerpo_lata->setComponenteEspecularMaterial(0.4,0.4,0.4,1);
			cuerpo_lata->setComponenteAmbientalMaterial(0.774597,0.774597,0.774597,1);
			cuerpo_lata->setComponenteBrilloMaterial(0.6);

			cuerpo_lata->setTextura("tex/text-lata-1.jpg");
			cuerpo_lata->aplicarMaterial();
			cuerpo_lata->dibujarSuavizadoPlano(grosor,ajedrez); 
		glPopMatrix();
		

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			peon->setComponenteDifusaMaterial(0.21,0.13,0.05,1.0);
			peon->setComponenteEspecularMaterial(0.71,0.43,0.18,1.0);
			peon->setComponenteAmbientalMaterial(0.39,0.27,0.17,1.0);
			peon->setComponenteBrilloMaterial(0.2);
			peon->setTextura("tex/text-madera.jpg");
			peon->dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();

		peon->resetTextura();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);
			peon->setComponenteDifusaMaterial(0.00, 	0.00, 	0.00, 	1.0 );
			peon->setComponenteEspecularMaterial(0.01, 	0.01, 	0.01, 	1.0);
			peon->setComponenteAmbientalMaterial(0.50, 	0.50, 	0.50, 	1.0);
			peon->setComponenteBrilloMaterial(0.25);
			peon->aplicarMaterial();
			peon->dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();
		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			peon->setTextura("tex/tex_black.jpg");
			peon->setComponenteDifusaMaterial(0.02, 	0.02, 	0.02, 	1.0  );
			peon->setComponenteEspecularMaterial(0.01, 	0.01, 	0.01, 	1.0);
			peon->setComponenteAmbientalMaterial(0.40, 	0.40, 	0.40, 	1.0);
			peon->setComponenteBrilloMaterial(0.128);
			peon->dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glScalef(10,10,10);
			//glTranslatef(1,1.5,6);
			glRotatef(90,1,0,0);
			tablero->setTextura("tex/escaques4x4.jpg");
			tablero->dibujarTableroTextura(grosor,ajedrez);
		glPopMatrix();
	}

	void dibujarSuavizadoGouraud(int grosor, bool ajedrez){
		glPushMatrix();
			glTranslatef(0,0,-3);
			glScalef(3,3,3);

			tapa_sup_lata->setComponenteDifusaMaterial(0.19225,0.19225,0.19225, 1);
			tapa_sup_lata->setComponenteEspecularMaterial(0.50754,0.50754,0.50754, 1);
			tapa_sup_lata->setComponenteAmbientalMaterial(0.508273,0.508273,0.508273, 0.1);
			tapa_sup_lata->setComponenteBrilloMaterial(0.4);

			tapa_sup_lata->aplicarMaterial();
			tapa_sup_lata->dibujarSuavizadoGouraud(grosor,ajedrez);


			tapa_inf_lata->setComponenteDifusaMaterial(0.19225,0.19225,0.19225, 1);
			tapa_inf_lata->setComponenteEspecularMaterial(0.50754,0.50754,0.50754, 1);
			tapa_inf_lata->setComponenteAmbientalMaterial(0.508273,0.508273,0.508273, 0.1);
			tapa_inf_lata->setComponenteBrilloMaterial(0.4);

			tapa_inf_lata->aplicarMaterial();
			tapa_inf_lata->dibujarSuavizadoGouraud(grosor,ajedrez);
			
 	 	 	
			cuerpo_lata->setComponenteDifusaMaterial(0.25 ,0.25,0.25,1);
			cuerpo_lata->setComponenteEspecularMaterial(0.4,0.4,0.4,1);
			cuerpo_lata->setComponenteAmbientalMaterial(0.774597,0.774597,0.774597,1);
			cuerpo_lata->setComponenteBrilloMaterial(0.6);

			cuerpo_lata->setTextura("tex/text-lata-1.jpg");
			cuerpo_lata->aplicarMaterial();
			cuerpo_lata->dibujarSuavizadoGouraud(grosor,ajedrez);


		glPopMatrix();
		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
 		 				
			peon->setComponenteDifusaMaterial(0.21,0.13,0.05,1.0);
			peon->setComponenteEspecularMaterial(0.71,0.43,0.18,1.0);
			peon->setComponenteAmbientalMaterial(0.39,0.27,0.17,1.0);
			peon->setComponenteBrilloMaterial(0.2);

			peon->setTextura("tex/text-madera.jpg");
			peon->aplicarMaterial();
			peon->dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();

		peon->resetTextura();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);

			peon->setComponenteDifusaMaterial(0.00, 	0.00, 	0.00, 	1.0 );
			peon->setComponenteEspecularMaterial(0.01, 	0.01, 	0.01, 	1.0);
			peon->setComponenteAmbientalMaterial(0.50, 	0.50, 	0.50, 	1.0);
			peon->setComponenteBrilloMaterial(0.25);
			peon->aplicarMaterial();
			peon->dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();
		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			peon->setTextura("tex/tex_black.jpg");

			peon->setComponenteDifusaMaterial(0.02, 	0.02, 	0.02, 	1.0  );
			peon->setComponenteEspecularMaterial(0.01, 	0.01, 	0.01, 	1.0);
			peon->setComponenteAmbientalMaterial(0.40, 	0.40, 	0.40, 	1.0);
			peon->setComponenteBrilloMaterial(0.128);
			peon->aplicarMaterial();


			peon->dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glScalef(10,10,10);
			//glTranslatef(1,1.5,6);
			glRotatef(90,1,0,0);
			tablero->setTextura("tex/escaques4x4.jpg");
			tablero->dibujarTableroTextura(grosor,ajedrez);
		glPopMatrix();
	}
};

#endif