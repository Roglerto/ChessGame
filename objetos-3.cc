//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2005-2012
//
// GPL
//**************************************************************************

#include "file_ply_stl.hpp"
#include "objetos-3.h" 
#include "math.h"
#include "iostream"

using namespace std;


//*************************************************************************
// _object3D
//*************************************************************************
//*************************************************************************
//
//*************************************************************************

_object3D::_object3D()
{
  
  Point_size=POINT_SIZE;
  Line_width=LINE_WIDTH;
  
}



//*************************************************************************
//
//*************************************************************************

void _object3D::draw_points()
{
glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor4f(1,0,0,1);
glPointSize(5);

glBegin( GL_POINTS ) ;


for( int i=0 ; i < (int)Vertices.size() ; i++ ) {
	glVertex3f( Vertices[i].x, Vertices[i].y, Vertices[i].z );
}
glEnd() ;
  
}

//*************************************************************************
// _triangles_object3D
//*************************************************************************
 

_triangles_object3D::_triangles_object3D()
{
   Faces_normals_computed       = false ;
   Vertices_normals_computed    = false ;
   Vertices_tex_coords_computed = false ;
   material=NULL;  
   
   
   Point_size=POINT_SIZE;
Line_width=LINE_WIDTH;

Line_color.x=1;
Line_color.y=1;
Line_color.z=0;
Line_color.w=0;

Solid_color.x=0;
Solid_color.y=1;
Solid_color.z=1;
Solid_color.w=0;

Solid_chess_color1.x=0;
Solid_chess_color1.y=1;
Solid_chess_color1.z=1;
Solid_chess_color1.w=1;

Solid_chess_color2.x=0;
Solid_chess_color2.y=0;
Solid_chess_color2.z=1;
Solid_chess_color2.w=0;
}

//*************************************************************************
// Dibuja las aristas de los triangulos no iluminados
//*************************************************************************

void _triangles_object3D::draw_edges()
{   
glDisable(GL_LIGHTING);

glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glColor4f(Line_color.x,Line_color.y,Line_color.z,Line_color.w);
glBegin( GL_TRIANGLES ) ;

int Vertex_1,Vertex_2,Vertex_3;

for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);
}


glEnd() ;   
}

//*************************************************************************
// Dibuja triangulos no iluminados con apariencia de ajedrez
//*************************************************************************

void _triangles_object3D::draw_solid_chess()
{
int Vertex_1,Vertex_2,Vertex_3;

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin( GL_TRIANGLES );


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	if ( i %2 == 0 ){ glColor4f(Solid_chess_color1.x,Solid_chess_color1.y,Solid_chess_color1.z,Solid_chess_color1.w) ;
		}else {glColor4f(Solid_chess_color2.x,Solid_chess_color2.y,Solid_chess_color2.z,Solid_chess_color2.w);
		}
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;   
}

//*************************************************************************
// Dibuja triangulos no iluminados
//*************************************************************************

void _triangles_object3D::draw_solid_non_illuminated()
{

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

int Vertex_1,Vertex_2,Vertex_3;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor4f(Solid_chess_color2.x,Solid_chess_color2.y,Solid_chess_color2.z,Solid_chess_color2.w);
glBegin( GL_TRIANGLES );


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

		
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;
  
}



//*************************************************************************
// Dibuja puntos, aristas y caras a la vez
//*************************************************************************

void _triangles_object3D::draw_points_edges_solid_non_illuminated()
{
draw_points();
draw_edges();
draw_solid_non_illuminated();
}
//**********************************************************************





//**********************************************************************


void _triangles_object3D::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}
if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}

glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	
	
	glNormal3f( Vertices_normals[Vertex_1].x , Vertices_normals[Vertex_1].y,Vertices_normals[Vertex_1].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_1].x,Vertices_tex_coords[Vertex_1].y );
	 glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);

	

	glNormal3f( Vertices_normals[Vertex_2].x , Vertices_normals[Vertex_2].y ,
				Vertices_normals[Vertex_2].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_2].x,Vertices_tex_coords[Vertex_2].y );
	 glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);

	

	glNormal3f( Vertices_normals[Vertex_3].x , Vertices_normals[Vertex_3].y ,
				Vertices_normals[Vertex_3].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_3].x,Vertices_tex_coords[Vertex_3].y );
	 glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);


	
}

glEnd() ;   
}

void _triangles_object3D::draw_solid_material_flat()
{


int Vertex_1,Vertex_2,Vertex_3;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}
if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}


