#ifndef __Figura_
#define __Figura_

#include "Dibujable.h"

class Figura : public virtual Dibujable{
	private:
		vector<_vertex3f> vertices_ply_3f;
		vector<_vertex3i> caras_ply_3i;

		vector<_vertex3f> vertices_ply_3f_r;
		vector<_vertex3i> caras_ply_3i_r;

		vector<_vertex3f> vertices_ply_3f_b;
		vector<_vertex3i> caras_ply_3i_b;

		vector<_vertex3f> *vertices;
		vector<_vertex3i> *caras;

		float r1=1.0f,g1=0.0f,b1=0.0f,r2=0.0f,g2=1.0f,b2=0.0f;

		float *r=&r1,*g=&g1,*b=&b1;

		void revolucion(int nveces, float angulo_final){
			//REVOLUCION DE VERTICES
			_vertex3f punto_primo;
			float inicio=angulo_final/nveces;
			//Copio el contenido de los vértices el los vértices del revolucionado
			vertices_ply_3f_r.clear();
			for(int i=0;i<vertices_ply_3f.size();i++){vertices_ply_3f_r.push_back(vertices_ply_3f[i]);}

			int numPutosPerfil=vertices_ply_3f_r.size();

			for(int i=1;i<nveces;i++){//Recorro las divisiones
				for(int j=0;j<numPutosPerfil;j++){//Recorro los puntos
					punto_primo.x=vertices_ply_3f[j].x*cos(inicio*i)+vertices_ply_3f[j].z*sin(inicio*i);
					punto_primo.y=vertices_ply_3f[j].y;
					punto_primo.z=-vertices_ply_3f[j].x*sin(inicio*i)+vertices_ply_3f[j].z*cos(inicio*i);
					vertices_ply_3f_r.push_back(punto_primo);
				}
			}

			//UNION DE LOS PUNTOS PARA FORMAR LAS CARAS (MATRIZ DE REVOLUCION)
			caras_ply_3i_r.clear(); //IMPORTANTISIMO: Borro las caras que hubiera antes para que no se dibujen cosas erróneas.
			
			_vertex3i caraActual;
			for(int i=0;i<nveces;i++){ //Recorro las divisiones de la circunferencia
				for(int j=0;j<numPutosPerfil-1;j++){ //Recorro cada punto del perfil de esa división.
					//VOY A HACER MODULO (%) PARA CONSEGUIR UNA ESTRUCTURA CIRCULAR, ES DECIR, QUE EL PRIMER PERFIL Y EL ULTIMO SEAN EL MISMO.
					//Triangulos Pares
					caraActual.x=(i%nveces)*numPutosPerfil+j;
					caraActual.y=((i+1)%nveces)*numPutosPerfil+j;
					caraActual.z=((i+1)%nveces)*numPutosPerfil+(j+1);
					caras_ply_3i_r.push_back(caraActual);
					//Triangulos Impares
					caraActual.x=(i%nveces)*numPutosPerfil+j;
					caraActual.y=((i+1)%nveces)*numPutosPerfil+(j+1);
					caraActual.z=(i%nveces)*numPutosPerfil+(j+1);
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
			centro_superior.x=0; centro_superior.y=vertices_ply_3f[numPutosPerfil-1].y; centro_superior.z=0;
			vertices_ply_3f.push_back(centro_superior);
			int index_cent_sup=vertices_ply_3f.size()-1;*/
			if(	centro_inferior.x!=vertices_ply_3f_r[0].x || 
				centro_inferior.y!=vertices_ply_3f_r[0].y || 
				centro_inferior.z!=vertices_ply_3f_r[0].z){ //Este if es para no replicar los puntos que ya se encuentran en el eje Y.
				for(int i=0;i<nveces;i++){
					caraActual.x=index_cent_inf;
					caraActual.y=(i%nveces)*numPutosPerfil;
					caraActual.z=((i+1)%nveces)*numPutosPerfil;
					caras_ply_3i_r.push_back(caraActual);

					/*caraActual.x=index_cent_sup;
					caraActual.y=(i%nveces)*numPutosPerfil+(numPutosPerfil-1);
					caraActual.z=((i+1)%nveces)*numPutosPerfil+(numPutosPerfil-1);
					caras_ply_3i.push_back(caraActual);*/
				}
			}

			
			_vertex3f centro_superior;
			centro_superior.x=0; centro_superior.y=vertices_ply_3f_r[numPutosPerfil-1].y; centro_superior.z=0;
			vertices_ply_3f_r.push_back(centro_superior);
			int index_cent_sup=vertices_ply_3f_r.size()-1;

			if(	centro_inferior.x!=vertices_ply_3f_r[numPutosPerfil-1].x || 
				centro_inferior.y!=vertices_ply_3f_r[numPutosPerfil-1].y || 
				centro_inferior.z!=vertices_ply_3f_r[numPutosPerfil-1].z){ //Este if es para no replicar los puntos que ya se encuentran en el eje Y.
				for(int i=0;i<nveces;i++){
					caraActual.x=vertices_ply_3f_r.size()-1;
					caraActual.y=(i%nveces)*numPutosPerfil+(numPutosPerfil-1);
					caraActual.z=((i+1)%nveces)*numPutosPerfil+(numPutosPerfil-1);
					caras_ply_3i_r.push_back(caraActual);
				}
			}
			cout<<"Se ha llamado a la funcion revolución."<<endl;
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
		
		Figura(){};

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
		}
		Figura(char* fichero, int nveces, float angulo_final){
			loadPly(fichero);
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
		}
		Figura(char* fichero, int nveces, float angulo_final, int x, int y, int z){
			loadPly(fichero);
			revolucion(nveces, angulo_final);
			barrido(x,y,z);
			setSweepVertex();
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
		}

		void modelarCono(int nveces, float angulo_final){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(0,0.5,0)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,0));
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
		}

		void modelarCilindro(int nveces, float angulo_final){
			vertices_ply_3f.clear();
			vertices_ply_3f.push_back(_vertex3f(0.5,0.5,0)); //vertices[0]
			vertices_ply_3f.push_back(_vertex3f(0.5,-0.5,0));
			revolucion(nveces, angulo_final);
			setRevolutionVertex();
		}

		vector<_vertex3i>& getCaras(){
			return *caras;
		}

		vector<_vertex3f>& getVertices(){
			return *vertices;
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


				
};

#endif