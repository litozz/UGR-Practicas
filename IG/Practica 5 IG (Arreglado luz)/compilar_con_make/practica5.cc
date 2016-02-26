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
#include "Grua.h"
#include "Escena_lata_peones.h"
#include "Camara.h"

using namespace std;

bool ajedrez=false;
int grosor=2;
bool animacion=true;

vector<Dibujable*> figuras;

int modo_dibujado=0;

Figura beethoven("ply/beethoven.ply");
Figura hormiga("ply/ant.ply");
Figura perfil("ply/perfil.ply",1000, 2*PI);


Escena_Lata_Peones lata_peones;


Figura tablero;
Figura cubo;
Figura cilindro;

Grua grua;

Figura esfera;


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


enum modo{LIGHT,LIGHT_SMOOTH,TEXTURE_LIGHT,NONE};
modo current_mode=NONE;


/*Variables practica 5*/
Camara camara1;
vector<Camara> camaras;
int camaraActiva=0;
int tipocam=0;

float xant,yant;

typedef enum {parar_camara, mover_camara, mover_camara_first_person,select_objects} estadoRaton;

estadoRaton mouseStatus;

int objetoSeleccionado = 0;

GLfloat anterior_Window_width;
GLfloat anterior_Window_height;

bool cenital=false;
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
	const float ratioXY=(float)UI_window_width/(float)UI_window_height;
	switch(tipocam){
		case 0:glFrustum(-Window_width,Window_width,-Window_height/ratioXY,Window_height/ratioXY,Front_plane,Back_plane);break;
		case 1:glOrtho(-Window_width,Window_width,-Window_height/ratioXY,Window_height/ratioXY,Front_plane,Back_plane);break;
	}	
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);*/
	camaras[camaraActiva].setObserver();
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
	switch(modo_dibujado){
		case 0:
			current_mode=NONE;
			for(int i=0;i<figuras.size();i++){
				figuras[i]->dibujar(grosor,ajedrez); //Herencia virtual Dibujable->Figura y Dibujable->Grua: Necesarios punteros.
			}
			
			break;

		case 1: //suavizado plano
			current_mode=LIGHT;
			for(int i=0;i<figuras.size();i++){
				figuras[i]->dibujarSuavizadoPlano(grosor,ajedrez); 
			}
			
			break;
		case 2: //suavizado gouroud
			current_mode=LIGHT;
			for(int i=0;i<figuras.size();i++){
				figuras[i]->dibujarSuavizadoGouraud(grosor,ajedrez); 
			}
			
			break;

		case 4: //Textura
			current_mode=TEXTURE_LIGHT;
			for(int i=0;i<figuras.size();i++){
				figuras[i]->dibujarTableroTextura(grosor,ajedrez);
			}	
			break;
	}
		
}


