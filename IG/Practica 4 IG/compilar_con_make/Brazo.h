#ifndef __Brazo_
#define __Brazo_
#define PI 3.14159265
#include "Punta.h"
#include "Carro.h"

class Brazo{
private:
	Torre brazo=Torre(10,false,false);	//Brazo
	Torre trasera=Torre(10,true,false);	//Barra trasera
	Punta punta;					//Piramide altura, Tope del carro

	Figura enlace;					//Cubo que une el brazo y la trasera, Contrapeso de cemento
	Figura eje;						//Eje del giro del brazo, Tensores
	Carro carro;

	float anchoTotal;
	float carro_inicial=1;
	float carro_final;
	float carro_actual=carro_inicial;

	float max_bajada;
public:
	Brazo(){
		enlace.modelarCubo();
		eje.modelarCilindro(100,2*PI);
		anchoTotal=2+brazo.getAlturaTorre()+(trasera.getAlturaTorre()/2);
		carro_final=brazo.getAlturaTorre();
		max_bajada=carro.getMaxBajada();
	}

	float getMaxBajada(){return carro.getMaxBajada();}
	float getMinBajada(){return carro.getMinBajada();}
	float getMaxPosicion(){return carro_final;}
	float getMinPosicion(){return carro_inicial;}

	float getPosicionCarroActual(){return carro_actual;}
	float getBajadaPlumaActual(){carro.getBajadaPlumaActual();}

	float getAnchoBrazo(){return anchoTotal;}

	void avanzarCarro(){
		if(carro_actual<carro_final)
			carro_actual=carro_actual+0.1;
	}

	void retrocederCarro(){
		if(carro_actual>carro_inicial)
			carro_actual=carro_actual-0.1;
	}

	void resetPosicion(){
		carro_actual=carro_inicial;
		carro.resetPosicion();
	}

/*
setColorEnlace(float r, float g, float b)
setColorEje(float r, float g, float b)
setColorCarro(float r_cuerda, float g_cuerda, float b_cuerda,float r_carro, float g_carro, float b_carro,float r_bola, float g_bola, float b_bola)
void setColorBrazo(float rtorre,float gtorre, float btorre,float reje,float geje, float beje)
*/
	void setColorEnlace(float r, float g, float b){
		enlace.setColor(r,g,b);
	}

	void setColorEje(float r, float g, float b){
		eje.setColor(r,g,b);
	}

	void setColorCarro(float r_cuerda, float g_cuerda, float b_cuerda,
					   float r_carro, float g_carro, float b_carro,
					   float r_bola, float g_bola, float b_bola){
		carro.setColorCuerda(r_cuerda,g_cuerda,b_cuerda);
		carro.setColorSoporte(r_carro,g_carro,b_carro);
		carro.setColorBola(r_bola,g_bola,b_bola);
	}

	void setColorBrazo(float rtorre,float gtorre, float btorre,
					   float reje,float geje, float beje){
		brazo.setColorBase(rtorre,gtorre,btorre);
		brazo.setColorTorre(rtorre,gtorre,btorre);
		brazo.setColorEje(reje,geje,beje);

		trasera.setColorBase(rtorre,gtorre,btorre);
		trasera.setColorTorre(rtorre,gtorre,btorre);
		trasera.setColorEje(reje,geje,beje);

		punta.setColor(rtorre,gtorre,btorre);
	}

	Carro& getCarro(){return carro;} //Hay que devolverlo por referencia para actual sobre el objeto

