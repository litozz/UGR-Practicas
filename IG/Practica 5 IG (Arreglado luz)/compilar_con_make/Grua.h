#ifndef __Grua_
#define __Grua_

#include "Brazo.h"
#include "Dibujable.h"

class Grua : public virtual Dibujable{
private:
	Torre torre=Torre(10,true,true);
	Brazo brazo;

	int grado_inicio=360;
	float min_bajada, max_bajada, max_posicion, min_posicion;
	
public:
	Grua(){
		
		torre.setColorBase(0.412, 0.412, 0.412);
		torre.setColorTorre(1,0.843,0);
		torre.setColorEje(0.412, 0.412, 0.412);
		
		brazo.setColorEnlace(0.412, 0.412, 0.412);
		brazo.setColorEje(0.0,0.0,0.804);
		brazo.setColorCarro(0,0,0,	0.412, 0.412, 0.412,	0.412, 0.412, 0.412);
		brazo.setColorBrazo(1,0.843,0,	0.412, 0.412, 0.412); //Color del brazo transversal

		min_bajada=brazo.getMinBajada();
		max_bajada=brazo.getMaxBajada();
		max_posicion=brazo.getMaxPosicion();
		min_posicion=brazo.getMinPosicion();
	}

	void avanzarCarro(){brazo.avanzarCarro();}
	void retrocederCarro(){brazo.retrocederCarro();}
	void subirPlomo(){brazo.getCarro().subirPlomo();}
	void bajarPlomo(){brazo.getCarro().bajarPlomo();}

	float getMinBajada(){return min_bajada;}
	float getMaxBajada(){return max_bajada;}
	float getMinPosicion(){return min_posicion;}
	float getMaxPosicion(){return max_posicion;}

	float getPosicionCarroActual(){return brazo.getPosicionCarroActual();}
	float getBajadaPlumaActual(){return brazo.getBajadaPlumaActual();}

	void girarBrazoDerecha(){
		grado_inicio=(grado_inicio+1)%360;
	}

	void girarBrazoIzquierda(){
		grado_inicio=grado_inicio-1;
		if(grado_inicio==0)
			grado_inicio=360;
	}

	void resetPosicion(){
		brazo.resetPosicion();
		grado_inicio=360;
	}

	void dibujar(int grosor, bool ajedrez){
		torre.dibujar(grosor,ajedrez);
		glPushMatrix();
			glTranslatef(0,6,0);
			glRotatef(grado_inicio,0,1,0);
			brazo.dibujar(grosor,ajedrez);
		glPopMatrix();
	}

	
	void dibujarSuavizadoPlano(int grosor, bool ajedrez){
		torre.dibujarSuavizadoPlano(grosor,ajedrez);
		glPushMatrix();
			glTranslatef(0,6,0);
			glRotatef(grado_inicio,0,1,0);
			brazo.dibujarSuavizadoPlano(grosor,ajedrez);
		glPopMatrix();
	}

	void dibujarSuavizadoGouraud(int grosor, bool ajedrez){
		torre.dibujarSuavizadoGouraud(grosor,ajedrez);
		glPushMatrix();
			glTranslatef(0,6,0);
			glRotatef(grado_inicio,0,1,0);
			brazo.dibujarSuavizadoGouraud(grosor,ajedrez);
		glPopMatrix();
	}

};

#endif