#ifndef _CAMARA_
#define _CAMARA_
#include <GL/glut.h>

using namespace std;

class Camara{
	private: 
		GLfloat Observer_angle_x;
		GLfloat Observer_angle_y;
		GLfloat Observer_distance;

		GLfloat eye_x;
		GLfloat eye_y;
		GLfloat eye_z;

		GLfloat at_x;
		GLfloat at_y;
		GLfloat at_z;

		GLfloat up_x;
		GLfloat up_y;
		GLfloat up_z;

		void setLookAt(){
			glLoadIdentity();
			gluLookAt(	
				eye_x, eye_y, eye_z,
				at_x, at_y,  at_z,
				up_x, up_y,  up_z
			);
		}

	public:
		Camara(){
			Observer_angle_x = 0;
			Observer_angle_y = 0;

			eye_x = 0;	eye_y = 0; 	eye_z = 10;
			at_x = 0; 	at_y = 0;	at_z = 0;
			up_x = 0; 	up_y = 1;  	up_z = 0;

			setLookAt();
		}

		void girar(int x, int y){
			glRotatef(Observer_angle_x - x,1,0,0);
			glRotatef(Observer_angle_y - y,0,1,0);
			Observer_angle_x += x;
			Observer_angle_y += y;
		}

		void girarDesdeOrigen(int x, int y){
			Observer_angle_x=0;
			Observer_angle_y=0;
			glRotatef(Observer_angle_x - x,1,0,0);
			glRotatef(Observer_angle_y - y,0,1,0);
			Observer_angle_x += x;
			Observer_angle_y += y;	
		}

		void setObserver(){
			glTranslatef(eye_x,eye_y,-eye_z);
			glRotatef(Observer_angle_x,1,0,0);
			glRotatef(Observer_angle_y,0,1,0);
		}

		void setObserver_desplaza_x_neg(GLfloat i){eye_x = eye_x - i;setLookAt();}
		void setObserver_desplaza_x_pos(GLfloat i){eye_x = eye_x + i;setLookAt();}
		void setObserver_desplaza_y_neg(GLfloat i){eye_y = eye_y - i;setLookAt();}
		void setObserver_desplaza_y_pos(GLfloat i){eye_y = eye_y + i;setLookAt();}
		void setObserver_desplaza_z_neg(GLfloat i){eye_z = eye_z - i;setLookAt();}
		void setObserver_desplaza_z_pos(GLfloat i){eye_z = eye_z + i;setLookAt();}

		void setObserver_desplaza_x(GLfloat i){eye_x += i;setLookAt();}
		void setObserver_desplaza_y(GLfloat i){eye_y += i;setLookAt();}
		void setObserver_desplaza_z(GLfloat i){eye_z += i;setLookAt();}

		void setObserver_centro(GLfloat x, GLfloat y, GLfloat z){
			at_x += x;
			at_y += y;
			at_z += z;
			setLookAt();
		}


		void setObserver_inclinacion(GLfloat x, GLfloat y, GLfloat z){
			up_x += x;
			up_y += y;
			up_z += z;
			setLookAt();
		}

		void setObserver_angle_x(GLfloat i){Observer_angle_x += i;}
		void setObserver_angle_y(GLfloat i){Observer_angle_y += i;}

		void setObserver_distance_multiply(GLfloat i){eye_z += i*2;}
		void setObserver_distance_divide(GLfloat i){eye_z -= i*2;}


		/*void cambiarProyeccion(const float ratioXY,GLfloat Window_width,GLfloat Window_height,GLfloat Front_plane,GLfloat Back_plane,int tipo){
			switch(tipo){
				case 0:glFrustum(-Window_width,Window_width,-Window_height/ratioXY,Window_height/ratioXY,Front_plane,Back_plane);break;
				case 1:glOrtho(-Window_width,Window_width,-Window_height/ratioXY,Window_height/ratioXY,Front_plane,Back_plane);break;
			}	
		}*/
};

#endif