glShadeModel(GL_FLAT);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glNormal3f( Vertices_normals[Vertex_1].x , Vertices_normals[Vertex_1].y ,
				Vertices_normals[Vertex_1].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_1].x,Vertices_tex_coords[Vertex_1].y );
	 glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	
	glNormal3f( Vertices_normals[Vertex_2].x , Vertices_normals[Vertex_2].y ,
				Vertices_normals[Vertex_2].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_2].x,Vertices_tex_coords[Vertex_2].y );
	 glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	
	glNormal3f( Vertices_normals[Vertex_3].x , Vertices_normals[Vertex_3].y ,
				Vertices_normals[Vertex_3].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_3].x,Vertices_tex_coords[Vertex_3].y );
	 glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);
	

}

glEnd() ;

   
}


//*************************************************************************
//
//*************************************************************************

void _triangles_object3D::draw( _draw_type Draw_type )
{
switch (Draw_type){
	case POINTS: draw_points(); break;
	case EDGES: draw_edges(); break;
	case SOLID_CHESS: draw_solid_chess(); break;
	case SOLID_NON_ILLUMINATED: draw_solid_non_illuminated(); break;
	case normales_caras: draw_solid_normales_caras(); break;
	case normales_vertices: draw_solid_normales_vertices(); break;
	case POINTS_EDGES_SOLID_NON_ILLUMINATED: draw_points_edges_solid_non_illuminated(); break;
	
	case SOLID_MATERIAL_FLAT:  draw_solid_material_flat(); break;
	case SOLID_MATERIAL_GOUROUD:draw_solid_material_gouroud();  break;


}
  
}

void _triangles_object3D::draw_solid_normales_caras(){
int Vertex_1,Vertex_2,Vertex_3;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glShadeMode(GL_FLAT);

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	if(Faces_normals[i].y<0){
		glColor4f(Solid_chess_color2.x,Faces_normals[i].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Faces_normals[i].y,Solid_chess_color1.z,Solid_chess_color1.w);
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;




}



void _triangles_object3D::draw_solid_normales_vertices(){


int Vertex_1,Vertex_2,Vertex_3;


if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glShadeMode(GL_FLAT);

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	if(Vertices_normals[Vertex_1].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_1].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_1].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);

	if(Vertices_normals[Vertex_2].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_2].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_2].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);

	if(Vertices_normals[Vertex_3].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_3].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_3].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;




}



//*************************************************************************
// calcula las normales de las caras
//*************************************************************************

void _triangles_object3D::compute_faces_normals()
{
_vertex3f a,a2,a3,b,b2,b3,n1,n2,n3,c,c2,c3,abvector,acvector,dato;
int Vertex_1,Vertex_2,Vertex_3;


for(int i=0; i < (int) Faces_vertices.size(); i++){

	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;




	a.x=Vertices[Vertex_1].x;
	a.y=Vertices[Vertex_1].y ; // vertice p1
	a.z=Vertices[Vertex_1].z;
	
	
	
	
	b.x=Vertices[Vertex_2].x;
	b.y=Vertices[Vertex_2].y ;  //vertice p0
	b.z=Vertices[Vertex_2].z;
	

	
	abvector.x=b.x-a.x;
	abvector.y=b.y-a.y ;   // vector A
	abvector.z=b.z-a.z;
	
	
	
	c.x=Vertices[Vertex_3].x;
	c.y=Vertices[Vertex_3].y ;   //vertice p2
	c.z=Vertices[Vertex_3].z;
	
		
	acvector.x=c.x-a.x;
	acvector.y=c.y-a.y ;   // vector A
	acvector.z=c.z-a.z;
	
	
	
	//CALCULAMOS producto vectorial de abvectorxacvector
	
	dato.x=(abvector.y*acvector.z) - (abvector.z*acvector.y);
	dato.y=(-1)* ((abvector.x*acvector.z) - (abvector.z*acvector.x));
	dato.z=(abvector.x*acvector.y) - (abvector.y*acvector.x);

	
	Faces_normals.push_back(dato);
	
	}

	for(int i=0; i < (int) Faces_normals.size(); i++){
	
	Faces_normals[i].normalize();

	}
	
	Faces_normals_computed=true;   
}


//*************************************************************************
// Calcular normales de vértices,
//
//*************************************************************************

