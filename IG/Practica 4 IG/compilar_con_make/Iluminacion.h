#ifndef __Iluminacion_H_
#define __Iluminacion_H_

#import <math.h>
#define PI 3.14159265

class Iluminacion{
private:
	
	int movimientoLuz=0;

	GLfloat luz0[4]={0,1,0,0};

	GLfloat luz1[4]={0,0,10,0};
	GLfloat colorluz1[4]={1,1,0,1};
	
	GLfloat luz2[4]={1,-10,0,0};
	GLfloat colorluz2[4]={0,1,1,1};

	GLfloat luz3[4]={0,0,0,10};
	GLfloat colorluz3[4]={0,0,1,1};
	
	GLfloat ambient[4]={1,1,1,1};

public:
	Iluminacion(){}
	

	void setColorLuz1(float r, float g, float b){colorluz1[0]=r; colorluz1[1]=g; colorluz1[2]=b;}
	void setColorLuz2(float r, float g, float b){colorluz2[0]=r; colorluz2[1]=g; colorluz2[2]=b;}
	void setColorLuz3(float r, float g, float b){colorluz3[0]=r; colorluz3[1]=g; colorluz3[2]=b;}

	void habilitar(){
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

		glLightfv(GL_LIGHT0, GL_POSITION, luz0);

		glPushMatrix();
			glRotatef(movimientoLuz,1,0,0);
			glLightfv(GL_LIGHT1,GL_POSITION,luz1);
			glLightfv(GL_LIGHT1,GL_DIFFUSE, colorluz1);
		glPopMatrix();

		glLightfv(GL_LIGHT2,GL_POSITION, luz2);
		glLightfv(GL_LIGHT2,GL_DIFFUSE, colorluz2);

		glLightfv(GL_LIGHT3, GL_POSITION, luz3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, colorluz3);

		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

	}


	void deshabilitar(){
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHTING);
	}	//¿Por qué no funciona?

	void moverUp(){movimientoLuz++;}
	void moverDown(){movimientoLuz--;}
};

#endif