void dibujarSeleccion(){
	glDisable(GL_LIGHTING);
	glDisable(GL_DITHER);
	figuras[0]->dibujarSeleccion(0,0,255);
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
	UI_window_width=Ancho1;
	UI_window_height=Alto1;
	glViewport(0,0,Ancho1,Alto1);
	change_projection();
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
			mod_jerarquico=false;
			modo_dibujado=1;
			break;

		case '2'://perfil  
			figuras.clear();
			perfil.setTextura("tex/text-madera.jpg");
			figuras.push_back(&perfil);
			mod_jerarquico=false;
			modo_dibujado=2;
			break;

		case '3': //Grua
			figuras.clear();
			figuras.push_back(&grua);
			mod_jerarquico=true;
			modo_dibujado=1;
			break;

		case '4': //Escena lata y peones
			figuras.clear();
			figuras.push_back(&lata_peones);
			mod_jerarquico=false;
			modo_dibujado=2;
			break;

		case '5': //Tablero
			figuras.clear();
			tablero.setTextura("tex/escaques4x4.jpg");
			figuras.push_back(&tablero);
			mod_jerarquico=false;
			modo_dibujado=4; //Textura
			break;

		case '6': //Bola del mundo
			figuras.clear();
			esfera.setTextura("tex/dia_8192.jpg");
			figuras.push_back(&esfera);
			mod_jerarquico=false;
			modo_dibujado=2; //Textura
			break;

		case '7':
			figuras.clear();
			cilindro.setTextura("tex/text-lata-1.jpg");
			figuras.push_back(&cilindro);
			mod_jerarquico=false;
			modo_dibujado=2; //Textura
			break;

		case 'q':modo_manual=true;break;
		case 'w':modo_manual=false;break;
		case 'Z':if(modo_manual)grua.avanzarCarro();break;
		case 'z':if(modo_manual)grua.retrocederCarro();break;
		case 'x':if(modo_manual)grua.subirPlomo();break;
		case 'X':if(modo_manual)grua.bajarPlomo();break;
		case 'c':if(modo_manual)grua.girarBrazoDerecha();break;
		case 'C':if(modo_manual)grua.girarBrazoIzquierda();break;

		case 'p': glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); ajedrez=false; modo_dibujado=0;break;//Dibujar en modo puntos
		case 'l': glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); ajedrez=false; modo_dibujado=0; break; //Dibujar en modo alambre	
		case 's': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=false; modo_dibujado=0; break; 	//Dibujar en modo sólido
		case 'a': glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); ajedrez=true; modo_dibujado=0; break; 	//Dibujar en modo ajedrez

		case '*':
			modo_dibujado=1;
			break;

		case '/':
			modo_dibujado=2;
			break;

		case 'E':
		case 'e':
			animacion=false;
			break;

		case 'R':
		case 'r':
			animacion=false;
			break;
		
		case 'T':
		case 't':
			animacion=true;
			break;

		/*CAMARA PRIMERA PERSONA*/

		case 'W':if(!cenital)camaras[camaraActiva].setObserver_desplaza_z_pos(0.5);break;
		case 'A':if(!cenital)camaras[camaraActiva].setObserver_desplaza_x_pos(0.5);break;
		case 'S':if(!cenital)camaras[camaraActiva].setObserver_desplaza_z_neg(0.5);break;
		case 'D':if(!cenital)camaras[camaraActiva].setObserver_desplaza_x_neg(0.5);break;

		//case 'q':
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
	case GLUT_KEY_LEFT:if(!cenital)camaras[camaraActiva].girar(0,-1);break;
	case GLUT_KEY_RIGHT:if(!cenital)camaras[camaraActiva].girar(0,1);break;
	case GLUT_KEY_UP:if(!cenital)camaras[camaraActiva].girar(-1,0);break;
	case GLUT_KEY_DOWN:if(!cenital)camaras[camaraActiva].girar(1,0);break;
	case GLUT_KEY_PAGE_UP:if(!cenital)camaras[camaraActiva].setObserver_distance_multiply(0.6);break;
	case GLUT_KEY_PAGE_DOWN:if(!cenital)camaras[camaraActiva].setObserver_distance_divide(0.6);break;
	case GLUT_KEY_F1:
		cenital=false;
		tipocam=0;
		change_projection();
		Window_height=anterior_Window_height;
		Window_width=anterior_Window_height;
		break;
	case GLUT_KEY_F2:
		cenital=true;
		tipocam=1;
		camaras[camaraActiva].girarDesdeOrigen(90,0);
		anterior_Window_width=Window_width;
		anterior_Window_height=Window_height;
		Window_width=Window_width*25;
		Window_height=Window_height*25;
		change_projection();
		break; 
	case GLUT_KEY_F3:
		cenital=false;
		tipocam=1;
		Window_height=anterior_Window_height;
		Window_width=anterior_Window_height;
		change_projection();
		break;
	}
	glutPostRedisplay();
}


// Funcion de incializacion de la luz
void set_light(){
	//definir luces
	GLfloat light_ambient[] 	= {0.7,0.7,0.7, 1.0};
	GLfloat light_difuse[] 		= {0.9, 0.9, 0.9, 1.0};
	GLfloat light_specular[] 	= {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] 	= {0, 0, 10.0, 1.0};//El ultimo parametro =1 es para luz posicional (fuente en un punto)

	//set lights
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//enable light0
	glEnable(GL_LIGHT0);


	//luz direccional
	GLfloat light_direction[] = {1,1,1,0};

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_direction);

	//enable light1
	glEnable(GL_LIGHT1);


	// definir materiales

	GLfloat material_ambient[]	= {0.2125,0.1275,0.054}; 	
	GLfloat material_difuse[]	= {0.714,0.4284,0.18144}; 	
	GLfloat material_specular[]	= {0.393548,0.271906,0.166721}; 	
	GLfloat material_shininess[]= {0.2};

	// set material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_difuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);


	//enable lighting
	glEnable(GL_LIGHTING);
}

