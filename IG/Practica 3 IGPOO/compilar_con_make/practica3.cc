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
#include <unistd.h>
//#include "Figura.h"
//#include "Barra.h"
//#include "Cubo_Barra.h"
//#include "Torre.h"
//#include "Brazo.h"
#include "Grua.h"
//#include "Punta.h"
//#include "Carro.h"

using namespace std;

bool ajedrez=false;
int grosor=2;
vector<Dibujable*> figuras;

//Figura beethoven("ply/beethoven.ply");
Figura hormiga("ply/ant.ply");
Figura perfil("ply/perfil.ply",1000, 2*PI);
//Figura big_dodge("ply/big_dodge.ply");

//Figura cubo;
//Figura tetraedro;
//Figura cilindro;
//Figura cono;
//Figura hexagono;

Grua grua;

int giro_dcha=0;
int giro_izda=0;
int avance_carro=0;
int retroceso_carro=0;
int baja_pluma=0;
int sube_pluma=0;
bool hecho=false;
bool modo_manual=true;
bool mod_jerarquico;

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

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
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

void draw_axis(){
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
void draw_objects(){
	for(int i=0;i<figuras.size();i++){
		figuras[i]->dibujar(grosor,ajedrez); //Herencia virtual Dibujable->Figura y Dibujable->Grua: Necesarios punteros.
	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void){
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

void change_window_size(int Ancho1,int Alto1){
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
void normal_keys(unsigned char Tecla1,int x,int y){
	switch(Tecla1){
		case '1'://Hormiga
			figuras.clear();
			figuras.push_back(&hormiga);
			cout<<"Mostrando hormiga"<<endl;
			mod_jerarquico=false;
			break;
		/*case '2'://Beethoven
			figuras.clear();
			figuras.push_back(&beethoven);
			cout<<"Mostrando beethoven"<<endl;
			mod_jerarquico=false;
			break;
		case '3'://big_dodge
			figuras.clear();
			figuras.push_back(&big_dodge);
			cout<<"Mostrando dodge"<<endl;
			mod_jerarquico=false;
			break;*/
		case '2'://perfil  
			figuras.clear();
			figuras.push_back(&perfil);
			cout<<"Mostrando perfil por revolución"<<endl;
			mod_jerarquico=false;
			break;
		/*case '5'://perfil con revolución  
			figuras.clear();
			figuras.push_back(&cilindro);
			cout<<"Mostrando cilindro por revolución"<<endl;
			mod_jerarquico=false;
			break;
		case '6': //Cilindro
			figuras.clear();
			figuras.push_back(&cono);
			cout<<"Mostrando cono por revolución"<<endl;
			mod_jerarquico=false;
			break;
		case '7': //Cono
			figuras.clear();
			figuras.push_back(&hexagono);
			cout<<"Mostrando hexagono por barrido"<<endl;
			mod_jerarquico=false;
			break;*/
		case '3': //Grua
			figuras.clear();
			figuras.push_back(&grua);
			//modo_manual=false;
			mod_jerarquico=true;
			cout<<"Mostrando el modelo jerárquico grúa"<<endl;
			break;

		case 'q':modo_manual=true;break;
		case 'w':modo_manual=false;break;
		case 'Z':if(modo_manual)grua.avanzarCarro();break;
		case 'z':if(modo_manual)grua.retrocederCarro();break;
		case 'x':if(modo_manual)grua.subirPlomo();break;
		case 'X':if(modo_manual)grua.bajarPlomo();break;
		case 'c':if(modo_manual)grua.girarBrazoDerecha();break;
		case 'C':if(modo_manual)grua.girarBrazoIzquierda();break;

		case 'p': glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); ajedrez=false; break;	//Dibujar en modo puntos
		case 'l': glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); ajedrez=false; break;	//Dibujar en modo alambre	
		case 's': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=false; break;	//Dibujar en modo sólido
		case 'a': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=true; break;	//Dibujar en modo ajedrez
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

void special_keys(int Tecla1,int x,int y){
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

void initialize(void){
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


	//cubo.modelarCubo();
	//tetraedro.modelarTetraedro();
	//cilindro.modelarCilindro(100,2*PI);//
	//cono.modelarCono(100,2*PI);//
	//hexagono.modelarHexagono(0,0,5);//

	figuras.push_back(&grua);
	mod_jerarquico=true;
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


void animar(void){
	if(!modo_manual && mod_jerarquico){ //Si se esta mostrando el modelo jerárquico en modo automatico
		if(giro_izda<180){
			grua.girarBrazoIzquierda();
			glutPostRedisplay();
			giro_izda++;
		}else if(avance_carro<50){
			grua.avanzarCarro();
			glutPostRedisplay();
			avance_carro++;
		}else if(baja_pluma<100){
			grua.bajarPlomo();
			glutPostRedisplay();
			baja_pluma++;
		}else if(sube_pluma<50){
			grua.subirPlomo();
			glutPostRedisplay();
			sube_pluma++;
		}else if(giro_dcha<180){
			grua.girarBrazoDerecha();
			glutPostRedisplay();
			giro_dcha++;
		}else if(retroceso_carro<30){
			grua.retrocederCarro();
			glutPostRedisplay();
			retroceso_carro++;
		}else if(sube_pluma<100){
			grua.bajarPlomo();
			glutPostRedisplay();
			sube_pluma++;
		}else if(sube_pluma>0){
			grua.subirPlomo();
			glutPostRedisplay();
			sube_pluma++;
			hecho=true;
		}
		if(hecho){
			giro_dcha=0;
			giro_izda=0;
			avance_carro=0;
			retroceso_carro=0;
			baja_pluma=0;
			sube_pluma=0;
			hecho=false;
			grua.resetPosicion();
			glutPostRedisplay();
			usleep(200000);
		}
	}
}


int main(int argc, char **argv){

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
	glutCreateWindow("Práctica 3");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	glutIdleFunc(animar);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}