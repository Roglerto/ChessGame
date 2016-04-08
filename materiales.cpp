#include <GL/glu.h>
#include <GL/glut.h>
#include "aux-p4.hpp"
#include "materiales.hpp"



//**********************************************************************

Textura::Textura( const std::string & nombreArchivoJPG ) 
{
// Constructor: lee el archivo y guarda los texels en memoria:
jpg::Imagen ima(nombreArchivoJPG);

imagen= &ima;

glGenTextures( 1, &ident_textura );
glBindTexture (GL_TEXTURE_2D, ident_textura);

gluBuild2DMipmaps( GL_TEXTURE_2D,
GL_RGB,
// formato interno
// Devuelve el número de columnas de la imagen:
ima.tamX()  ,
// Devuelve el número de filas de la imagen:
 ima.tamY()  ,
GL_RGB,
// formato y orden de los texels en RAM
GL_UNSIGNED_BYTE,
// tipo de cada componente de cada texel
// Devuelve un puntero a la zona donde estan los texels,
// puestos por filas, tres bytes (sin signo) por texel, en orden RGB:
 ima.leerPixels() 
// puntero a los bytes con texels (void *)
);


	
}

//----------------------------------------------------------------------

Textura::~Textura( ) 
{
  if(imagen!=NULL){
		delete imagen;
		imagen = NULL;
	}
}

//----------------------------------------------------------------------

void Textura::activar( ) 
{
glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ident_textura);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(modo_gen_ct==mgct_coords_objeto){
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv( GL_S, GL_OBJECT_PLANE, coefs_s ) ;
		glTexGenfv( GL_T, GL_OBJECT_PLANE, coefs_t ) ;
	}
   

}

//**********************************************************************

Material::Material() 
{
   iluminacion = false ;
   tex = NULL ;
   
   coloresCero() ;
}

//----------------------------------------------------------------------

Material::Material( const std::string & nombreArchivoJPG ) 
{
   iluminacion    = false ;
   tex            = new Textura( nombreArchivoJPG ) ;
   
   coloresCero();
   
   del.difusa = vectorRGB( 0.5, 0.5, 0.5 );
   tra.difusa = vectorRGB( 0.2, 0.2, 0.2 );
   
   del.especular = vectorRGB( 1.0, 1.0, 1.0 );
   tra.especular = vectorRGB( 0.2, 0.2, 0.2 );
}

//----------------------------------------------------------------------

void Material::coloresCero()
{
   const vectorRGB ceroRGB(0.0,0.0,0.0);
   
   color         = 
   
   del.emision   = 
   del.ambiente  = 
   del.difusa    = 
   del.especular = 

   tra.emision   = 
   tra.ambiente  = 
   tra.difusa    = 
   tra.especular = ceroRGB ;
   
   del.exp_brillo = 
   tra.exp_brillo = 1.0 ;
}

//----------------------------------------------------------------------

Material::~Material() 
{      
   if ( tex != NULL )
   {  delete tex ;
      tex = NULL ;
   }
}


//----------------------------------------------------------------------

void Material::activar()
{
GLfloat del_Emision_component[4]={del.emision.x,del.emision.y,del.emision.z,1.0};
GLfloat del_Ambient_component[4]={del.ambiente.x,del.ambiente.y,del.ambiente.z,1.0};
GLfloat del_Difu_component[4]={del.difusa.x,del.difusa.y,del.difusa.z,1};
GLfloat del_Especu_component[4]={del.especular.x,del.especular.y,del.especular.z,1.0};

GLfloat tra_Emision_component[4]={tra.emision.x,tra.emision.y,tra.emision.z,1.0};
GLfloat tra_Ambient_component[4]={tra.ambiente.x,tra.ambiente.y,tra.ambiente.z,1.0};
GLfloat tra_Difu_component[4]={tra.difusa.x,tra.difusa.y,tra.difusa.z,1.0};
GLfloat tra_Especu_component[4]={tra.especular.x,tra.especular.y,tra.especular.z,1.0};

GLfloat component[4]={color.x,color.y,color.z,1.0};

glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT,GL_FILL);
glPolygonMode(GL_BACK,GL_FILL);


if(tex!=NULL)  
	tex->activar(); 
	
if(tex==NULL)  {
	glDisable(GL_TEXTURE_2D);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	}

