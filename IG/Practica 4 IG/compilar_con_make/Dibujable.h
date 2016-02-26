#ifndef __dibujable_
#define __dibujable_

#include "Material.h"

class Dibujable{
private:
	Material material;
public:
	virtual void dibujar(int grosor, bool ajedrez){}
	virtual void dibujarSuavizadoPlano(int grosor, bool ajedrez){}
	virtual void dibujarSuavizadoGouraud(int grosor, bool ajedrez){}
	virtual void dibujarTextura(int grosor, bool ajedrez){}
	virtual void dibujarTableroTextura(int grosor, bool ajedrez){}
};

#endif