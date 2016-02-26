#ifndef __Barra_
#define __Barra_

#include "Figura.h"

class Barra{
private:
	Figura cubo;
public:
	Barra(){
		cubo.modelarCubo();
	}

	Barra(float r,float g, float b){
		cubo.setColor(r,g,b);
		cubo.modelarCubo();
	}

	void setColor(float r,float g, float b){
		cubo.setColor(r,g,b);
	}

	void dibujar(int grosor, bool ajedrez){
		glPushMatrix();
			glScalef(0.1,1,0.1);
			cubo.dibujar(grosor,ajedrez);
		glPopMatrix();
	}
};

#endif