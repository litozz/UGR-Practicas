#ifndef __Cubo_Barra_
#define __Cubo_Barra_

#include "Barra.h"
#include <math.h>

class Cubo_Barra : public virtual Dibujable{
private:
	Barra barra;
public:
	Cubo_Barra(){}

	Cubo_Barra(float r, float g, float b){
		setColor(r,g,b);
	}

	void setColor(float r,float g, float b){
		barra.setColor(r,g,b);
	}

	void dibujar(int grosor, bool ajedrez){
		glPushMatrix();
			glTranslatef(0.45,0,0.45);//Barra derecha delante
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.45,0,0.45);//Barra izda delante
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.45,0,-0.45);//Barra derecha detras
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.45,0,-0.45);//Barra izda detras
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-0.45);
			glRotatef(45,0,0,1);
			glScalef(1,sqrt(2)-0.1,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,0.45);
			glRotatef(-45,0,0,1);
			glScalef(1,sqrt(2)-0.1,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.45,-0.45);
			glRotatef(90,0,0,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.45,0.45);
			glRotatef(90,0,0,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.45,0.45,0);
			glRotatef(90,1,0,0);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.45,0.45,0);
			glRotatef(90,1,0,0);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.45,0,0);
			glRotatef(-45,1,0,0);
			glScalef(1,sqrt(2)-0.1,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.45,0,0);
			glRotatef(45,1,0,0);
			glScalef(1,sqrt(2)-0.1,1);
			barra.dibujar(grosor,ajedrez);
		glPopMatrix();

	}
};

#endif