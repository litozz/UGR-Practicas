#ifndef __Figura_
#define __Figura_

#include "Dibujable.h"
#include <jpg_imagen.hpp>
#include <jpg_jinclude.h>
#include <math.h>
#include <string>
//#include "Material.h"

#define PI 3.14159265


class Figura : public virtual Dibujable{
	private:
		GLfloat material_ambient[4]	= {0.19225,0.19225,0.19225, 1}; 	
		GLfloat material_difuse[4]	= {0.50754,0.50754,0.50754, 1}; 	
		GLfloat material_specular[4]= {0.508273,0.508273,0.508273, 0.1}; 	
		GLfloat material_shininess[1]= {0.4};

		vector<_vertex3f> vertices_ply_3f;
		vector<_vertex3i> caras_ply_3i;

		vector<_vertex3f> vertices_ply_3f_r;
		vector<_vertex3i> caras_ply_3i_r;

		vector<_vertex3f> vertices_ply_3f_b;
		vector<_vertex3i> caras_ply_3i_b;

		vector<_vertex3f> normales_caras;
		vector<_vertex3f> normales_vertices;

		vector<_vertex2f> coord_textura;

		vector<_vertex3f> *vertices;
		vector<_vertex3i> *caras;

		string textura="NONE";


		jpg::Imagen * pimg = NULL;
		unsigned long tamx;
		unsigned long tamy;
		unsigned char * texels;

		int nPerfilesTablero;
		int nCuadradosTablero;
		int nivelTablero;

		float r1=1.0f,g1=0.0f,b1=0.0f,r2=0.0f,g2=1.0f,b2=0.0f;

		float *r=&r1,*g=&g1,*b=&b1;

		//Material material;

