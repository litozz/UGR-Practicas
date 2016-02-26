//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************
#define PI 3.14159265

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
/*MI CODIGO*/
#include <math.h>
#include <vector>
#include "vertex.h"
#include <iostream>
#include "file_ply_stl.h"
#include <math.h> //seno, coseno...

using namespace std;

/*PUNTEROS QUE APUNTAN A LOS VERTICES, ARISTAS Y TRIANGULOS SELECCIONADOS ACTUALMENTE*/
vector<_vertex3f>* vertices;
vector<_vertex3i>* caras;

float rprim=1.0f,gprim=0.0f,bprim=0.0f;		//Color 1 cubo 		MORADO
float rsec=0.0f,gsec=1.0f,bsec=0.0f;		//Color 2 cubo 		AZUL (Sólo se ve en modo ajedrez)

float *r1=&rprim,*g1=&gprim,*b1=&bprim; 		//Color primario seleccionado. Requiere inicialización.
float *r2=&rsec,*g2=&gsec,*b2=&bsec; 		//Color secundario seleccionado. Requiere inicialización.
float *r=r1,*g=g1,*b=b1;				   		//Color seleccionado actualmente (primario o secundario). Requiere inicialización. 

bool ajedrez=false;
int grosor=2;

/*PRACTICA 2*/

_file_ply ply;

vector<_vertex3f> vertices_ply_3f_hormiga;
vector<_vertex3i> caras_ply_3i_hormiga;

vector<_vertex3f> vertices_ply_3f_beethoven;
vector<_vertex3i> caras_ply_3i_beethoven;

vector<_vertex3f> vertices_ply_3f_dodge;
vector<_vertex3i> caras_ply_3i_dodge;

vector<_vertex3f> vertices_ply_3f_perfil;
vector<_vertex3i> caras_ply_3i_perfil;

vector<_vertex3f> vertices_ply_3f_solido_rev;
vector<_vertex3i> caras_ply_3i_solido_rev;

vector<_vertex3f> vertices_ply_3f_cilindro;
vector<_vertex3i> caras_ply_3i_cilindro;
vector<_vertex3f> vertices_ply_3f_cilindro_rev;
vector<_vertex3i> caras_ply_3i_cilindro_rev;

vector<_vertex3f> vertices_ply_3f_cono;
vector<_vertex3i> caras_ply_3i_cono;
vector<_vertex3f> vertices_ply_3f_cono_rev;
vector<_vertex3i> caras_ply_3i_cono_rev;

vector<_vertex3f> vertices_ply_3f_mod;
vector<_vertex3i> caras_ply_3i_mod;
vector<_vertex3f> vertices_ply_3f_mod_barrido;
vector<_vertex3i> caras_ply_3i_mod_barrido;
/**/


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void cambiarColor(){
	if(r==r1 && g==g1 && b==b1){	//Si el color seleccionado es el primario
		r=r2;g=g2;b=b2;				//Seleccionamos el secundario
	}else{							//Si no,
		r=r1;g=g1;b=b1;				//Seleccionamos el primario
	}
	glColor3f(*r,*g,*b);			//Cambiamos el color para la siguiente visualización.
}

/*void dibujarPuntos(vector<_vertex3f> v){
	//Rastreo el vector de caras para ir dibujandolos
	glBegin(GL_POINTS);
	for(int i=0; i<v.size();i++){
		glVertex3f(v[i].x,v[i].y,v[i].z);
	}
	glEnd();
}*/



