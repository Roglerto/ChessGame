/**
  * 
  *  interaccion.cpp
  * Archivo fuente del módulo de interacción de la practica 5
  * 
  * Informática Gráfica 
  *  3º Grado en Ingeniería Informática
  * Universidad de Granada
  * 
  *  Curso 2012/13
  *  Autor: J.C. Torres
  * 
  *  Versión 1.0
  *  Diciembre 2012
  *   
  **/
#include <GL/glut.h>
#include <iostream>
#include "interaccion.hpp"
#include "tablero.hpp"
#include <stdio.h>
#include <cmath>

#define MAX_SEL 64

extern tablero *  obj_tablero;
using namespace std;


int moving, begin_x,begin_y;
int newModel = 1;
int trasl_x, trasl_y;
GLfloat escala_x, escala_y;
GLfloat angle =0.f;

float x0,  yy0;

int modo=0;
 int  is , js ,auxi,auxj;

int turno=0,fase=0,num;


/**
 
void clickRaton( int boton, int estado, int x, int y );

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/
void clickRaton(int button, int state, int x, int y)
{

 if (button == GLUT_RIGHT_BUTTON   && state == GLUT_DOWN) {
 
 cout << " CAMARA " <<endl;
 
	moving = 1;
	begin_x = x;
	begin_y = y;
	}
 if (button == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) {
 
 
	  if( fase==0 ){     //EMPIEZA JUGADOR 1 SELECCIONA FICHA
	   cout <<" empieza jugador 1 LATAS " <<endl;
	  	modo=1;
	  }if( fase==1 ){    //JUGADOR 1 ELIGE DESTINO
	   cout <<" jugador 1 LATAS elige destino " <<endl;
	  	modo=5;
	  }if( fase==2 ) {   //EMPIEZA JUGADOR 2 SELECCIONA FICHA
	   cout <<" empieza jugador 2 TETERAS " <<endl;
	 	 modo=2;
	 }if( fase==3 ) {	//JUGADOR 2 ELIGE DESTINO
	  cout <<" jugador 2 TETERAS elige destino" <<endl;
	  	modo=5;
	  
	  }
	  
	 switch(modo) 
      {
      
      case 1://JUGADOR 1
      
      	    num= pick(x, y,  modo,  &is,  &js);
            if(num==1){
		auxi=is;
		auxj=js;
            	fase=1;
            }else if(num==0){
            	cout <<" TURNO LATAS" <<endl;
            }

            break ;
            
       case 2://JUGADOR 2
       
       	    num= pick(x, y,  modo,  &is,  &js);
            if(num==1){
              auxi=is;
	      auxj=js;
              fase=3;
            }else if(num==0){
                cout <<" TURNO TETERAS" <<endl;
            }
            
            break ;
            
      case 5://CASILLA
      
           num= pick(x, y,  modo,  &is,  &js);
           
            if(num==1){
             
             
               obj_tablero->move(auxi , auxj ,is  ,js ); //DESPLAZAMOS LA PIEZA A UNA CASILLA VACIA               
              
            
            if(fase== 3)
            	fase=0;
            else fase=2;
            
            DibujarVentana();
            
            }else if(num==0){
                     cout <<" TURNO CASILLA" <<endl;
            }
           
            break ;
      
      }
}

 if ((button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) && state == GLUT_UP) {
	moving = 0;
	}
		
}


/**

void RatonMovido( int x, int y );

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido(int x, int y)
{	//Captura el movimiento del mouse.
 if (moving==1) {		
	getCamara(&x0,&yy0);
	trasl_y= (int) (y0+(y-begin_y)) ;
	trasl_x= (int) (x0-(x-begin_x));

	setCamara(trasl_x,trasl_y);
	begin_x=x;
	begin_y=y;
	glutPostRedisplay();
}

}

//(GLfloat)(x - begin_x)/100.0


/**
int pick(int x, int y, int modo, int * is, int * js);

    Función de selección
    
Entrada
  x,y Posición del cursor
  modo=0 selecciona casilla
  modo=1 selecciona pieza jugador 1
  modo=2 selecciona pieza jugador 2

Devuelve 
  0 si no se ha seleccionado nada
  1 cuando hay objeto seleccionado según el modo
	  
Salida
  is,js coordenadas de la celda seleccionada

**/ 

int pick(int x, int y, int modo,  int * is, int * js)
{
GLuint BufferSeleccion[MAX_SEL] ;
GLint hits, viewport[4];
int i=0;
int t=0,tam=0;
bool encontrado=false;



 // 1. Declarar buffer de selección
glSelectBuffer(MAX_SEL, BufferSeleccion);
// 2. Obtener los parámetros del viewport
glGetIntegerv (GL_VIEWPORT, viewport);
// 3. Pasar OpenGL a modo selección
glRenderMode (GL_SELECT);
// 4. Fijar la transformación de proyección para la seleccion
//glInitNames();
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);
MatrizProyeccion(); // SIN REALIZAR LoadIdentity !
// 5. Dibujar la escena
DibujarVentana();
// 6. Pasar OpenGL a modo render
hits = glRenderMode (GL_RENDER);
// 7, Restablecer la transformación de proyección (sin gluPickMatrix)
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
MatrizProyeccion();
//glLoadIdentity();

// 8. Analizar el contenido del buffer de selección


if(modo==5){                    //CASILLA
	
	while(!encontrado && tam!=MAX_SEL){
		if(BufferSeleccion[i]==0)
			i+=3;
		 if(BufferSeleccion[i]==3){
			if(BufferSeleccion[i+3]==modo){
				encontrado=true;
				t=1;
				(*is)=BufferSeleccion[i+4];
				(*js)=BufferSeleccion[i+5];
				
			}else i+=6;
		}
		tam++;	
	}
	 
        
}if(modo==1){                  //JUGADOR 1


	while(!encontrado && tam!=MAX_SEL){
		if(BufferSeleccion[i]==0)
			i+=3;
		 if(BufferSeleccion[i]==3){
			if(BufferSeleccion[i+3]==modo){
				encontrado=true;
				t=1;
				(*is)= BufferSeleccion[i+4];
				(*js)=BufferSeleccion[i+5];
				
			}else i+=6;
		}
		tam++;		
	}
        
    	



}if(modo==2){                    //JUGADOR 2

	while(!encontrado && tam!=MAX_SEL){
		if(BufferSeleccion[i]==0)
			i+=3;
		 if(BufferSeleccion[i]==3){
			if(BufferSeleccion[i+3]==modo){
				encontrado=true;
				t=1;
				(*is)=BufferSeleccion[i+4];
				(*js)=BufferSeleccion[i+5];
			}else i+=6;
		}
		tam++;		
	}
	
    

  

}
// 9. Devolver los valores encontrados en is,js y el resultado



 

 return t;
}



