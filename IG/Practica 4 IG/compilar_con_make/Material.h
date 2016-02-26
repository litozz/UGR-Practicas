#ifndef __Material_H_
#define __Material_H_

#import <math.h>
#define PI 3.14159265

class Material{
private:
	GLfloat difuse[4] = {0.4,0.4,0.4,1};					//Componente difusa del material
	GLfloat specular[4] = {0.774597,0.774597,0.774597,1};	//Componente especular del material
	GLfloat ambient[4] = {0.25,0.25,0.25,1};				//Componente ambiental del material
	float shininess=76.8;										//Componente de brillo
public:
	Material(){}


	void setComponenteDifusa(float a, float b, float c, float d){difuse[0]=a;difuse[1]=b;difuse[2]=c;difuse[3]=d;}
	void setComponenteEspecular(float a, float b, float c, float d){specular[0]=a;specular[1]=b;specular[2]=c;specular[3]=d;}
	void setComponenteAmbiental(float a, float b, float c, float d){ambient[0]=a;ambient[1]=b;ambient[2]=c;ambient[3]=d;}
	void setComponenteBrillo(float brillo){shininess=brillo*128;}

	void aplicarMaterial(){
		glDisable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat*)&difuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat*)&specular);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat*)&ambient);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
	}

	void habilitarColor(){glEnable(GL_COLOR_MATERIAL);}
	void deshabilitarColor(){glDisable(GL_COLOR_MATERIAL);}


	void resetMaterial(){
		difuse[0] = 0.4;		difuse[1] = 0.4;		difuse[2] = 0.4;		difuse[3] = 1;					
		specular[0] = 0.774597;	specular[1] = 0.774597;	specular[2] = 0.774597;	specular[3] = 1;
		ambient[0] = 0.25;		ambient[1] = 0.25;		ambient[2] = 0.25;		ambient[3] = 1;	
		shininess=76.8;
	}		
};

#endif