		void revolucion(int nveces, float angulo_final){
			//REVOLUCION DE VERTICES
			_vertex3f punto_primo;
			float inicio=angulo_final/nveces;
			//Copio el contenido de los vértices el los vértices del revolucionado
			vertices_ply_3f_r.clear();
			for(int i=0;i<vertices_ply_3f.size();i++){vertices_ply_3f_r.push_back(vertices_ply_3f[i]);}

			int numPuntosPerfil=vertices_ply_3f_r.size();

			/*i VA HASTA NVECES PARA DUPLICAR EL PRIMER PERFIL PARA TEXTURA*/
			for(int i=1;i<=nveces;i++){//Recorro las divisiones
				for(int j=0;j<numPuntosPerfil;j++){//Recorro los puntos
					punto_primo.x=vertices_ply_3f[j].x*cos(inicio*(i%nveces))+vertices_ply_3f[j].z*sin(inicio*(i%nveces));
					punto_primo.y=vertices_ply_3f[j].y;
					punto_primo.z=-vertices_ply_3f[j].x*sin(inicio*(i%nveces))+vertices_ply_3f[j].z*cos(inicio*(i%nveces));
					vertices_ply_3f_r.push_back(punto_primo);
				}
			}
			/*FIN GENERACIÓN DE VERTICES*/

			//UNION DE LOS PUNTOS PARA FORMAR LAS CARAS (MATRIZ DE REVOLUCION)
			caras_ply_3i_r.clear(); //IMPORTANTISIMO: Borro las caras que hubiera antes para que no se dibujen cosas erróneas.
			
			_vertex3i caraActual;
			for(int i=0;i<=nveces;i++){ //Recorro las divisiones de la circunferencia
				for(int j=0;j<numPuntosPerfil-1;j++){ //Recorro cada punto del perfil de esa división.
					//VOY A HACER MODULO (%) PARA CONSEGUIR UNA ESTRUCTURA CIRCULAR, ES DECIR, QUE EL PRIMER PERFIL Y EL ULTIMO SEAN EL MISMO.
					//Triangulos Pares
					caraActual.x=(i%nveces)*numPuntosPerfil+j;
					caraActual.y=((i+1)%nveces)*numPuntosPerfil+j;
					caraActual.z=((i+1)%nveces)*numPuntosPerfil+(j+1);
					caras_ply_3i_r.push_back(caraActual);
					//Triangulos Impares
					caraActual.x=(i%nveces)*numPuntosPerfil+j;
					caraActual.y=((i+1)%nveces)*numPuntosPerfil+(j+1);
					caraActual.z=(i%nveces)*numPuntosPerfil+(j+1);
					caras_ply_3i_r.push_back(caraActual);
				}
			}

			//PONER LAS TAPAS A LAS FIGURAS

			/*
			OJO!! SI METEMOS LA CREACION DE BASES EN UN SOLO BUCLE, LAS BASES SERÁN DE UN SOLO COLOR, 
			YA QUE SE ALTERNARÁN LOS COLORES ROJO ABAJO, VERDE ARRIBA.
			SI SE QUIERE QUE LAS BASES SEAN DE LOS DOS COLORES (PARA VER LAS DIVISIONES) SE HARAN EN
			DOS BUCLES DISTINTOS, ASI SE HARA ROJO ABAJO, VERDE ABAJO... Y LUEGO ROJO ARRIBA, VERDE
			ARRIBA... 
			*/

			_vertex3f centro_inferior;
			centro_inferior.x=0; centro_inferior.y=vertices_ply_3f_r[0].y; centro_inferior.z=0;
			vertices_ply_3f_r.push_back(centro_inferior);
			int index_cent_inf=vertices_ply_3f_r.size()-1;

			/*_vertex3f centro_superior;
			centro_superior.x=0; centro_superior.y=vertices_ply_3f[numPuntosPerfil-1].y; centro_superior.z=0;
			vertices_ply_3f.push_back(centro_superior);
			int index_cent_sup=vertices_ply_3f.size()-1;*/
			if(	centro_inferior.x!=vertices_ply_3f_r[0].x || 
				centro_inferior.y!=vertices_ply_3f_r[0].y || 
				centro_inferior.z!=vertices_ply_3f_r[0].z){ //Este if es para no replicar los puntos que ya se encuentran en el eje Y.
				for(int i=0;i<=nveces;i++){
					caraActual.x=index_cent_inf;
					caraActual.y=(i%nveces)*numPuntosPerfil;
					caraActual.z=((i+1)%nveces)*numPuntosPerfil;
					caras_ply_3i_r.push_back(caraActual);

					/*caraActual.x=index_cent_sup;
					caraActual.y=(i%nveces)*numPuntosPerfil+(numPuntosPerfil-1);
					caraActual.z=((i+1)%nveces)*numPuntosPerfil+(numPuntosPerfil-1);
					caras_ply_3i.push_back(caraActual);*/
				}
			}

			
			_vertex3f centro_superior;
			centro_superior.x=0; centro_superior.y=vertices_ply_3f_r[numPuntosPerfil-1].y; centro_superior.z=0;
			vertices_ply_3f_r.push_back(centro_superior);
			int index_cent_sup=vertices_ply_3f_r.size()-1;

			if(	centro_inferior.x!=vertices_ply_3f_r[numPuntosPerfil-1].x || 
				centro_inferior.y!=vertices_ply_3f_r[numPuntosPerfil-1].y || 
				centro_inferior.z!=vertices_ply_3f_r[numPuntosPerfil-1].z){ //Este if es para no replicar los puntos que ya se encuentran en el eje Y.
				for(int i=0;i<=nveces;i++){
					caraActual.x=vertices_ply_3f_r.size()-1;
					caraActual.y=(i%nveces)*numPuntosPerfil+(numPuntosPerfil-1);
					caraActual.z=((i+1)%nveces)*numPuntosPerfil+(numPuntosPerfil-1);
					caras_ply_3i_r.push_back(caraActual);
				}
			}



			/*CALCULO DE LA TABLA DE COORDENADAS DE TEXTURA*/
				/*PASO 1: TABLA DE DISTANCIAS*/
			vector<float> distancias(numPuntosPerfil);
			distancias[0]=0;
			for(int i=1;i<numPuntosPerfil;i++){
				//distancias[i]=abs((float)vertices_ply_3f[i].y - (float)vertices_ply_3f[0].y);
//				distancias[i]=distancias[i-1]+abs((float)vertices_ply_3f[(i+1)%numPuntosPerfil].y - (float)vertices_ply_3f[i].y);
				distancias[i] = (vertices_ply_3f[i].y - vertices_ply_3f[0].y) / (vertices_ply_3f[numPuntosPerfil-1].y - vertices_ply_3f[0].y);
			}
				/*PASO 2: COORDENADAS DE TEXTURA*/
			float si,tj;
			for(int i=0;i<=nveces;i++){
				si=(float)i/(float)nveces; //La revolución tiene nveces+1 perfiles -> (nveces+1)-1=nveces
				for(int j=0;j<numPuntosPerfil;j++){
					//tj=distancias[j]/distancias[numPuntosPerfil-1];
					tj=distancias[j];
					coord_textura.push_back(_vertex2f(si,tj));
				}
			}
			/*FIN CALCULO TABLA DE COORDENADAS DE TEXTURA*/



		}//FIN FUNCION DE REVOLUCION



