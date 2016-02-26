//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
/*MI CODIGO*/
#include <math.h>
#include <vector>
#include "vertex.h"
#include <iostream>

using namespace std;

/*VECTORES COMUNES CUYOS DATOS SE RELLENAN EN INITIALIZE() (MODELADO)*/
vector<_vertex3f> verticesCubo(8);
vector<_vertex2i> aristasCubo(12);
vector<_vertex3i> triangulosCubo(12);
vector<_vertex3f> verticesTetra(4);
vector<_vertex2i> aristasTetra(6);
vector<_vertex3i> triangulosTetra(4);

/*PUNTEROS QUE APUNTAN A LOS VERTICES, ARISTAS Y TRIANGULOS SELECCIONADOS ACTUALMENTE*/
vector<_vertex3f>* vertices=&verticesCubo;
vector<_vertex2i>* aristas=&aristasCubo;
vector<_vertex3i>* triangulos=&triangulosCubo;

bool ajedrez=false;	//Permite el visualizado en modo ajedrez
bool los_dos=false; //Permite ver las dos figuras. En los modos Solido y Ajedrez no se aprecia
int grosor = 8;		//Grosor de los puntos (opcional)

float r1Cubo=1.0f,g1Cubo=0.0f,b1Cubo=0.0f;		//Color 1 cubo 		MORADO
float r2Cubo=0.0f,g2Cubo=1.0f,b2Cubo=0.0f;		//Color 2 cubo 		AZUL (Sólo se ve en modo ajedrez)
float r1Tetra=1.0f,g1Tetra=0.0f,b1Tetra=1.0f;	//Color 1 tetraedro ROJO 
float r2Tetra=0.0f,g2Tetra=0.0f,b2Tetra=1.0f;	//Color 2 tetraedro Verde (Sólo se ve en modo ajedrez)

float *r1=&r1Cubo,*g1=&g1Cubo,*b1=&b1Cubo; 		//Color primario seleccionado. Requiere inicialización.
float *r2=&r2Cubo,*g2=&g2Cubo,*b2=&b2Cubo; 		//Color secundario seleccionado. Requiere inicialización.
float *r=r1,*g=g1,*b=b1;				   		//Color seleccionado actualmente (primario o secundario). Requiere inicialización. 


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

