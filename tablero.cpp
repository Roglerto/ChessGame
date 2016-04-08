/**
  * 
  *  tablero.cpp
  * Archivo fuente del módulo de tablero de la practica 5
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
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "jpg_imagen.hpp"
#include "materiales.hpp"

#include "tablero.hpp"
#include "lata-coca.hpp"
#include "tetera.hpp"


using namespace std;


const float lado= 0.1 ; // longitud de casillas




/** 

Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base. 

**/
void caja( float a, float b, float m)

{
	float x,y,z;
	
	x= a/2;
	z= m/2;
	y = b;

   glShadeModel( GL_FLAT );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );


      glVertex3f( x, y, -z );
      glVertex3f( -x, y, -z );

glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

      glVertex3f( x, y, z );
      glVertex3f( -x, y, z );
glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( -x, 0, z );

glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, -z );
      glVertex3f( x, y, -z );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( -x, 0, -z );
      glVertex3f( -x, 0, z );
      glVertex3f( -x, y, z );
      glVertex3f( -x, y, -z ); }
   glEnd();
}





//**********************************************************************
// clase tablero
//
//**********************************************************************

//----------------------------------------------------------------------
// Constructor:

tablero::tablero(LataCocaCola * obj_lata_coca_cola,Tetera * obj_tetera)
{
  int i,j;
  ficha1=obj_lata_coca_cola; 
  ficha2=obj_tetera;
     for(i=0;i<8;++i)
    for(j=0;j<8;++j)
      piezas[i][j]=0;
    
    for(i=0;i<8;++i) {
      j=i%2;
        piezas[i][j]=1;
	piezas[i][6+j]=2;
    }
    seleccionando=0;
}



void tablero::draw()
{
  int i,j;
  float x,y,z;
  float lmin,lmax; // extremos del marco
   float c1[4]={1.0,1.0,1.0,1.}, c2[4]={0.1,0.1,0.1,1.0},c3[4]={0.4,0.2,0.0,1.0};
  

  glShadeModel( GL_FLAT );
  glInitNames();

  y=lado/4.0;

glPushName(5);
  // Casillas
  for(i=0;i<8;++i){
    x=lado*i-lado*4;
  
  	glPushName(i);
  
    for(j=0;j<8;++j){
       z=lado*j-lado*4;
       
         glPushName(j);
       
       if((i+j)%2)
	   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c1);
	 else
	    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c2);
	    
     glBegin( GL_QUADS );{
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( x, y, z );
      glVertex3f( x+lado, y, z );
      glVertex3f( x+lado, y, z+lado );
      glVertex3f( x, y, z+lado ); }
      glEnd();
      
      	glPopName();
    }
      glPopName();
  }
glPopName();


	// jugador 1  COCACOLA
   for(i=0;i<8;++i){
    x=lado*i-lado*4;
    

    
    for(j=0;j<8;++j){
      z=lado*j-lado*4;
      

      
       if(piezas[i][j]==1) 
	  {
	  glPushName(1);
	      glPushName(i);
	  	      glPushName(j);
	  	      
	  glPushMatrix();
	     glTranslatef(x+lado/2,y+0.05,z+lado/2);
	     glScalef(0.1,0.1,0.1);
	     ficha1->draw(SOLID_MATERIAL_GOUROUD);
	  glPopMatrix();	
	  
	  	glPopName();
	      glPopName();
	    glPopName();    
	}
	

    }

   }

    

	// jugador 2   TETERAS
     for(i=0;i<8;++i){
       x=lado*i-lado*4;
       
    
       
      for(j=0;j<8;++j){
        z=lado*j-lado*4;
        
        
        
       if(piezas[i][j]==2) 
	  {
	  glPushName(2);
	      glPushName(i);
	  	      glPushName(j);
	  
	  glPushMatrix();
	      glTranslatef(x+lado/2,y+0.025,z+lado/2);
	      glScalef(0.08,0.08,0.08);
	      ficha2->draw(SOLID_MATERIAL_GOUROUD);
	  glPopMatrix();
	  
	  	glPopName();
	      glPopName();
	   glPopName();
	  
	}
	    
    }
        
   }
 
  
  // Dibujo del marco del tablero 

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c3);
    lmin= -lado*5.0;
    lmax= -lado*4;
  
    glBegin( GL_QUAD_STRIP );{
    
    glNormal3f( 0.0, 0.0, -1.0 );  
      glVertex3f(  lmin, y, -lmin );
      glVertex3f(  lmin, 0, -lmin );

      glVertex3f( -lmin, y, -lmin );
      glVertex3f( -lmin, 0, -lmin );

     glNormal3f( -1.0, 0.0, 0.0 );    

      glVertex3f( -lmin, y, lmin );
      glVertex3f( -lmin, 0, lmin );
      
    glNormal3f( 0.0, 0.0, 1.0 );      
    
      glVertex3f(  lmin, y, lmin );
      glVertex3f(  lmin, 0, lmin );

     glNormal3f( 1.0, 0.0, 0.0 );      

      glVertex3f(  lmin, y, -lmin );
      glVertex3f(  lmin, 0, -lmin );  }
    glEnd();

    glBegin( GL_QUAD_STRIP );{
    
    glNormal3f( 0.0, 1.0, 0.0 );  
      glVertex3f(  lmin, y, -lmin );
      glVertex3f(  lmax, y, -lmax );

      glVertex3f( -lmin, y, -lmin );
      glVertex3f( -lmax, y, -lmax );   

      glVertex3f( -lmin, y, lmin );
      glVertex3f( -lmax, y, lmax );      
    
      glVertex3f(  lmin, y, lmin );
      glVertex3f(  lmax, y, lmax );

      glVertex3f(  lmin, y, -lmin );
      glVertex3f(  lmax, y, -lmax );  }
    glEnd();
  
      glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -lmin, 0, -lmin );
      glVertex3f( lmin, 0, -lmin);
      glVertex3f( lmin, 0, lmin );
      glVertex3f( -lmin, 0, lmin ); }
      glEnd();
    
}
/**
Traslada la pieza en la casilla xi,yi a xf,yf

Requisitos: xf,yf está vacia 
	    las dos celdas son vecinas por una esquina, o tienen una casilla de diferencia ocupada por el contrincante
	    xf,yf es una celda valida en las damas
	    
	    

Efectos: si se ha comido una ficha desaparece del tablero

**/
 int tablero::move(int xi, int yi, int xf, int yf)
 {
   if(xi<0 || xi >7 || yi<0 || yi >7  || xf<0 || xf >7  || yf<0 || yf >7 ) {
      printf(" Movimiento incorrecto %d %d -> %d %d \n",xi,yi,xf, yf);
      return 0;
   }
   if( piezas[xf][yf] == piezas[xi][yi]) {
     printf(" Movimiento incorrecto %d %d -> %d %d \n",xi,yi,xf, yf);
      return 0;
   }
   if( abs(xf-xi)>2 || abs(yf-yi)>2) {
     printf(" Movimiento incorrecto %d %d -> %d %d \n",xi,yi,xf, yf);
      return 0;
   }
   piezas[xf][yf] = piezas[xi][yi];
   piezas[xi][yi] = 0;
   return 1;
 }


  void tablero::setSeleccionando(int s)
  {
    seleccionando=s;
  }
