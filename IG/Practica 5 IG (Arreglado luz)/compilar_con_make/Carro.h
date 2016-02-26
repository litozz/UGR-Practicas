#ifndef __Carro_
#define __Carro_
#define PI 3.14159265
#include "Figura.h"
#include <GL/glut.h>

class Carro{
private:
	Figura cuerda;
	Figura soporte;
	GLUquadric  *quadObj;

	float plomo_inicial=1;
	float plomo_final=10;
	float plomo_actual=plomo_inicial;

	float r_bola,g_bola,b_bola;
public:
	Carro(){
		cuerda.modelarCilindro(50,2*PI);
		soporte.modelarCubo();
	}

	Carro(float r_c, float g_c, float b_c, float r_s, float g_s, float b_s){
		cuerda.modelarCilindro(50,2*PI);
		soporte.modelarCubo();
		setColorCuerda(r_c,g_c,b_c);
		setColorSoporte(r_s,g_s,b_s);
	}

	float getMaxBajada(){return plomo_final;}
	float getMinBajada(){return plomo_inicial;}
	float getBajadaPlumaActual(){return plomo_actual;}

	void setColorCuerda(float r_c, float g_c, float b_c){cuerda.setColor(r_c,g_c,b_c);}
	void setColorSoporte(float r_s, float g_s, float b_s){soporte.setColor(r_s,g_s,b_s);}
	void setColorBola(float r, float g, float b){r_bola=r;g_bola=g;b_bola=b;}

	void bajarPlomo(){
		if(plomo_actual<plomo_final)
			plomo_actual=plomo_actual+0.1;
	}

	void subirPlomo(){
		if(plomo_actual>plomo_inicial)
			plomo_actual=plomo_actual-0.1;
	}

	void resetPosicion(){
		plomo_actual=plomo_inicial;
	}

	void dibujar(int grosor, int ajedrez){
		glPushMatrix();
			glTranslatef(0,2.75,0);	
			glPushMatrix();
				glTranslatef(0,-0.1,0);
				glScalef(1,0.2,1);
				soporte.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-(plomo_actual/2),0);
				glScalef(0.05,plomo_actual,0.05);
				cuerda.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glColor3f(r_bola,g_bola,b_bola);
				glTranslatef(0,-(plomo_actual)-0.3,0);
				quadObj = gluNewQuadric();
				gluQuadricTexture(quadObj, GL_TRUE);
				gluSphere (quadObj,0.3,50,50);
			glPopMatrix();
		glPopMatrix();
	}









	void dibujarSuavizadoPlano(int grosor, int ajedrez){
		glPushMatrix();
			glTranslatef(0,2.75,0);	
			glPushMatrix();
				glTranslatef(0,-0.1,0);
				glScalef(1,0.2,1);
				soporte.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-(plomo_actual/2),0);
				glScalef(0.05,plomo_actual,0.05);
				cuerda.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glColor3f(r_bola,g_bola,b_bola);
				glTranslatef(0,-(plomo_actual)-0.3,0);
				quadObj = gluNewQuadric();
				gluQuadricTexture(quadObj, GL_TRUE);
				gluSphere (quadObj,0.3,50,50);
			glPopMatrix();
		glPopMatrix();
	}



	void dibujarSuavizadoGouraud(int grosor, int ajedrez){
		glPushMatrix();
			glTranslatef(0,2.75,0);	
			glPushMatrix();
				glTranslatef(0,-0.1,0);
				glScalef(1,0.2,1);
				soporte.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-(plomo_actual/2),0);
				glScalef(0.05,plomo_actual,0.05);
				cuerda.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glColor3f(r_bola,g_bola,b_bola);
				glTranslatef(0,-(plomo_actual)-0.3,0);
				quadObj = gluNewQuadric();
				gluQuadricTexture(quadObj, GL_TRUE);
				gluSphere (quadObj,0.3,50,50);
			glPopMatrix();
		glPopMatrix();
	}
};

#endif