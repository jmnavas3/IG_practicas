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
#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"
#include "textura.h"
#include "cuadro.h"
#include "p4/helicoptero.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION, SELILUMINACION} menu;

enum mallas {
  //P1
  CUBO, PIRAMIDE,
  //P2
  ESFERA, CONO, CILINDRO, LATA, HORMIGA,
  //P3
  PEONN, PEONB,
  //PROYECTO
  CHOPPER, CAZA,
  //Tamaño
  TAM
};


class Escena
{

 private:

  menu modoMenu=NADA;
  Ejes ejes;

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
  // variables que definen la posicion de la camara en coordenadas polares
  GLfloat Observer_distance;
  GLfloat Observer_angle_x;
  GLfloat Observer_angle_y;
  // variables que controlan la ventana y la transformacion de perspectiva
  GLfloat Width, Height, Front_plane, Back_plane;
  
 // ** PARÁMETROS DE LA ESCENA
  // animacion automatica
  bool automatica=true;
  // "luz general" e interruptores
  bool luz;
  std::vector<bool> interruptor{0,0,0,0,0,0,0,0};
  // rotación luz direccional
  float var_a = 0.0f;
  float var_b = 0.0f;
  bool alpha_l, beta_l;
  float rot_idle = 0.0f, rot1 = 0.0f, rot2=0.0f;
  // inicialización de las luces
  Tupla2f direccionLuz;
  Tupla3f posicionLuz;
  Tupla4f ambiental, difusa, especular;
  // escalados uniformes para varios objetos
  float escala = 30;
  float escala2 = 20;
  // {PUNTOS, LINEAS , SOLIDO , SOMBRA}       1 --> GL_FLAT
  std::vector<bool> activo{0,0,1,0}; //SOMBRA 0 --> GL_SMOOTH

  //  array de objetos
  Malla3D **objetos = new Malla3D*[TAM];
  //  fuentes de luz
  LuzDireccional       *luzDireccional = nullptr;
  LuzDireccional       *luzDefecto     = nullptr;
  LuzPosicional        *luzPosicional1 = nullptr;
  LuzPosicional        *luzPosicional2  = nullptr;
  //  materiales
  Material             *blanco_difuso   = nullptr;
  Material             *negro_especular = nullptr;

  // MODELO JERARQUICO
  Helicoptero *modelo = nullptr;

 // ** MÉTODOS DE LA ESCENA

  // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
  void clear_window();
  void eliminarObjetos(); // nuevo
  void eliminarLuces();   // nuevo

  public:

  Escena();
  ~Escena();  // nuevo
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
  void ScalefUniforme(GLfloat escalado); // nuevo
  void animarModeloJerarquico();

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
};
#endif