	void dibujar(int grosor, bool ajedrez){
		//glPushMatrix();
		//	glTranslatef(3,0.4,0);
			glPushMatrix();
				glColor3f(1,1,0);
				glTranslatef(-5.5,0.5,0);
				glRotatef(90,0,0,1);
				brazo.dibujar(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0.5,0);
				enlace.dibujar(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();//Trasera
				glTranslatef(3,0.05,0);
				glScalef(0.5,0.1,1);
				glRotatef(90,0,0,1);
				trasera.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.25,0);
				glScalef(1,0.5,1);
				eje.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-brazo.getAlturaTorre()-1,0.5,0);
				glRotatef(90,0,0,1);
				punta.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,3,0);
				glScalef(1,4,1);
				punta.dibujar(grosor,ajedrez);
			glPopMatrix();

			//Dibujo el contrapeso
			glPushMatrix();
				glTranslatef((trasera.getAlturaTorre()/2)-1.1,0,0);
				glScalef(1.5,1,0.8);
				enlace.dibujar(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-carro_actual,-2.7,0);
				carro.dibujar(grosor,ajedrez);
			glPopMatrix();	

			//Tensor largo
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				float hipotenusa=sqrt((brazo.getAlturaTorre()+0.6)*(brazo.getAlturaTorre()+0.6)+20.25);
				glTranslatef(-5.25,3.15,0);
				glRotatef(90+23,0,0,1);
				glScalef(0.1,hipotenusa-0.2,0.1);
				eje.dibujar(grosor,ajedrez);
			glPopMatrix();

			//Tensor corto
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				hipotenusa=sqrt(((trasera.getAlturaTorre()+0.6)/2)*((trasera.getAlturaTorre()+0.6)/2)+20.25);//7.18401
				glTranslatef(2.8,2.7,0);
				glRotatef(90-44,0,0,1);
				glScalef(0.1,hipotenusa+0.6,0.1);
				eje.dibujar(grosor,ajedrez);
			glPopMatrix();

		//glPopMatrix();
	}





	void dibujarSuavizadoPlano(int grosor, bool ajedrez){
		//glPushMatrix();
		//	glTranslatef(3,0.4,0);
			glPushMatrix();
				glColor3f(1,1,0);
				glTranslatef(-5.5,0.5,0);
				glRotatef(90,0,0,1);
				brazo.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0.5,0);
				enlace.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();//Trasera
				glTranslatef(3,0.05,0);
				glScalef(0.5,0.1,1);
				glRotatef(90,0,0,1);
				trasera.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.25,0);
				glScalef(1,0.5,1);
				eje.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-brazo.getAlturaTorre()-1,0.5,0);
				glRotatef(90,0,0,1);
				punta.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,3,0);
				glScalef(1,4,1);
				punta.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			//Dibujo el contrapeso
			glPushMatrix();
				glTranslatef((trasera.getAlturaTorre()/2)-1.1,0,0);
				glScalef(1.5,1,0.8);
				enlace.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-carro_actual,-2.7,0);
				carro.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();	

			//Tensor largo
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				float hipotenusa=sqrt((brazo.getAlturaTorre()+0.6)*(brazo.getAlturaTorre()+0.6)+20.25);
				glTranslatef(-5.25,3.15,0);
				glRotatef(90+23,0,0,1);
				glScalef(0.1,hipotenusa-0.2,0.1);
				eje.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

			//Tensor corto
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				hipotenusa=sqrt(((trasera.getAlturaTorre()+0.6)/2)*((trasera.getAlturaTorre()+0.6)/2)+20.25);//7.18401
				glTranslatef(2.8,2.7,0);
				glRotatef(90-44,0,0,1);
				glScalef(0.1,hipotenusa+0.6,0.1);
				eje.dibujarSuavizadoPlano(grosor,ajedrez);
			glPopMatrix();

		//glPopMatrix();
	}




	void dibujarSuavizadoGouraud(int grosor, bool ajedrez){
		//glPushMatrix();
		//	glTranslatef(3,0.4,0);
			glPushMatrix();
				glColor3f(1,1,0);
				glTranslatef(-5.5,0.5,0);
				glRotatef(90,0,0,1);
				brazo.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0.5,0);
				enlace.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();
			
			glPushMatrix();//Trasera
				glTranslatef(3,0.05,0);
				glScalef(0.5,0.1,1);
				glRotatef(90,0,0,1);
				trasera.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.25,0);
				glScalef(1,0.5,1);
				eje.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-brazo.getAlturaTorre()-1,0.5,0);
				glRotatef(90,0,0,1);
				punta.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,3,0);
				glScalef(1,4,1);
				punta.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			//Dibujo el contrapeso
			glPushMatrix();
				glTranslatef((trasera.getAlturaTorre()/2)-1.1,0,0);
				glScalef(1.5,1,0.8);
				enlace.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-carro_actual,-2.7,0);
				carro.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();	

			//Tensor largo
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				float hipotenusa=sqrt((brazo.getAlturaTorre()+0.6)*(brazo.getAlturaTorre()+0.6)+20.25);
				glTranslatef(-5.25,3.15,0);
				glRotatef(90+23,0,0,1);
				glScalef(0.1,hipotenusa-0.2,0.1);
				eje.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

			//Tensor corto
			glPushMatrix();
				/*La punta mide 1.125, no 1*/
				hipotenusa=sqrt(((trasera.getAlturaTorre()+0.6)/2)*((trasera.getAlturaTorre()+0.6)/2)+20.25);//7.18401
				glTranslatef(2.8,2.7,0);
				glRotatef(90-44,0,0,1);
				glScalef(0.1,hipotenusa+0.6,0.1);
				eje.dibujarSuavizadoGouraud(grosor,ajedrez);
			glPopMatrix();

		//glPopMatrix();
	}
};

#endif