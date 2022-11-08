#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "objply.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "cubo.h"
#include "piramidepentagonal.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "lata.h"
// luces
#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION, SELILUMINACION} menu;
class Escena
{

  private:

 // ** PARÁMETROS DE OBJETOS

  // {PUNTOS,LINEAS,SOLIDO,CULL,TIPOILUMINACION}
  std::vector<bool> activo{0,0,1,1,0}; //iluminacion 0 --> GL_SMOOTH
  float var_a = 0.0f, var_b=0.0f;
  float escala = 30.0f;
   
 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
      // variables que definen la posicion de la camara en coordenadas polares
  GLfloat Observer_distance;
  GLfloat Observer_angle_x;
  GLfloat Observer_angle_y;

  // variables que controlan la ventana y la transformacion de perspectiva
  GLfloat Width, Height, Front_plane, Back_plane;

  // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


  void clear_window();

  menu modoMenu=NADA;

 // ** OBJETOS DE LA ESCENA

  Ejes ejes;
  
  // P1
  Cubo                 *cubo = nullptr ;
  PiramidePentagonal   *piramide= nullptr ;
  
  // P2
  ObjPLY               *objetoply = nullptr;
  ObjRevolucion        *peon = nullptr;
  Cilindro             *cilindro = nullptr;
  Cono                 *cono = nullptr;
  Esfera               *esfera = nullptr;
  Lata                 *lata = nullptr;

  // P3
  //    objetos
  ObjRevolucion        *prueba = nullptr;
  ObjRevolucion        *peonBlanco = nullptr;
  ObjRevolucion        *peonNegro = nullptr;
  //    fuentes de luz
  LuzDireccional       *luzDireccional = nullptr;
  LuzPosicional        *luzPosicional = nullptr;
  LuzPosicional        *luzPosicional1 = nullptr;
  //    control luces
  Tupla3f posicionLuz;
  Tupla4f ambiental, difusa, especular;
  float luz, alpha_l, beta_l;
  //    materiales
  Material             *defecto         = nullptr;
  Material             *blanco_difuso   = nullptr;
  Material             *negro_especular = nullptr;

   
  public:

  Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