		void barrido(int x, int y, int z){

			for(int i=0;i<vertices_ply_3f.size();i++){vertices_ply_3f_b.push_back(vertices_ply_3f[i]);}

			_vertex3f punto;
			for(int i=0;i<vertices_ply_3f.size();i++){
				punto.x=vertices_ply_3f[i].x+(x);
				punto.y=vertices_ply_3f[i].y+(y);
				punto.z=vertices_ply_3f[i].z+(z);
				vertices_ply_3f_b.push_back(punto);
			}
			
			caras_ply_3i_b.clear();
			
			_vertex3i caraActual;
			for(int i=0;i<2;i++){ //Recorro las divisiones de la circunferencia
				for(int j=0;j<vertices_ply_3f.size();j++){ //Recorro cada punto del perfil de esa división.

		/* HAGO MODULO EN J PORQUE ES NECESARIO QUE EL ULTIMO PUNTO DEL PERFIL SE UNA CON EL PRIMERO, A DIFERENCIA DE REVOLUCIÓN */

					//VOY A HACER MODULO (%) PARA CONSEGUIR UNA ESTRUCTURA CIRCULAR, ES DECIR, QUE EL PRIMER PERFIL Y EL ULTIMO SEAN EL MISMO.
					//Triangulos Pares
					caraActual.x=(j%vertices_ply_3f.size());
					caraActual.y=vertices_ply_3f.size()+(j%vertices_ply_3f.size());
					caraActual.z=vertices_ply_3f.size()+((j+1)%vertices_ply_3f.size());
					caras_ply_3i_b.push_back(caraActual);
					//Triangulos Impares
					caraActual.x=(j%vertices_ply_3f.size());
					caraActual.y=vertices_ply_3f.size()+((j+1)%vertices_ply_3f.size());
					caraActual.z=((j+1)%vertices_ply_3f.size());
					caras_ply_3i_b.push_back(caraActual);
				}
			}

			//Le pongo las tapas; Hago dos bucles independientes para que se distinga el modo ajedrez en ambas tapas
			_vertex3f centro;
			centro.x=0; centro.y=0; centro.z=0;
			vertices_ply_3f_b.push_back(centro);
			int index_cent_sup=vertices_ply_3f_b.size()-1;

			for(int i=0;i<vertices_ply_3f.size();i++){
				caraActual.x=index_cent_sup;
				caraActual.y=(vertices_ply_3f.size()+(i+1))%vertices_ply_3f.size();
				caraActual.z=(vertices_ply_3f.size()+(i+2))%vertices_ply_3f.size();
				caras_ply_3i_b.push_back(caraActual);
			}

			centro.x=x; centro.y=y; centro.z=z;
			vertices_ply_3f_b.push_back(centro);
			index_cent_sup=vertices_ply_3f_b.size()-1;

			for(int i=0;i<vertices_ply_3f.size();i++){
				caraActual.x=index_cent_sup;
				caraActual.y=vertices_ply_3f.size()+((vertices_ply_3f.size()+(i+1))%vertices_ply_3f.size());
				caraActual.z=vertices_ply_3f.size()+((vertices_ply_3f.size()+(i+2))%vertices_ply_3f.size());
				caras_ply_3i_b.push_back(caraActual);
			}
		}



		void loadPly(char* fichero){
			_file_ply ply;
			vector<float> vertices_ply;
			vector<int> caras_ply;

			vertices_ply_3f.clear();
			caras_ply_3i.clear();

			ply.open(fichero);
			ply.read(vertices_ply,caras_ply);

			_vertex3f punto;
			_vertex3i cara;
			
			for(int i=0;i<vertices_ply.size();i=i+3){
				punto.x=vertices_ply[i];
				punto.y=vertices_ply[i+1];
				punto.z=vertices_ply[i+2];			
				vertices_ply_3f.push_back(punto);
			}

			for(int i=0;i<caras_ply.size();i=i+3){
				cara.x=caras_ply[i];
				cara.y=caras_ply[i+1];
				cara.z=caras_ply[i+2];			
				caras_ply_3i.push_back(cara);
			}
		}


	public:
		
		Figura(){textura="NONE";};

