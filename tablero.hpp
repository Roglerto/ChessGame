/**
  * 
  *  tablero.hpp
  * Archivo include para módulo de tablero de la practica 5
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
#ifndef  TABLERO_HPP
#define  TABLERO_HPP

#include "materiales.hpp"
#include "objetos-4.hpp"
#include "lata-coca.hpp"
#include "tetera.hpp"
#include "objeto-ply.hpp"

class tablero 
{
   public:
   int piezas[8][8];
   LataCocaCola * ficha1;
   Tetera * ficha2;
   int seleccionando;
   
//   tablero();
   tablero(LataCocaCola * obj_lata_coca_cola,Tetera * obj_tetera);
   void  draw();
   void setSeleccionando(int s);
  
  /**
Traslada la pieza en la casilla xi,yi a xf,yf

Requisitos: 	    
	  las dos celdas están a menos de una casilla de distancia, 
	  si la celda destino está ocupada por el contrincante la pieza es comida
	   
Efectos: si se ha comido una ficha desaparece del tablero

Devuelve: 1 si se ha podido mover, 0 en caso contrario

**/
 int move(int xi, int yi, int xf, int yf);
} ;


#endif
