#ifndef __Torre_
#define __Torre_
#define PI 3.14159265
#include "Cubo_Barra.h"


class Torre{
private:
	Figura base;
	Cubo_Barra cubo;
	Figura eje;
	int altura;
	bool dib_base;
	bool dib_eje;
	float coef_centrado;
public:
	Torre(){
		setSizes(10,true,true);
		base.modelarCubo();
		eje.modelarCilindro(50,2*PI);
	}

	Torre(int h, bool _base, bool _eje){
		setSizes(h,_base, _eje);
		base.modelarCubo();
		eje.modelarCilindro(50,2*PI);
	}

	Torre(int h, bool _base, bool _eje, 
		  float r_base, float g_base, float b_base,
		  float r_torre, float g_torre, float b_torre,
		  float r_eje, float g_eje, float b_eje){
		setSizes(h,_base, _eje);
		base.modelarCubo();
		eje.modelarCilindro(50,2*PI);
		setColorBase(r_base,g_base,b_base);
		setColorTorre(r_torre,g_torre,b_torre);
		setColorEje(r_eje,g_eje,b_eje);
	}

	void setColorBase(float r,float g, float b){base.setColor(r,g,b);}
	void setColorTorre(float r,float g, float b){cubo.setColor(r,g,b);}
	void setColorEje(float r,float g, float b){eje.setColor(r,g,b);}

	void setSizes(int h, bool _base, bool _eje){
		altura=h;
		dib_base=_base;
		dib_eje=_eje;
		coef_centrado=0.0;
		if(dib_base){coef_centrado=coef_centrado+0.5;}
		coef_centrado=altura+coef_centrado;
	}

	float getAlturaTorre(){return coef_centrado;}

	void dibujar(int grosor, bool ajedrez){
		float cont_dibujo=0;
		glPushMatrix();
			glTranslatef(0,-(coef_centrado/2),0);
			if(dib_base){
				cont_dibujo=cont_dibujo+0.5;
				glPushMatrix();
					glTranslatef(0,cont_dibujo/2,0);
					glScalef(1.5,0.5,1.5);
					base.dibujar(grosor,ajedrez);
				glPopMatrix();
			}
			int i=0;
			for(i=1;i<=altura;i++){
				cont_dibujo=cont_dibujo+0.5;
				glPushMatrix();
					glTranslatef(0,cont_dibujo,0);
					cubo.dibujar(grosor,ajedrez);
				glPopMatrix();
				cont_dibujo=cont_dibujo+0.5;
			}
			if(dib_eje){
				glPushMatrix();
					glTranslatef(0,(cont_dibujo/2)+0.5,0);
					glScalef(0.5,coef_centrado,0.5);
					eje.dibujar(grosor,ajedrez);
				glPopMatrix();
			}
		glPopMatrix();
	}
};

#endif