		Figura(string tex){
			pimg=new jpg::Imagen(tex);
			tamx = pimg->tamX();
			tamy = pimg->tamY();
			texels = pimg->leerPixels();
			textura=tex;

			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); // Para que la textura tenga el color de la imagen
		};

		Figura(float _r, float _g, float _b){
			r1=_r;g1=_g;b1=_b;
			r2=0.0f;g2=0.0f;b2=0.0f;
			r=&r1;g=&g1;b=&b1;
		}

		Figura(float _r1, float _g1, float _b1, float _r2, float _g2, float _b2){
			r1=_r1;g1=_g1;b1=_b1;
			r2=_r2;g2=_g2;b2=_b2;
			r=&r1;g=&g1;b=&b1;
		}

		void setColor(float _r, float _g, float _b){
			r1=_r;g1=_g;b1=_b;
			r2=0.0f;g2=0.0f;b2=0.0f;
			r=&r1;g=&g1;b=&b1;
		}

		void setColor(float _r1, float _g1, float _b1, float _r2, float _g2, float _b2){
			r1=_r1;g1=_g1;b1=_b1;
			r2=_r2;g2=_g2;b2=_b2;
			r=&r1;g=&g1;b=&b1;
		}


		Figura(char * fichero){
			loadPly(fichero);
			setOriginalVertex();
			calcularNormales();
		}
		Figura(char* fichero, int nveces, float angulo_final){
			loadPly(fichero);
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
			calcularNormales();
		}
		Figura(char* fichero, int nveces, float angulo_final, int x, int y, int z){
			loadPly(fichero);
			revolucion(nveces, angulo_final);
			barrido(x,y,z);
			setSweepVertex();
			calcularNormales();
		}

		Figura(vector<_vertex3f> _vertices, vector<_vertex3i> _caras){
			vertices_ply_3f.clear();
			for(int i=0;i<_vertices.size();i++){
				vertices_ply_3f.push_back(_vertices[i]);
			}
			caras_ply_3i.clear();
			for(int i=0;i<_caras.size();i++){
				caras_ply_3i.push_back(_caras[i]);
			}
			setOriginalVertex();
			calcularNormales();
		}

		void modelarHexagono(int x, int y, int z){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(-0.5,0,0)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(-0.25,0.5,0));
			vertices_ply_3f.push_back(_vertex3f(0.25,0.5,0));
			vertices_ply_3f.push_back(_vertex3f(0.5,0,0));
			vertices_ply_3f.push_back(_vertex3f(0.25,-0.5,0));
			vertices_ply_3f.push_back(_vertex3f(-0.25,-0.5,0));
			barrido(x,y,z);
			setSweepVertex();
			calcularNormales();
		}

		void modelarTetraedro(){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(0.5,0.5,0.5)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(-0.5,-0.5,0.5));
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,-0.5));
			vertices_ply_3f.push_back(_vertex3f(-0.5,0.5,-0.5));//vertices[3]
			caras_ply_3i.push_back(_vertex3i(0,1,2));
			caras_ply_3i.push_back(_vertex3i(0,1,3));
			caras_ply_3i.push_back(_vertex3i(0,2,3));
			caras_ply_3i.push_back(_vertex3i(1,2,3));
			setOriginalVertex();
			calcularNormales();
		}




		void modelarTablero(int nivel){
			nivelTablero=nivel;
			vertices_ply_3f.clear();
			int nPuntos=0;
			if(nivel%2==1){
				nPuntos=nivel*2;
				for(float i=-nivel+0.5;i<=nivel-0.5;i++){ //Avanza X
					for(float j=-nivel+0.5;j<=nivel-0.5;j++){ //Avanza Y
						vertices_ply_3f.push_back(_vertex3f(i,j,0));//0
					}
				}

				for(int i=0;i<nPuntos-1;i++){
					for(int j=0;j<nPuntos-1;j++){
						caras_ply_3i.push_back(_vertex3i(i*nPuntos+j,i*nPuntos+(j+1),(i+1)*nPuntos+(j+1)));//Cara par
						caras_ply_3i.push_back(_vertex3i(i*nPuntos+j,(i+1)*nPuntos+j,(i+1)*nPuntos+(j+1)));//Cara impar
						nCuadradosTablero++;
					}
				}
				
			}else{
				nPuntos=nivel+1;
				for(float i=-nivel+1;i<=nivel-1;i++){ //Avanza X
					for(float j=-nivel+1;j<=nivel-1;j++){ //Avanza Y
						vertices_ply_3f.push_back(_vertex3f(i,j,0));//0
					}
				}


				for(int i=0;i<nPuntos-1;i++){
					for(int j=0;j<nPuntos-1;j++){
						caras_ply_3i.push_back(_vertex3i(i*nPuntos+j,i*nPuntos+(j+1),(i+1)*nPuntos+(j+1)));//Cara par
						caras_ply_3i.push_back(_vertex3i(i*nPuntos+j,(i+1)*nPuntos+j,(i+1)*nPuntos+(j+1)));//Cara impar
						nCuadradosTablero++;
					}
				}		
			}

			vector<float> distancias(nPuntos);
			distancias[0]=0;
			for(int i=1;i<nPuntos;i++){
				distancias[i] = (float)(vertices_ply_3f[i].y - vertices_ply_3f[0].y) / (float)(vertices_ply_3f[nPuntos-1].y - vertices_ply_3f[0].y);
			}
				
			float si=0,tj=0;
			for(int i=0;i<nPuntos;i++){
				si=(float)i/(float)(nPuntos-1);
				for(int j=0;j<nPuntos;j++){
					tj=distancias[j];
					coord_textura.push_back(_vertex2f(tj,si));
				}
			}

			nPerfilesTablero=nPuntos;
			setOriginalVertex();
			calcularNormales();
		}

		void dibujarTableroTextura(int grosor, bool ajedrez){

			if((*vertices).size()>=1 && (*caras).size()>=1){

				resetColors();
				glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
				glColor3f(*r,*g,*b);
				glEnable(GL_TEXTURE_2D);						
				glBegin(GL_TRIANGLES);	
				//Rastreo el vector de caras para ir dibujandolos
				

				for(int i=0;i<nPerfilesTablero-1;i++){
					for(int j=0;j<nPerfilesTablero-1;j++){
						//Cara inferior
						glNormal3f(normales_vertices[i*nPerfilesTablero+j].x,normales_vertices[i*nPerfilesTablero+j].y,normales_vertices[i*nPerfilesTablero+j].z);
						glTexCoord2f(coord_textura[0*nPerfilesTablero+0].x,coord_textura[0*nPerfilesTablero+0].y);
						glVertex3f(vertices_ply_3f[i*nPerfilesTablero+j].x,vertices_ply_3f[i*nPerfilesTablero+j].y,vertices_ply_3f[i*nPerfilesTablero+j].z);



						glNormal3f(normales_vertices[i*nPerfilesTablero+(j+1)].x,normales_vertices[i*nPerfilesTablero+(j+1)].y,normales_vertices[i*nPerfilesTablero+(j+1)].z);
						glTexCoord2f(coord_textura[0*nPerfilesTablero+(nPerfilesTablero-1)].x,coord_textura[0*nPerfilesTablero+(nPerfilesTablero-1)].y);
						glVertex3f(vertices_ply_3f[i*nPerfilesTablero+(j+1)].x,vertices_ply_3f[i*nPerfilesTablero+(j+1)].y,vertices_ply_3f[i*nPerfilesTablero+(j+1)].z);
						


						glNormal3f(normales_vertices[(i+1)*nPerfilesTablero+j].x,normales_vertices[(i+1)*nPerfilesTablero+j].y,normales_vertices[(i+1)*nPerfilesTablero+j].z);
						glTexCoord2f(coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+0].x,coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+0].y);
						glVertex3f(vertices_ply_3f[(i+1)*nPerfilesTablero+j].x,vertices_ply_3f[(i+1)*nPerfilesTablero+j].y,vertices_ply_3f[(i+1)*nPerfilesTablero+j].z);


						//CARA SUPERIOR
						glNormal3f(normales_vertices[i*nPerfilesTablero+(j+1)].x,normales_vertices[i*nPerfilesTablero+(j+1)].y,normales_vertices[i*nPerfilesTablero+(j+1)].z);
						glTexCoord2f(coord_textura[0*nPerfilesTablero+(nPerfilesTablero-1)].x,coord_textura[0*nPerfilesTablero+(nPerfilesTablero-1)].y);
						glVertex3f(vertices_ply_3f[i*nPerfilesTablero+(j+1)].x,vertices_ply_3f[i*nPerfilesTablero+(j+1)].y,vertices_ply_3f[i*nPerfilesTablero+(j+1)].z);
						


						glNormal3f(normales_vertices[(i+1)*nPerfilesTablero+j].x,normales_vertices[(i+1)*nPerfilesTablero+j].y,normales_vertices[(i+1)*nPerfilesTablero+j].z);
						glTexCoord2f(coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+0].x,coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+0].y);
						glVertex3f(vertices_ply_3f[(i+1)*nPerfilesTablero+j].x,vertices_ply_3f[(i+1)*nPerfilesTablero+j].y,vertices_ply_3f[(i+1)*nPerfilesTablero+j].z);



						glNormal3f(normales_vertices[(i+1)*nPerfilesTablero+(j+1)].x,normales_vertices[(i+1)*nPerfilesTablero+(j+1)].y,normales_vertices[(i+1)*nPerfilesTablero+(j+1)].z);
						glTexCoord2f(coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+(nPerfilesTablero-1)].x,coord_textura[(nPerfilesTablero-1)*nPerfilesTablero+(nPerfilesTablero-1)].y);
						glVertex3f(vertices_ply_3f[(i+1)*nPerfilesTablero+(j+1)].x,vertices_ply_3f[(i+1)*nPerfilesTablero+(j+1)].y,vertices_ply_3f[(i+1)*nPerfilesTablero+(j+1)].z);
						

					}
				}

				if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
					cambiarColor();
				}
				
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
		}

		void modelarCubo(){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(-0.5,-0.5,0.5)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,0.5));
			vertices_ply_3f.push_back(_vertex3f(-0.5,0.5,0.5));
			vertices_ply_3f.push_back(_vertex3f(0.5,0.5,0.5));
			vertices_ply_3f.push_back(_vertex3f(-0.5,-0.5,-0.5));
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,-0.5));
			vertices_ply_3f.push_back(_vertex3f(-0.5,0.5,-0.5));
			vertices_ply_3f.push_back(_vertex3f(0.5,0.5,-0.5)); //vertices[7]
			caras_ply_3i.push_back(_vertex3i(0,1,3));
			caras_ply_3i.push_back(_vertex3i(0,3,2));
			caras_ply_3i.push_back(_vertex3i(1,5,7));
			caras_ply_3i.push_back(_vertex3i(1,7,3));
			caras_ply_3i.push_back(_vertex3i(5,4,6));
			caras_ply_3i.push_back(_vertex3i(5,6,7));
			caras_ply_3i.push_back(_vertex3i(4,0,2));
			caras_ply_3i.push_back(_vertex3i(4,2,6));
			caras_ply_3i.push_back(_vertex3i(4,5,1));
			caras_ply_3i.push_back(_vertex3i(4,1,0));
			caras_ply_3i.push_back(_vertex3i(2,3,7));
			caras_ply_3i.push_back(_vertex3i(2,7,6));
			setOriginalVertex();
			calcularNormales();
		}

		void modelarCono(int nveces, float angulo_final){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(0,0.5,0)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,0));
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
			calcularNormales();
		}

		void modelarCilindro(int nveces, float angulo_final){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(0.5,0.5,0)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,0));
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
			calcularNormales();
		}

		void modelarEsfera(){
			vertices_ply_3f.clear();
			for(int i=89;i>0;i--){
				vertices_ply_3f.push_back(_vertex3f(cos(i*PI/180),sin(i*PI/180),0));
			}

			for(int i=0;i<90;i++){
				vertices_ply_3f.push_back(_vertex3f(cos(i*PI/180),-sin(i*PI/180),0));
			}

			revolucion(360, 2*PI);
			setRevolutionVertex();
			calcularNormales();
		}

		vector<_vertex3i>& getCaras(){
			return *caras;
		}

		vector<_vertex3f>& getVertices(){
			return *vertices;
		}

		vector<_vertex3f>& getNormalesCaras(){
			return normales_caras;
		}

		vector<_vertex3f>& getNormalesVertices(){
			return normales_vertices;
		}

		void calcularNormales(){
			_vertex3f v1,v2,vn;
			for(int i=0;i<(*caras).size();i++){
				v1.x=(*vertices)[(*caras)[i]._1].x-(*vertices)[(*caras)[i]._0].x;
				v1.y=(*vertices)[(*caras)[i]._1].y-(*vertices)[(*caras)[i]._0].y;
				v1.z=(*vertices)[(*caras)[i]._1].z-(*vertices)[(*caras)[i]._0].z;
			
				v2.x=(*vertices)[(*caras)[i]._2].x-(*vertices)[(*caras)[i]._0].x;
				v2.y=(*vertices)[(*caras)[i]._2].y-(*vertices)[(*caras)[i]._0].y;
				v2.z=(*vertices)[(*caras)[i]._2].z-(*vertices)[(*caras)[i]._0].z;

				vn=v1.cross_product(v2);

				normales_caras.push_back(vn.normalize());
			}

			_vertex3f normal=_vertex3f(0,0,0);
			for(int i=0;i<(*vertices).size();i++)
				normales_vertices.push_back(normal);

			for(int i=0;i<(*caras).size();i++){
				normales_vertices[(*caras)[i]._0]+=normales_caras[i];
				normales_vertices[(*caras)[i]._1]+=normales_caras[i];
				normales_vertices[(*caras)[i]._2]+=normales_caras[i];
			}

			for(int i=0;i<normales_vertices.size();i++){
				normales_vertices[i]=normales_vertices[i].normalize();
			}
		}

		void draw_points(int grosor){
			resetColors();
			glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
			glColor3f(*r,*g,*b);
			glBegin(GL_POINTS);
			for(int i=0; i<(*vertices).size();i++){
				glVertex3f((*vertices)[i].x,(*vertices)[i].y,(*vertices)[i].z);
			}
			glEnd();
		}


		void dibujar(int grosor, bool ajedrez){
			if((*vertices).size()>=1 && (*caras).size()>=1){
				resetColors();
				glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
				glColor3f(*r,*g,*b);						//Cambio el color a lo que está seleccionado (puede cambiar, es una inicialización)
				glBegin(GL_TRIANGLES);	
				//Rastreo el vector de caras para ir dibujandolos
				for(int i=0; i<(*caras).size();i++){
					glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
					glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
					glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
					if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
						cambiarColor();
					}
				}
				glEnd();
			}
		}



		void dibujarSuavizadoPlano(int grosor, bool ajedrez){

			if((*vertices).size()>=1 && (*caras).size()>=1){
				if(textura=="NONE"){
					//cout<<"Dibujo suav. plano sin textura, textura = "<<textura<<endl;
					resetColors();
					glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
					glColor3f(*r,*g,*b);						//Cambio el color a lo que está seleccionado (puede cambiar, es una inicialización)
					glBegin(GL_TRIANGLES);	
					//Rastreo el vector de caras para ir dibujandolos
					glShadeModel(GL_FLAT);
					for(int i=0; i<(*caras).size();i++){
						glNormal3f(normales_caras[i].x,normales_caras[i].y,normales_caras[i].z);
						glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
						glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
						glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
						if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
							cambiarColor();
						}
					}
					glEnd();
				}else{
					//cout<<"Dibujo suav. plano con textura, textura = "<<textura<<endl;
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

					glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);

					//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); 
					glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);// Para que afecte la luz a la textura


					resetColors();
					glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
					glColor3f(*r,*g,*b);
					glEnable(GL_TEXTURE_2D);						
					glBegin(GL_TRIANGLES);
					glShadeModel(GL_SMOOTH);
					//Rastreo el vector de caras para ir dibujandolos
					for(int i=0; i<(*caras).size();i++){
						
						glNormal3f(normales_caras[i].x,normales_caras[i].y,normales_caras[i].z);

						glTexCoord2f(coord_textura[(*caras)[i]._0].x,coord_textura[(*caras)[i]._0].y);
						glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
						
						
						glTexCoord2f(coord_textura[(*caras)[i]._1].x,coord_textura[(*caras)[i]._1].y);
						glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
						
						glTexCoord2f(coord_textura[(*caras)[i]._2].x,coord_textura[(*caras)[i]._2].y);
						glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
						
						if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
							cambiarColor();
						}
					}
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
			}
		}


		void dibujarSuavizadoGouraud(int grosor, bool ajedrez){

			if((*vertices).size()>=1 && (*caras).size()>=1){
				if(textura=="NONE"){
					//cout<<"Dibujo gouraud sin textura, textura = "<<textura<<endl;
					resetColors();
					glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
					glColor3f(*r,*g,*b);						//Cambio el color a lo que está seleccionado (puede cambiar, es una inicialización)
					glBegin(GL_TRIANGLES);	
					//Rastreo el vector de caras para ir dibujandolos
					glShadeModel(GL_SMOOTH);
					for(int i=0; i<(*caras).size();i++){
						glNormal3f(normales_vertices[(*caras)[i]._0].x,normales_vertices[(*caras)[i]._0].y,normales_vertices[(*caras)[i]._0].z);
						glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
						glNormal3f(normales_vertices[(*caras)[i]._1].x,normales_vertices[(*caras)[i]._1].y,normales_vertices[(*caras)[i]._1].z);
						glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
						glNormal3f(normales_vertices[(*caras)[i]._2].x,normales_vertices[(*caras)[i]._2].y,normales_vertices[(*caras)[i]._2].z);
						glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
						if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
							cambiarColor();
						}
					}
					glEnd();
				}else{
					//cout<<"Dibujo gouraud con textura, textura = "<<textura<<endl;
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
					glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

					glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);

					//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); 
					glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);// Para que afecte la luz a la textura

					resetColors();
					glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
					glColor3f(*r,*g,*b);
					glEnable(GL_TEXTURE_2D);						
					glBegin(GL_TRIANGLES);
					glShadeModel(GL_SMOOTH);
					//Rastreo el vector de caras para ir dibujandolos
					for(int i=0; i<(*caras).size();i++){
						
						glNormal3f(normales_vertices[(*caras)[i]._0].x,normales_vertices[(*caras)[i]._0].y,normales_vertices[(*caras)[i]._0].z);
						glTexCoord2f(coord_textura[(*caras)[i]._0].x,coord_textura[(*caras)[i]._0].y);
						glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
						
						glNormal3f(normales_vertices[(*caras)[i]._1].x,normales_vertices[(*caras)[i]._1].y,normales_vertices[(*caras)[i]._1].z);
						glTexCoord2f(coord_textura[(*caras)[i]._1].x,coord_textura[(*caras)[i]._1].y);
						glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
						
						glNormal3f(normales_vertices[(*caras)[i]._2].x,normales_vertices[(*caras)[i]._2].y,normales_vertices[(*caras)[i]._2].z);
						glTexCoord2f(coord_textura[(*caras)[i]._2].x,coord_textura[(*caras)[i]._2].y);
						glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
						
						if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
							cambiarColor();
						}
					}
					glEnd();
					glDisable(GL_TEXTURE_2D);
					
				}
			}
		}


		void dibujarConNombres(int grosor, bool ajedrez){
			glInitNames();
			glPushName(0);
			if((*vertices).size()>=1 && (*caras).size()>=1){
				resetColors();
				glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
				glColor3f(*r,*g,*b);						//Cambio el color a lo que está seleccionado (puede cambiar, es una inicialización)
				glBegin(GL_TRIANGLES);	
				//Rastreo el vector de caras para ir dibujandolos
				for(int i=0; i<(*caras).size();i++){
					glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
					glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
					glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
					if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
						cambiarColor();
					}
				}
				glEnd();
			}
		}

		void dibujarSeleccion(GLubyte r,GLubyte g,GLubyte b){
			glColor3ub(r,g,b);
			if((*vertices).size()>=1 && (*caras).size()>=1){
				glBegin(GL_TRIANGLES);	
				//Rastreo el vector de caras para ir dibujandolos
				for(int i=0; i<(*caras).size();i++){
					glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
					glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
					glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
				}
				glEnd();
			}
		}


		/*void dibujarTextura(int grosor, bool ajedrez){
			if(vertices_ply_3f_r.size()>0){

				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);

				//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); 
				glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);// Para que afecte la luz a la textura

				if((*vertices).size()>=1 && (*caras).size()>=1){
					resetColors();
					glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
					glColor3f(*r,*g,*b);
					glEnable(GL_TEXTURE_2D);						
					glBegin(GL_TRIANGLES);
					glShadeModel(GL_SMOOTH);
					//Rastreo el vector de caras para ir dibujandolos
					for(int i=0; i<(*caras).size();i++){
						
						glNormal3f(normales_vertices[(*caras)[i]._0].x,normales_vertices[(*caras)[i]._0].y,normales_vertices[(*caras)[i]._0].z);
						glTexCoord2f(coord_textura[(*caras)[i]._0].x,coord_textura[(*caras)[i]._0].y);
						glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
						
						glNormal3f(normales_vertices[(*caras)[i]._1].x,normales_vertices[(*caras)[i]._1].y,normales_vertices[(*caras)[i]._1].z);
						glTexCoord2f(coord_textura[(*caras)[i]._1].x,coord_textura[(*caras)[i]._1].y);
						glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
						
						glNormal3f(normales_vertices[(*caras)[i]._2].x,normales_vertices[(*caras)[i]._2].y,normales_vertices[(*caras)[i]._2].z);
						glTexCoord2f(coord_textura[(*caras)[i]._2].x,coord_textura[(*caras)[i]._2].y);
						glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
						
						if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
							cambiarColor();
						}
					}
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
			}
		}*/



		

		void cambiarColor(){
			if(r==&r1 && g==&g1 && b==&b1){	//Si el color seleccionado es el primario
				r=&r2;g=&g2;b=&b2;				//Seleccionamos el secundario
			}else{							//Si no,
				r=&r1;g=&g1;b=&b1;				//Seleccionamos el primario
			}
			glColor3f(*r,*g,*b);			//Cambiamos el color para la siguiente visualización.
		}
		
		void resetColors(){
			r=&r1;g=&g1;b=&b1;
		}

		void setOriginalVertex(){
			vertices=&vertices_ply_3f;
			caras=&caras_ply_3i;
		}

		void setRevolutionVertex(){
			vertices=&vertices_ply_3f_r;
			caras=&caras_ply_3i_r;
		}

		void setSweepVertex(){	//Vertices por barrido
			vertices=&vertices_ply_3f_b;
			caras=&caras_ply_3i_b;	
		}

		void setTextura(string tex){
			pimg=new jpg::Imagen(tex);
			tamx = pimg->tamX();
			tamy = pimg->tamY();
			texels = pimg->leerPixels();
			textura=tex;

			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); // Para que la textura tenga el color de la imagen
		}

		void resetTextura(){textura="NONE";}


		//---------------------------------------------------LUCES Y MATERIAL-----------------------------------------

		/*void setComponenteDifusaMaterial(float a, float b, float c, float d){material.setComponenteDifusa(a,b,c,d);}
		void setComponenteEspecularMaterial(float a, float b, float c, float d){material.setComponenteEspecular(a,b,c,d);}
		void setComponenteAmbientalMaterial(float a, float b, float c, float d){material.setComponenteAmbiental(a,b,c,d);}
		void setComponenteBrilloMaterial(float brillo){material.setComponenteBrillo(brillo);}

		void aplicarMaterial(){material.aplicarMaterial();}

		void habilitarColorFigura(){material.habilitarColor();}	*/

		void setMaterialAmbient(float a,float b,float c, float d){material_ambient[0]=a;material_ambient[1]=b;material_ambient[2]=c;material_ambient[3]=d;}
		void setMaterialDifuse(float a,float b,float c, float d){material_difuse[0]=a;material_difuse[1]=b;material_difuse[2]=c;material_difuse[3]=d;}
		void setMaterialSpecular(float a,float b,float c, float d){material_specular[0]=a;material_specular[1]=b;material_specular[2]=c;material_specular[3]=d;}
		void setMaterialShininess(float a){material_shininess[0]=a;}
		void aplicarMaterial(int ambient,int difuse,int specular,int shininess){
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_difuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
		}

		void resetMaterial(){
			material_ambient[0]=0.2;material_ambient[1]=0.2;material_ambient[2]=0.2;material_ambient[3]=1.0;
			material_difuse[0]=0.8;material_difuse[1]=0.8;material_difuse[2]=0.8;material_difuse[3]=1.0;
			material_specular[0]=0;material_specular[1]=0;material_specular[2]=0;material_specular[3]=1;
			material_shininess[0]=0;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_difuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
		}

		
};

#endif