void dibujar(){
	//Selecciono el color primario actual
	r=r1;g=g1;b=b1;
	//Cambio el color para dibujar
	glColor3f(*r,*g,*b);
	//Rastreo el vector de triangulos para ir dibujandolos
	for(int i=0; i<(*triangulos).size();i++){
		glVertex3f((*vertices)[(*triangulos)[i]._0].x,(*vertices)[(*triangulos)[i]._0].y,(*vertices)[(*triangulos)[i]._0].z);
		glVertex3f((*vertices)[(*triangulos)[i]._1].x,(*vertices)[(*triangulos)[i]._1].y,(*vertices)[(*triangulos)[i]._1].z);
		glVertex3f((*vertices)[(*triangulos)[i]._2].x,(*vertices)[(*triangulos)[i]._2].y,(*vertices)[(*triangulos)[i]._2].z);
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
		if(los_dos){							//Si quiero visualizar las dos figuras: 
			vertices=&verticesCubo;				//Los vértices que voy a utilizar son los del cubo
			aristas=&aristasCubo;				//Las aristas que voy a utilizar son las del cubo
			triangulos=&triangulosCubo;			//Los triángulos que voy a utilizar son los del cubo
			r1=&r1Cubo;g1=&g1Cubo;b1=&b1Cubo;	//El color primario que voy a utilizar es el color primario del cubo
			r2=&r2Cubo;g2=&g2Cubo;b2=&b2Cubo;	//El color secundario que voy a utilizar es el color secundario del cubo.
			dibujar();							//Dibujo el cubo
			
			vertices=&verticesTetra;			//Los vértices que voy a utilizar son los del tetraedro
			aristas=&aristasTetra;				//Las aristas que voy a utilizar son las del tetraedro
			triangulos=&triangulosTetra;		//Los triángulos que voy a utilizar son los del tetraedro
			r1=&r1Tetra;g1=&g1Tetra;b1=&b1Tetra;//El color primario que voy a utilizar es el color primario del tetraedro
			r2=&r2Tetra;g2=&g2Tetra;b2=&b2Tetra;//El color secundario que voy a utilizar es el color secundario del tetraedro.
			dibujar();							//Dibujo el tetraedro

		}else{									//No voy a dibujar las dos figuras. Sólo voy a dibujar una.
			dibujar();							//Dibujo la figura que haya definido con la función normal_keys()
		}
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

void normal_keys(unsigned char Tecla1,int x,int y)
{
/*
La modificación de esta funcion permite cambiar de figura 1->cubo; 2->tetraedro; 3->ambas
Como la visualización depende del modo, ésta funcion tambien permite cambiar el modo: P->puntos;L->Lineas;S->Sólido;A->Ajedrez
*/
	switch(toupper(Tecla1)){
		case '1'://Voy a dibujar el cubo
			//Actualizo vértices, aristas, triangulos y colores a los del cubo 
			vertices=&verticesCubo;
			aristas=&aristasCubo;
			triangulos=&triangulosCubo;
			r1=&r1Cubo;g1=&g1Cubo;b1=&b1Cubo;
			r2=&r2Cubo;g2=&g2Cubo;b2=&b2Cubo;
			r=r1;g=g1;b=b1;
			los_dos=false;	//Pongo los_dos a false porque solo voy a visualizar el cubo
			break;
		case '2'://Voy a dibujar el tetraedro
			//Actualizo vértices, aristas, triangulos y colores a los del tetraedro 
			vertices=&verticesTetra;
			aristas=&aristasTetra;
			triangulos=&triangulosTetra;
			r1=&r1Tetra;g1=&g1Tetra;b1=&b1Tetra;
			r2=&r2Tetra;g2=&g2Tetra;b2=&b2Tetra;
			r=r1;g=g1;b=b1;
			los_dos=false;	//Pongo los_dos a false porque solo voy a visualizar el tetraedro
			break;
		case '3'://Los dos  
			los_dos=true;
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
Window_width=5;
Window_height=5;
Front_plane=10;
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


	//MODELADO CUBO
	/* DEFINICIÓN DEL ORDEN DE NUMERACIÓN DE LOS VÉRTICES
		 V6 ________V7
		  /|      /|
		 /_|____ / |
	  V2|  |  V3|  |
		|  | _ _|_ |
		| /	V4 	| /V5
		|/______|/
		V0	 	V1
	*/
	//vector<_vertex3f> verticesCubo(8);
	verticesCubo[0]=_vertex3f(-3,-3,3);
	verticesCubo[1]=_vertex3f(3,-3,3);
	verticesCubo[2]=_vertex3f(-3,3,3);
	verticesCubo[3]=_vertex3f(3,3,3);
	verticesCubo[4]=_vertex3f(-3,-3,-3);
	verticesCubo[5]=_vertex3f(3,-3,-3);
	verticesCubo[6]=_vertex3f(-3,3,-3);
	verticesCubo[7]=_vertex3f(3,3,-3);
	/* DEFINICIÓN DEL ORDEN DE NUMERACIÓN DE LAS ARISTAS
		A0 -> V0-V1
		A1 -> V0-V2
		A2 -> V1-V3
		A3 -> V2-V3
		A4 -> V0-V4
		A5 -> V1-V5
		A6 -> V2-V6
		A7 -> V3-V7
		A8 -> V4-V5
		A9 -> V4-V6
		A10 -> V5-V7
		A11 -> V6-V7
	*/
	
	//vector<_vertex2i> aristasCubo(12);
	aristasCubo[0]._0=0;	aristasCubo[0]._1=1;
	aristasCubo[1]._0=0;	aristasCubo[1]._1=2;
	aristasCubo[2]._0=1;	aristasCubo[2]._1=3;
	aristasCubo[3]._0=2;	aristasCubo[3]._1=3;
	aristasCubo[4]._0=0;	aristasCubo[4]._1=4;
	aristasCubo[5]._0=1;	aristasCubo[5]._1=5;
	aristasCubo[6]._0=2;	aristasCubo[6]._1=6;
	aristasCubo[7]._0=3;	aristasCubo[7]._1=7;
	aristasCubo[8]._0=4;	aristasCubo[8]._1=5;
	aristasCubo[9]._0=4;	aristasCubo[9]._1=6;
	aristasCubo[10]._0=5;	aristasCubo[10]._1=7;
	aristasCubo[11]._0=6;	aristasCubo[11]._1=7;
	/* DEFINICIÓN DEL ORDEN DE NUMERACIÓN DE LOS TRIANGULOS
		Cara frontal:
		T0 -> V0-V2-V1
		T1 -> V3-V2-V1
		Cara izquierda:
		T2 -> V4-V0-V6
		T3 -> V2-V0-V6
		Cara derecha:
		T4 -> V1-V3-V5
		T5 -> V7-V3-V5
		Cara trasera:
		T6 -> V5-V7-V4
		T7 -> V6-V7-V4
		Cara inferior:
		T8 -> V4-V0-V5
		T9 -> V1-V0-V5
		Cara superior:
		T10 -> V6-V2-V7
		T11 -> V3-V2-V7
	*/
	
	//vector<_vertex3i> triangulosCubo(12);
	triangulosCubo[0]._0=0;		triangulosCubo[0]._1=2;		triangulosCubo[0]._2=1;
	triangulosCubo[1]._0=3;		triangulosCubo[1]._1=2;		triangulosCubo[1]._2=1;
	triangulosCubo[2]._0=4;		triangulosCubo[2]._1=0;		triangulosCubo[2]._2=6;
	triangulosCubo[3]._0=2;		triangulosCubo[3]._1=0;		triangulosCubo[3]._2=6;
	triangulosCubo[4]._0=1;		triangulosCubo[4]._1=3;		triangulosCubo[4]._2=5;
	triangulosCubo[5]._0=7;		triangulosCubo[5]._1=3;		triangulosCubo[5]._2=5;
	triangulosCubo[6]._0=5;		triangulosCubo[6]._1=7;		triangulosCubo[6]._2=4;
	triangulosCubo[7]._0=6;		triangulosCubo[7]._1=7;		triangulosCubo[7]._2=4;
	triangulosCubo[8]._0=4;		triangulosCubo[8]._1=0;		triangulosCubo[8]._2=5;
	triangulosCubo[9]._0=1;		triangulosCubo[9]._1=0;		triangulosCubo[9]._2=5;
	triangulosCubo[10]._0=6;	triangulosCubo[10]._1=2;	triangulosCubo[10]._2=7;
	triangulosCubo[11]._0=3;	triangulosCubo[11]._1=2;	triangulosCubo[11]._2=7;

	//MODELANDO TETRAEDRO

	//vector<_vertex3f> verticesTetra(4);
	verticesTetra[0]=_vertex3f(-3,-3,-3);
	verticesTetra[1]=_vertex3f(3,-3,3);
	verticesTetra[2]=_vertex3f(-3,3,3);
	verticesTetra[3]=_vertex3f(3,3,-3);


	//vector<_vertex2i> aristasTetra(12);
	aristasTetra[0]._0=0;	aristasTetra[0]._1=1;
	aristasTetra[1]._0=0;	aristasTetra[1]._1=2;
	aristasTetra[2]._0=0;	aristasTetra[2]._1=3;
	aristasTetra[3]._0=1;	aristasTetra[3]._1=2;
	aristasTetra[4]._0=1;	aristasTetra[4]._1=3;
	aristasTetra[5]._0=2;	aristasTetra[5]._1=3;

	
	//vector<_vertex3i> triangulosTetra(12);
	triangulosTetra[0]._0=0;		triangulosTetra[0]._1=1;		triangulosTetra[0]._2=2;
	triangulosTetra[1]._0=0;		triangulosTetra[1]._1=1;		triangulosTetra[1]._2=3;
	triangulosTetra[2]._0=0;		triangulosTetra[2]._1=2;		triangulosTetra[2]._2=3;
	triangulosTetra[3]._0=1;		triangulosTetra[3]._1=2;		triangulosTetra[3]._2=3;
	
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
glutCreateWindow("Práctica 1");

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
