#ifndef __Punta_
#define __Punta_

#define PI 3.14159265
#include "Torre.h"

class Punta{
private:
	Barra barra;
	Figura punta;
public:
	Punta(){
		punta.modelarCono(4,2*PI);
	}

	Punta(float r,float g, float b){
		punta.modelarCono(4,2*PI);
		setColor(r,g,b);	
	}

	void setColor(float r,float g, float b){
		barra.setColor(r,g,b);
		punta.setColor(r,g,b);
	}

	void dibujar(int grosor, bool ajedrez){
		glPushMatrix();
			glTranslatef(0,-0.1,0);
			/*glPushMatrix();
				glTranslatef(0,-0.45,0.45);
				glRotatef(90,0,0,1);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.45,-0.45);
				glRotatef(90,0,0,1);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.45,-0.45,0);
				glRotatef(90,0,1,0);
				glRotatef(90,0,0,1);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.45,-0.45,0);
				glRotatef(90,0,1,0);
				glRotatef(90,0,0,1);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();*/

			glPushMatrix();
				glTranslatef((-0.45/2)-0.05,0,(-0.45/2)-0.05);
				glRotatef(45,0,1,0);
				glRotatef(30,1,0,0);
				glRotatef(45,0,1,0);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();


			glPushMatrix();
				glTranslatef(-(0.45/2)-0.05,0,(0.45/2)+0.05);
				glRotatef(-45,0,1,0);
				glRotatef(-30,1,0,0);
				glRotatef(45,0,1,0);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();


			glPushMatrix();
				glTranslatef((0.45/2)+0.05,0,(0.45/2)+0.05);
				glRotatef(45,0,1,0);
				glRotatef(-30,1,0,0);
				glRotatef(45,0,1,0);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef((0.45/2)+0.05,0,(-0.45/2)-0.05);
				glRotatef(-45,0,1,0);
				glRotatef(30,1,0,0);
				glRotatef(45,0,1,0);
				barra.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,0.625,0);
				glScalef(0.5,0.5,0.5);
				glRotatef(45,0,1,0);
				punta.dibujar(grosor,ajedrez);
			glPopMatrix();
		glPopMatrix();
	}
};

#endif