if(iluminacion){
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);// tutoria deshabilitar color material 1 para delanteras y traseras
	glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, component);

	//MEFALTA-1 tutoria gl LIGHMODEL activar light model de 2 caras
	//MEFALTA -2 gl lightmodel activar evaulación por separado de la componente especular

	//glLightModelf( GL_DIFFUSE, color ) ;
	//glLightModelf( GL_SPECULAR, color ) ;
	//glLightModelf( GL_EMISSION, color ) ;


	//CARAS DELANTERAS
	
	glMaterialfv( GL_FRONT, GL_EMISSION, del_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_FRONT, GL_AMBIENT, del_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_FRONT, GL_DIFFUSE, del_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)	
	glMaterialfv( GL_FRONT, GL_SPECULAR, del_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_FRONT, GL_SHININESS, del.exp_brillo ) ;
	
	
	//CARAS TRASERAS
	
	glMaterialfv( GL_BACK, GL_EMISSION, tra_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_BACK, GL_AMBIENT, tra_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_BACK, GL_DIFFUSE, tra_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)
	glMaterialfv( GL_BACK, GL_SPECULAR, tra_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_BACK, GL_SHININESS, tra.exp_brillo ) ;
	
	

	
}else{
	glDisable(GL_LIGHTING);// color del material cuando iluminacion==false
	glColor4fv(component);


}
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Reflexiones Delanteras
	glColorMaterial(GL_FRONT, GL_EMISSION);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);

	// Reflexiones Traseras
	glColorMaterial(GL_BACK, GL_EMISSION);
	glColorMaterial(GL_BACK, GL_AMBIENT);
	glColorMaterial(GL_BACK, GL_DIFFUSE);
	glColorMaterial(GL_BACK, GL_SPECULAR);

 
}
  
//**********************************************************************

FuenteLuz::FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color )
{
   assert( glGetError() == GL_NO_ERROR );
   
   // guardar el indice opengl de la fuente, y comprobar que es 
   // alguno de GL_LIGHT0, GL_LIGHT1, etc.....
   
   ind_fuente = p_ind_fuente ;
   GLenum max_num_fuentes ;
   
   glGetIntegerv( GL_MAX_LIGHTS, (GLint *) &max_num_fuentes );
   assert( GL_LIGHT0 <= ind_fuente );
   assert( ind_fuente <= GL_LIGHT0 + max_num_fuentes );
   
   // inicializar parámetros de la fuente de luz
   longi_ini = p_longi_ini ;
   lati_ini  = p_lati_ini  ;
   longi = longi_ini ;
   lati  = lati_ini ;
   
   col_ambiente  = p_color ;
   col_difuso    = p_color ;
   col_especular = p_color ;
   
   assert( glGetError() == GL_NO_ERROR );
}

//----------------------------------------------------------------------

void FuenteLuz::activar()
{

GLfloat Light_position[4]={0.0, 0.0, 1.0, 0.0};

GLfloat Ambient_component[4]={col_ambiente.x,col_ambiente.y,col_ambiente.z,1};
GLfloat Difu_component[4]={col_difuso.x,col_difuso.y,col_difuso.z,1};
GLfloat Especu_component[4]={col_especular.x,col_especular.y,col_especular.z,1};

glEnable(GL_LIGHTING);
glEnable(ind_fuente);
glEnable(GL_RESCALE_NORMAL);

//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambient_component);
//glLightModelfv(GL_DIFFUSE,Difu_component);
//glLightModelfv(GL_SPECULAR,Especu_component);

glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );

glLightfv(ind_fuente, GL_AMBIENT, Ambient_component);
glLightfv(ind_fuente, GL_DIFFUSE, Difu_component);
glLightfv(ind_fuente, GL_SPECULAR, Especu_component);


glMatrixMode(GL_MODELVIEW);
glPushMatrix();
	//glLoadIdentity();
	glRotatef(longi,0.0,1.0,0.0);
	glRotatef(lati,1.0,0.0,0.0);	
	glLightfv(ind_fuente,GL_POSITION,Light_position);
glPopMatrix();


}

//----------------------------------------------------------------------

bool FuenteLuz::gestionarEventoTeclaEspecial( int key ) 
{
   bool actualizar = true ;
   const float incr = 3.0f ;
   
   switch( key )
   {
      case GLUT_KEY_RIGHT:
         longi = longi+incr ;
         break ;
      case GLUT_KEY_LEFT:
         longi = longi-incr ;
         break ;
      case GLUT_KEY_UP:
         lati = minim( lati+incr, 90.0) ;
         break ;
      case GLUT_KEY_DOWN:
         lati = maxim( lati-incr, -90.0 ) ;
         break ;
      case GLUT_KEY_HOME:
         lati  = lati_ini ;
         longi = longi_ini ;
         break ;
      default :
         actualizar = false ;
         cout << "tecla no usable para la fuente de luz." << endl << flush ;
   }
   
   //if ( actualizar )
   //   cout << "fuente de luz cambiada: longi == " << longi << ", lati == " << lati << endl << flush ;
   return actualizar ;
}