void _triangles_object3D::compute_vertices_normals()
{
_vertex3f a,a2,a3,b,b2,b3,n1,n2,n3,c,c2,c3,abvector,acvector,dato;
int Vertex_1,Vertex_2,Vertex_3;


compute_faces_normals();

//if(!Faces_normals_computed)
	//compute_faces_normals();


/*
para cada vertice i ( 0... numvert-1)
	normal_vert[i] = (0,0,0)

para cada cara j  ( 0.. num.cara -1)
	i0,i1,i2 = indices vert cara j-esima
	ar1=vert i1-vert i0
	ar2= vert i2 - vert i0
	normalcara[j]= ar1*ar2/||ar1*ar2||
	normalvert[i0]=normalvert[i0]+normalcara[j]
      
	(idem vert i1 y i2)

pàra cada vert i ( i 00..numvert-1)
	normalizar normal vert i-esimo

-----------------------------------------------------



*/

Vertices_normals.resize(Vertices.size());

a.x=0;
a.y=0;
a.z=0;


for(int i=0; i < (int) Vertices.size(); i++){
	Vertices_normals[i]=a;
}


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;

	Vertices_normals[Vertex_1].x=Vertices_normals[Vertex_1].x+Faces_normals[i].x;
	Vertices_normals[Vertex_1].y=Vertices_normals[Vertex_1].y+Faces_normals[i].y;
	Vertices_normals[Vertex_1].z=Vertices_normals[Vertex_1].z+Faces_normals[i].z;
	
	Vertices_normals[Vertex_2].x=Vertices_normals[Vertex_2].x+Faces_normals[i].x;
	Vertices_normals[Vertex_2].y=Vertices_normals[Vertex_2].y+Faces_normals[i].y;
	Vertices_normals[Vertex_2].z=Vertices_normals[Vertex_2].z+Faces_normals[i].z;

	Vertices_normals[Vertex_3].x=Vertices_normals[Vertex_3].x+Faces_normals[i].x;
	Vertices_normals[Vertex_3].y=Vertices_normals[Vertex_3].y+Faces_normals[i].y;
	Vertices_normals[Vertex_3].z=Vertices_normals[Vertex_3].z+Faces_normals[i].z;

	


}




for(int i=0; i < (int) Vertices_normals.size(); i++){
	
	Vertices_normals[i].normalize();
	

}

Vertices_normals_computed=true;


}

//----------------------------------------------------------------------

int _triangles_object3D::create(vector<float> Vertices1,vector<int> Faces1)
{

_vertex3f Vertex;
_vertex3i vert;

	
for(int i=0; i< (int) Vertices1.size();i++){
	Vertex.x=Vertices1[i];
	i++;
	Vertex.y=Vertices1[i];
	i++;
	Vertex.z=Vertices1[i];
	
	Vertices.push_back(Vertex);
	
}

for(int k=0; k< (int) Faces1.size();k++){
	vert.x=Faces1[k];
	k++;
	vert.y=Faces1[k];
	k++;
	vert.z=Faces1[k];
	
	Faces_vertices.push_back(vert);
}

return 0;
}



//**********************************************************************
// clase _ply_triangles_object3D

_ply_triangles_object3D::_ply_triangles_object3D( const std::string & nombreArchivo ) 
{
const char * archivo = nombreArchivo.c_str();

_file_ply::read( archivo, vertices,faces );

create(vertices,faces);

Vertices_tex_coords.resize(Vertices.size());

}

//*************************************************************************
// _cube
//*************************************************************************
//*************************************************************************
//
//*************************************************************************

_cube::_cube()
{
_vertex3f Vertex;
_vertex3i vert;

//ALMACENAMOS LOS VERTICES
Vertex.x=3;
Vertex.y=0;
Vertex.z=3;

Vertices.push_back(Vertex);

Vertex.x=3;
Vertex.y=0;
Vertex.z=0;

Vertices.push_back(Vertex);

Vertex.x=3;
Vertex.y=3;
Vertex.z=0;

Vertices.push_back(Vertex);

Vertex.x=3;
Vertex.y=3;
Vertex.z=3;

Vertices.push_back(Vertex);

Vertex.x=0;
Vertex.y=3;
Vertex.z=0;

Vertices.push_back(Vertex);

Vertex.x=0;
Vertex.y=0;
Vertex.z=0;

Vertices.push_back(Vertex);


Vertex.x=0;
Vertex.y=3;
Vertex.z=3;

Vertices.push_back(Vertex);

Vertex.x=0;
Vertex.y=0;
Vertex.z=3;

Vertices.push_back(Vertex);

//almacenamos las caras
vert.x=0;
vert.y=1;
vert.z=2;
Faces_vertices.push_back(vert);

vert.x=0;
vert.y=3;
vert.z=2;
Faces_vertices.push_back(vert);

vert.x=6;
vert.y=3;
vert.z=2;
Faces_vertices.push_back(vert);

vert.x=6;
vert.y=2;
vert.z=4;
Faces_vertices.push_back(vert);

vert.x=5;
vert.y=1;
vert.z=2;
Faces_vertices.push_back(vert);

vert.x=5;
vert.y=2;
vert.z=4;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=0;
vert.z=1;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=1;
vert.z=5;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=0;
vert.z=3;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=3;
vert.z=6;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=5;
vert.z=4;
Faces_vertices.push_back(vert);

vert.x=7;
vert.y=4;
vert.z=6;
Faces_vertices.push_back(vert);

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}
if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}