void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Window_width=0.5;
	Window_height=0.5;
	Front_plane=1;
	Back_plane=1000;
	//Inicializo tambien los valores anteriores de Wh y Ww
	anterior_Window_height=Window_height;
	anterior_Window_width=Window_width;
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
	/*CREACION DE LAS LUCES*/
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	set_light();

	/*FIN CREACION LUCES*/
	cubo.modelarCubo();
	tablero.modelarTablero(2);
	esfera.modelarEsfera();
	cilindro.modelarCilindro(100,2*PI);//
	figuras.push_back(&tablero);
	camaras.push_back(camara1);

	
}




//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


void animar(void){
	if(animacion){
		//luz.moverUp();
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
				usleep(200000);
			}
		}
	}
	glutPostRedisplay();
}


/*FUNCION DE SELECCION*/

bool pick (int x, int y){
    bool result = false;
    GLint viewport[4];
    GLubyte pixel[3];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);
        
    //cout<<"("<<pixel[0]<<","<<pixel[1]<<","<<pixel[2]<<")"<<endl;

    if(figuras[0]->getNumFiguras()>1){ //Escena de la lata y los peones
    	if(pixel[0]==0){//Puede ser la lata, el peon de madera o el peon blanco
    		if(pixel[1]==0){//Es la lata
    			objetoSeleccionado=1;
    			result=true;
    			cout<<"Seleccionado: LATA"<<endl;
    		}else{//Es el peon de madera o el blanco
    			if(pixel[2]==0){//Es el peon de madera
    				objetoSeleccionado=2;
    				result=true;
    				cout<<"Seleccionado: PEON DE MADERA"<<endl;
    			}else{//Es el peon blanco
    				objetoSeleccionado=3;
    				result=true;
    				cout<<"Seleccionado: PEON BLANCO"<<endl;
    			}
    		}
    	}else{//Puede ser el peon negro, el tablero o nada
    		if(pixel[1]==0){
    			if(pixel[2]==0){//Es el peon negro
    				objetoSeleccionado=4;
    				result=true;
    				cout<<"Seleccionado: PEON NEGRO"<<endl;
    			}else{//Es el tablero
    				objetoSeleccionado=5;
    				result=true;
    				cout<<"Seleccionado: TABLERO"<<endl;
    			}
    		}else{//No se selecciona nada
    			objetoSeleccionado=0;
    			result=false;
    			cout<<"No se ha seleccionado nada."<<endl;
    		}
    	}
    }else{//Hay una figura sola
    	if(pixel[0]==0){//Hay figura
    		objetoSeleccionado=1;
    		result=true;
    		cout<<"Seleccionado: la única figura."<<endl;
    	}else{
    		objetoSeleccionado=0;
    		result=false;
    		cout<<"No se ha seleccionado nada."<<endl;
    	}
    }

    return result;
}


/*FUNCIONES DE MOVIMIENTO DE LA CAMARA CON EL RATON*/
void ratonMovido(int x, int y) {
	if(mouseStatus==mover_camara && !cenital){
    	camaras[camaraActiva].girar(y-yant,x-xant);
    	xant=x;
    	yant=y;
	}
}

void clickRaton(int boton, int estado, int x, int y) {
	if (boton == GLUT_RIGHT_BUTTON && !cenital) {
		if (estado == GLUT_DOWN) {
			mouseStatus=mover_camara;
			xant=x;
			yant=y;
		}else{
			mouseStatus=parar_camara;
		}
	}else  if (boton==3 && !cenital){// state = GLUT_DOWN
		if(tipocam==0)
			camaras[camaraActiva].setObserver_distance_divide(0.6);
		else if(tipocam==1){
			Window_width/=2;
			Window_height/=2;
			change_projection();
		}
	}else if (boton==4 && !cenital){
		if(tipocam==0)
			camaras[camaraActiva].setObserver_distance_multiply(0.6);
		else if(tipocam==1){
			Window_width*=2;
			Window_height*=2;
			change_projection();
		}
	}else if(boton==GLUT_LEFT_BUTTON){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		dibujarSeleccion();
		if (estado == GLUT_DOWN) {
			mouseStatus=select_objects;
			pick(x,y);
			glEnable(GL_DITHER);
			glEnable(GL_LIGHTING);
		}else{
			mouseStatus=parar_camara;
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
	glutCreateWindow("Práctica 5");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	glutIdleFunc(animar);

	/*FUNCIONES PARA MOVER LA CAMARA CON EL RATON*/
	glutMouseFunc(clickRaton);
	glutMotionFunc(ratonMovido);
	
	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}