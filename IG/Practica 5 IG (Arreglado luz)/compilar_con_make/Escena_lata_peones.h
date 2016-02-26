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

	int numFiguras=5;


	vector<int> asignarColor(vector<int> &v){
		if(v[2]<1){
			v[2]+=0.01;
		}else if(v[1]<1){
			v[1]+=0.1;
			v[2]=0;
		}else{
			v[0]+=0.1;
			v[1]=0;
			v[2]=0;
		}
		return v;
	}



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
			tapa_sup_lata->resetMaterial();
			//tapa_sup_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			tapa_sup_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			tapa_sup_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//tapa_sup_lata->setMaterialShininess(0.6*128);
			tapa_sup_lata->aplicarMaterial(0,1,1,0);
			tapa_sup_lata->dibujarSuavizadoPlano(grosor,ajedrez);


			tapa_inf_lata->resetMaterial();
			//tapa_inf_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			tapa_inf_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			tapa_inf_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//tapa_inf_lata->setMaterialShininess(0.6*128);
			tapa_inf_lata->aplicarMaterial(0,1,1,0);
			tapa_inf_lata->dibujarSuavizadoPlano(grosor,ajedrez);
			
 	 	 	
			cuerpo_lata->resetMaterial();
			//cuerpo_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			cuerpo_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			cuerpo_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//cuerpo_lata->setMaterialShininess(0.6*128);
			cuerpo_lata->aplicarMaterial(0,1,1,0);
			cuerpo_lata->setTextura("tex/text-lata-1.jpg");
			cuerpo_lata->dibujarSuavizadoPlano(grosor,ajedrez);

			cuerpo_lata->resetMaterial(); //Reseteo el material del último para que no interfiera en el siguiente
		glPopMatrix();
			
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			
			//peon->setMaterialAmbient(0, 	0, 	0, 0.0);
			peon->setMaterialDifuse(0.8, 0.8, 0.8, 0.2);
			peon->setMaterialSpecular(1.0, 1.0,	1.0, 0.6);
			//peon->setMaterialShininess(1*128);
			peon->aplicarMaterial(0,1,1,0);

			peon->setTextura("tex/text-madera.jpg");
			peon->dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();

		peon->resetTextura();
		peon->resetMaterial();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);


			peon->setMaterialAmbient(0, 	0, 	0, 0.0);
			peon->setMaterialDifuse(0.8, 	0.8, 	0.8, 1.0);
			peon->setMaterialSpecular(0.015, 	0.015, 	0.015, 1.0);
			peon->setMaterialShininess(0.03*128);
			peon->aplicarMaterial(0,1,1,0);

			peon->dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();
		
		peon->resetTextura();
		peon->resetMaterial();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			
			peon->setMaterialAmbient(0.01, 	0.01, 	0.01, 1.0);
			peon->setMaterialDifuse(0.01, 	0.01, 	0.01, 0.0);
			peon->setMaterialSpecular(0.015, 	0.015, 	0.015, 1.0);
			peon->setMaterialShininess(0.03*128);
			peon->aplicarMaterial(0,1,1,0);

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
			tapa_sup_lata->resetMaterial();
			//tapa_sup_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			tapa_sup_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			tapa_sup_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//tapa_sup_lata->setMaterialShininess(0.6*128);
			tapa_sup_lata->aplicarMaterial(0,1,1,0);
			tapa_sup_lata->dibujarSuavizadoGouraud(grosor,ajedrez);


			tapa_inf_lata->resetMaterial();
			//tapa_inf_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			tapa_inf_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			tapa_inf_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//tapa_inf_lata->setMaterialShininess(0.6*128);
			tapa_inf_lata->aplicarMaterial(0,1,1,0);
			tapa_inf_lata->dibujarSuavizadoGouraud(grosor,ajedrez);
			
 	 	 	
			cuerpo_lata->resetMaterial();
			//cuerpo_lata->setMaterialAmbient(0.25, 	0.25, 	0.25, 1.0);
			cuerpo_lata->setMaterialDifuse(0.50754 ,	0.50754 ,	0.50754, 0.0);
			cuerpo_lata->setMaterialSpecular(0.508273 ,	0.508273 ,	0.508273, 0.0);
			//cuerpo_lata->setMaterialShininess(0.6*128);
			cuerpo_lata->aplicarMaterial(0,1,1,0);
			cuerpo_lata->setTextura("tex/text-lata-1.jpg");
			cuerpo_lata->dibujarSuavizadoGouraud(grosor,ajedrez);

			cuerpo_lata->resetMaterial(); //Reseteo el material del último para que no interfiera en el siguiente
		glPopMatrix();
			
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			
			//peon->setMaterialAmbient(0, 	0, 	0, 0.0);
			peon->setMaterialDifuse(0.8, 0.8, 0.8, 0.2);
			peon->setMaterialSpecular(1.0, 1.0,	1.0, 0.6);
			//peon->setMaterialShininess(1*128);
			peon->aplicarMaterial(0,1,1,0);

			peon->setTextura("tex/text-madera.jpg");
			peon->dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();

		peon->resetTextura();
		peon->resetMaterial();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);


			peon->setMaterialAmbient(0, 	0, 	0, 0.0);
			peon->setMaterialDifuse(0.8, 	0.8, 	0.8, 1.0);
			peon->setMaterialSpecular(0.015, 	0.015, 	0.015, 1.0);
			peon->setMaterialShininess(0.03*128);
			peon->aplicarMaterial(0,1,1,0);

			peon->dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();
		
		peon->resetTextura();
		peon->resetMaterial();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			
			peon->setMaterialAmbient(0.01, 	0.01, 	0.01, 1.0);
			peon->setMaterialDifuse(0.01, 	0.01, 	0.01, 0.0);
			peon->setMaterialSpecular(0.015, 	0.015, 	0.015, 1.0);
			peon->setMaterialShininess(0.03*128);
			peon->aplicarMaterial(0,1,1,0);

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




	void dibujarConNombres(int grosor, bool ajedrez){
		glInitNames();
		
		glPushName(0);
		glPushMatrix();
			glTranslatef(0,0,-3);
			glScalef(3,3,3);
			tapa_sup_lata->dibujar(grosor,ajedrez);
			tapa_inf_lata->dibujar(grosor,ajedrez);
			cuerpo_lata->dibujar(grosor,ajedrez); 
		glPopMatrix();
		
		glPushName(1);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushName(2);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();
		

		glPushName(3);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			peon->dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushName(4);
		glPushMatrix();
			glScalef(10,10,10);
			//glTranslatef(1,1.5,6);
			glRotatef(90,1,0,0);
			tablero->dibujar(grosor,ajedrez);
		glPopMatrix();
	}







	void dibujarSeleccion(GLubyte r,GLubyte g,GLubyte b){
		glPushMatrix();
			glTranslatef(0,0,-3);
			glScalef(3,3,3);
			tapa_sup_lata->dibujarSeleccion(0,0,255);//1
			tapa_inf_lata->dibujarSeleccion(0,0,255);//1
			cuerpo_lata->dibujarSeleccion(0,0,255); //1
		glPopMatrix();

		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-1,1.5,2);
			peon->dibujarSeleccion(0,255,0);//2
		glPopMatrix();

		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(0,1.5,4);
			peon->dibujarSeleccion(0,255,255);//3
		glPopMatrix();
		
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(1,1.5,6);
			peon->dibujarSeleccion(255,0,0);//4
		glPopMatrix();


		glPushMatrix();
			glScalef(10,10,10);
			//glTranslatef(1,1.5,6);
			glRotatef(90,1,0,0);
			tablero->dibujarSeleccion(255,0,255);//1
		glPopMatrix();
	}



	int getNumFiguras(){return numFiguras;}
};

#endif