Vertices_tex_coords.resize(Vertices.size());

        material = new Material();
	material->iluminacion    = true ;
	material->tex            = new texcube() ;
	material->del.ambiente  = vectorRGB( 0.1,0.1,0.1 ) ;
	material->del.difusa    = vectorRGB( 0.5,0.5,0.5 ) ;
	material->del.especular = vectorRGB( 1.0,1.0,1.0 ) ;
	material->del.exp_brillo = 40 ;
	material->tra.difusa    = vectorRGB( 0.3,0.3,0.3 ) ;
	material->tra.especular = vectorRGB( 0.5,0.5,0.5 ) ;
	material->tra.exp_brillo = 15 ;
}

texcube::texcube()

:  Textura("wood.jpg")
{
	modo_gen_ct = mgct_coords_ojo ;
}

void _triangles_object3D::draw_cube(_draw_type Draw_type){
int Vertex_1,Vertex_2,Vertex_3;
	if(Draw_type != SOLID_MATERIAL_FLAT && Draw_type != SOLID_MATERIAL_GOUROUD){
		draw(Draw_type);
	}
	else {
		if(Draw_type == SOLID_MATERIAL_FLAT) glShadeModel(GL_FLAT);
		else glShadeModel(GL_SMOOTH);

		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		material->activar();
                glBegin(GL_TRIANGLES);
                
		for ( int i = 0; i < 12; i+=2){
			Vertex_1 = Faces_vertices[i].x ;
	                Vertex_2 = Faces_vertices[i].y ;
	                Vertex_3 = Faces_vertices[i].z ;
	                
			glTexCoord2d(0.0,0.0);
			glNormal3f( Vertices_normals[Vertex_1].x , Vertices_normals[Vertex_1].y ,
					Vertices_normals[Vertex_1].z);
			glVertex3f(Vertices[Vertex_1].x,Vertices[Vertex_1].y,
					Vertices[Vertex_1].z);

			glTexCoord2d(1.0,0.0);
			glNormal3f( Vertices_normals[Vertex_2].x , Vertices_normals[Vertex_2].y ,
					Vertices_normals[Vertex_2].z );
			glVertex3f(Vertices[Vertex_2].x,Vertices[Vertex_2].y,
					Vertices[Vertex_2].z);

			glTexCoord2d(1.0,1.0);
			glNormal3f( Vertices_normals[Vertex_3].x , Vertices_normals[Vertex_3].y ,
					Vertices_normals[Vertex_3].z );
			glVertex3f(Vertices[Vertex_3].x,Vertices[Vertex_3].y,
					Vertices[Vertex_3].z);
			

			
			glTexCoord2f(0.0,0.0);
			glNormal3f( Vertices_normals[Faces_vertices[i+1][0]][0] , Vertices_normals[Faces_vertices[i+1][0]][1] ,
					Vertices_normals[Faces_vertices[i+1][0]][2]);
			glVertex3f(Vertices[Faces_vertices[i+1][0]][0],Vertices[Faces_vertices[i+1][0]][1],
					Vertices[Faces_vertices[i+1][0]][2]);

			glTexCoord2f(1.0,1.0);
			glNormal3f( Vertices_normals[Faces_vertices[i+1][1]][0] , Vertices_normals[Faces_vertices[i+1][1]][1] ,
					Vertices_normals[Faces_vertices[i+1][1]][2] );
			glVertex3f(Vertices[Faces_vertices[i+1][1]][0],Vertices[Faces_vertices[i+1][1]][1],
					Vertices[Faces_vertices[i+1][1]][2]);

			glTexCoord2f(0.0,1.0);
			glNormal3f( Vertices_normals[Faces_vertices[i+1][2]][0] , Vertices_normals[Faces_vertices[i+1][2]][1] ,
					Vertices_normals[Faces_vertices[i+1][2]][2] );
			glVertex3f(Vertices[Faces_vertices[i+1][2]][0],Vertices[Faces_vertices[i+1][2]][1],
					Vertices[Faces_vertices[i+1][2]][2]);
			
		}
	}glEnd();
}