void dibujar(){
	//Selecciono el color primario actual
	r=r1;g=g1;b=b1;
	//Cambio el color para dibujar
	glColor3f(*r,*g,*b);
	//Rastreo el vector de caras para ir dibujandolos
	for(int i=0; i<(*caras).size();i++){
		glVertex3f((*vertices)[(*caras)[i]._0].x,(*vertices)[(*caras)[i]._0].y,(*vertices)[(*caras)[i]._0].z);
		glVertex3f((*vertices)[(*caras)[i]._1].x,(*vertices)[(*caras)[i]._1].y,(*vertices)[(*caras)[i]._1].z);
		glVertex3f((*vertices)[(*caras)[i]._2].x,(*vertices)[(*caras)[i]._2].y,(*vertices)[(*caras)[i]._2].z);
		if(ajedrez){//Si el modo ajedrez está activado, voy a intercambiar el color primario por el secundario y viceversa.
			cambiarColor();
		}
	}
}
void draw_objects()
{
	glPointSize(grosor);						//Cambio el grosor a lo que diga la variable global.
	glColor3f(*r,*g,*b);						//Cambio el color a lo que está seleccionado (puede cambiar, es una inicialización)
	glBegin(GL_TRIANGLES);						//Le digo a OpenGL que voy a dibujar triangulos
		dibujar();							//Dibujo la figura que haya definido con la función normal_keys()
	glEnd();
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

/*void loadPly(char * archivoply, vector<_vertex3f>& vertices_ply_3f, vector<_vertex3i>& caras_ply_3i){
	vector<float> vertices_ply;
	vector<int> caras_ply;

	vertices_ply_3f.clear();
	caras_ply_3i.clear();

	ply.open(archivoply);
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
}*/

void revolucion(int nveces, const vector<_vertex3f>& vertices_ply_3f, const vector<_vertex3i>& caras_ply_3i, 
				vector<_vertex3f>& vertices_ply_3f_r, vector<_vertex3i>& caras_ply_3i_r){
	//REVOLUCION DE VERTICES
	_vertex3f punto_primo;
	
	float inicio=(2*PI)/nveces;
	//Copio el contenido de los vértices el los vértices del revolucionado
	vertices_ply_3f_r.clear();
	for(int i=vertices_ply_3f.size()/2-1;i<vertices_ply_3f.size();i++){vertices_ply_3f_r.push_back(vertices_ply_3f[i]);}

	int numPutosPerfil=vertices_ply_3f_r.size();

	for(int i=1;i<nveces;i++){//Recorro las divisiones
		for(int j=0;j<numPutosPerfil;j++){//Recorro los puntos
			punto_primo.x=vertices_ply_3f_r[j].x*cos(inicio*i)+vertices_ply_3f_r[j].z*sin(inicio*i);
			punto_primo.y=vertices_ply_3f_r[j].y;
			punto_primo.z=-vertices_ply_3f_r[j].x*sin(inicio*i)+vertices_ply_3f_r[j].z*cos(inicio*i);
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

	
	if(	centro_inferior.x!=vertices_ply_3f_r[0].x || 
		centro_inferior.y!=vertices_ply_3f_r[0].y || 
		centro_inferior.z!=vertices_ply_3f_r[0].z){ //Este if es para no replicar los puntos que ya se encuentran en el eje Y.
		for(int i=0;i<nveces;i++){
			caraActual.x=index_cent_inf;
			caraActual.y=(i%nveces)*numPutosPerfil;
			caraActual.z=((i+1)%nveces)*numPutosPerfil;
			caras_ply_3i_r.push_back(caraActual);
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


void barrido(int x, int y, int z,
	const vector<_vertex3f>& vertices_mod, const vector<_vertex3i>& caras_mod, 
	vector<_vertex3f>& vertices_mod_b, vector<_vertex3i>& caras_mod_b){

	for(int i=0;i<vertices_mod.size();i++){vertices_mod_b.push_back(vertices_mod[i]);}

	_vertex3f punto;
	for(int i=0;i<vertices_mod.size();i++){
		punto.x=vertices_mod[i].x+(x);
		punto.y=vertices_mod[i].y+(y);
		punto.z=vertices_mod[i].z+(z);
		vertices_mod_b.push_back(punto);
	}
	
	caras_mod_b.clear();
	
	_vertex3i caraActual;
	for(int i=0;i<2;i++){ //Recorro las divisiones de la circunferencia
		for(int j=0;j<vertices_mod.size();j++){ //Recorro cada punto del perfil de esa división.

/* HAGO MODULO EN J PORQUE ES NECESARIO QUE EL ULTIMO PUNTO DEL PERFIL SE UNA CON EL PRIMERO, A DIFERENCIA DE REVOLUCIÓN */

			//VOY A HACER MODULO (%) PARA CONSEGUIR UNA ESTRUCTURA CIRCULAR, ES DECIR, QUE EL PRIMER PERFIL Y EL ULTIMO SEAN EL MISMO.
			//Triangulos Pares
			caraActual.x=(j%vertices_mod.size());
			caraActual.y=vertices_mod.size()+(j%vertices_mod.size());
			caraActual.z=vertices_mod.size()+((j+1)%vertices_mod.size());
			caras_mod_b.push_back(caraActual);
			//Triangulos Impares
			caraActual.x=(j%vertices_mod.size());
			caraActual.y=vertices_mod.size()+((j+1)%vertices_mod.size());
			caraActual.z=((j+1)%vertices_mod.size());
			caras_mod_b.push_back(caraActual);
		}
	}

	//Le pongo las tapas; Hago dos bucles independientes para que se distinga el modo ajedrez en ambas tapas
	_vertex3f centro;
	centro.x=0; centro.y=0; centro.z=0;
	vertices_mod_b.push_back(centro);
	int index_cent_sup=vertices_mod_b.size()-1;

	for(int i=0;i<vertices_mod.size();i++){
		caraActual.x=index_cent_sup;
		caraActual.y=(vertices_mod.size()+(i+1))%vertices_mod.size();
		caraActual.z=(vertices_mod.size()+(i+2))%vertices_mod.size();
		caras_mod_b.push_back(caraActual);
	}

	centro.x=x; centro.y=y; centro.z=z;
	vertices_mod_b.push_back(centro);
	index_cent_sup=vertices_mod_b.size()-1;

	for(int i=0;i<vertices_mod.size();i++){
		caraActual.x=index_cent_sup;
		caraActual.y=vertices_mod.size()+((vertices_mod.size()+(i+1))%vertices_mod.size());
		caraActual.z=vertices_mod.size()+((vertices_mod.size()+(i+2))%vertices_mod.size());
		caras_mod_b.push_back(caraActual);
	}
}

void modelarCilindro(){
	vertices_ply_3f_cilindro.clear();
	vertices_ply_3f_cilindro.push_back(_vertex3f(1,1,0));
	vertices_ply_3f_cilindro.push_back(_vertex3f(1,-1,0));
}

void modelarCono(){
	vertices_ply_3f_cono.clear();
	vertices_ply_3f_cono.push_back(_vertex3f(0,1,0));
	vertices_ply_3f_cono.push_back(_vertex3f(1,-1,0));
}

void modelarCuadrado(){
	vertices_ply_3f_mod.clear();
	vertices_ply_3f_mod.push_back(_vertex3f(-0.5,-0.5,0));
	vertices_ply_3f_mod.push_back(_vertex3f(0.5,-0.5,0));
	vertices_ply_3f_mod.push_back(_vertex3f(0.5,0.5,0));
	vertices_ply_3f_mod.push_back(_vertex3f(-0.5,0.5,0));
}

void normal_keys(unsigned char Tecla1,int x,int y)
{
/*
La modificación de esta funcion permite cambiar de figura 1->Hormiga; 2->Beethoven; 3->Coche
Como la visualización depende del modo, ésta funcion tambien permite cambiar el modo: P->puntos;L->Lineas;S->Sólido;A->Ajedrez
*/
	switch(toupper(Tecla1)){
		case '1'://Hormiga
			vertices=&vertices_ply_3f_hormiga;
			caras=&caras_ply_3i_hormiga;
			cout<<"Mostrando hormiga"<<endl;
			break;
		case '2'://Beethoven
			vertices=&vertices_ply_3f_beethoven;
			caras=&caras_ply_3i_beethoven;
			cout<<"Mostrando beethoven"<<endl;
			break;
		case '3'://big_dodge
			vertices=&vertices_ply_3f_dodge;
			caras=&caras_ply_3i_dodge;
			cout<<"Mostrando dodge"<<endl;
			break;
		case '4'://perfil  
			vertices=&vertices_ply_3f_perfil;
			caras=&caras_ply_3i_perfil;
			cout<<"Mostrando perfil"<<endl;
			break;
		case '5'://perfil con revolución  
			vertices=&vertices_ply_3f_solido_rev;
			caras=&caras_ply_3i_solido_rev;
			cout<<"Mostrando perfil por revolución"<<endl;
			break;
		case '6': //Cilindro
			vertices=&vertices_ply_3f_cilindro_rev;
			caras=&caras_ply_3i_cilindro_rev;
			cout<<"Mostrando cilindro por revolución"<<endl;
			break;
		case '7': //Cono
			vertices=&vertices_ply_3f_cono_rev;
			caras=&caras_ply_3i_cono_rev;
			cout<<"Mostrando cono por revolución"<<endl;
			break;
		case '8': //Cubo por barrido
			vertices=&vertices_ply_3f_mod_barrido;
			caras=&caras_ply_3i_mod_barrido;
			cout<<"Mostrando cubo por barrido"<<endl;
			break;
		case 'P': glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); ajedrez=false; break;	//Dibujar en modo puntos
		case 'L': glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); ajedrez=false; break;	//Dibujar en modo alambre	
		case 'S': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=false; break;	//Dibujar en modo sólido
		case 'A': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=true; break;	//Dibujar en modo ajedrez
		case 'Q': exit(0);
	}
	glutPostRedisplay();	//Actualizar la escena
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************



void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=0.5;
Window_height=0.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);

loadPly("ply/beethoven.ply", vertices_ply_3f_beethoven, caras_ply_3i_beethoven); //Cargo el PLY de beethoven en sus respectivos arrays
loadPly("ply/ant.ply", vertices_ply_3f_hormiga, caras_ply_3i_hormiga); //Cargo el PLY de la hormiga en sus respectivos arrays
loadPly("ply/big_dodge.ply", vertices_ply_3f_dodge, caras_ply_3i_dodge); //Cargo el PLY de dodge en sus respectivos arrays

//Cargo el PLY del perfil en sus respectivos arrays
loadPly("ply/perfil.ply", vertices_ply_3f_perfil, caras_ply_3i_perfil);
//Revoluciono el perfil anteriormente cargado en unos nuevos arrays
revolucion(6, vertices_ply_3f_perfil,caras_ply_3i_perfil, vertices_ply_3f_solido_rev, caras_ply_3i_solido_rev);

//Modelo un cono en unos arrays y lo revoluciono
modelarCono();
revolucion(1000,vertices_ply_3f_cono, caras_ply_3i_cono,vertices_ply_3f_cono_rev,caras_ply_3i_cono_rev);

//Modelo un cilindro en unos arrays y lo revoluciono
modelarCilindro();
revolucion(1000,vertices_ply_3f_cilindro, caras_ply_3i_cilindro,vertices_ply_3f_cilindro_rev,caras_ply_3i_cilindro_rev);

//Modelo un cuadrado en unos arrays y lo extiendo por barrido
modelarCuadrado();
barrido(5, 0, 5, vertices_ply_3f_mod, caras_ply_3i_mod, vertices_ply_3f_mod_barrido, caras_ply_3i_mod_barrido);

/*
A partir de ahora cambiar entre las distintas figuras es cuestion de cambiar los punteros a la figura que queramos mostrar.
Por ejemplo, pongo los punteros para que muestren beethoven al inicio. Las teclas para cambiar entre las distintas figuras son:
1 -> Hormiga
2 -> Beethoven
3 -> Dodge (coche)
4 -> Perfil del peón de ajedrez sin revolucionar
5 -> Perfil del peón de ajedrez revolucionado
6 -> Cilindro (cuadrado por revolución)
7 -> Cono (triángulo por revolución)
8 -> Cubo por barrido
*/

//Inicializo los punteros
vertices=&vertices_ply_3f_beethoven;
caras=&caras_ply_3i_beethoven;
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
