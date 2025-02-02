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

typedef enum {NADA, SELOBJETO,SELVISUALIZACION} menu;
class Escena
{

   private:

 // ** PARÁMETROS P1
   std::vector<bool> activo{0,0,1,1};
   
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

   // Objetos de la escena
   Ejes ejes;
   //P1
   Cubo                 *cubo = nullptr ;
   PiramidePentagonal   *piramide= nullptr ;
   //P2
   ObjPLY               *objetoply = nullptr;
   ObjRevolucion        *objrevolucion = nullptr;
   Cilindro             *cilindro = nullptr;
   Cono                 *cono = nullptr;
   Esfera               *esfera = nullptr;
   Lata                 *lata = nullptr;

   
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
