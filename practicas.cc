//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "auxiliar.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;

// atributo estático de la clase Luz
int Luz::nluces = 0;

//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
	if ( escena != nullptr )
      escena->dibujar();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
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

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir )   {
		delete escena;
        escena = nullptr ;
		exit(0);
	}
   else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
		escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}

/**
 * @brief Función llamada cuando el gestor de eventos está libre
 * Se encarga de animar la escena
 */
void funcion_idle(){
   if(escena!=NULL)
      escena->animarModeloJerarquico();
   glutPostRedisplay();
}

void infoClic(int x, int y){
   
   // int w = glutGet(GLUT_WINDOW_WIDTH);
   int h = glutGet(GLUT_WINDOW_HEIGHT);
   GLbyte color[4];
   GLfloat profundidad;
   GLuint indice;
   
   glReadPixels(x, h -y -1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color );
   glReadPixels(x, h -y -1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &profundidad );
   glReadPixels(x, h -y -1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &indice );
   
   printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
         x, y, color[0], color[1], color[2], color[3], profundidad, indice);
}

/**
 * @brief Función llamada cuando el gestor de eventos detecta
 * la pulsación de botones del ratón.
 * @param boton GLUT_{LEFT,MIDDLE,RIGHT}_BUTTON
 * @param estado GLUT_{UP,DOWN} (up: soltado, down: pulsado)
 * @param x en coord. de pantalla
 * @param y en coord. de pantalla
 * 
 * Callback --> glutMouseFunc
 * 
 */
void clickRaton( int boton, int estado, int x, int y ) {
   if ( boton == GLUT_RIGHT_BUTTON ) {
      if ( estado == GLUT_DOWN ) {
         escena->moviendoCamara = true;
         escena->xant = x;
         escena->yant = y;
      } else
         escena->moviendoCamara = false;
   }
   else if ( boton == 3 || boton == 4 ){
      escena->haciendoZoom = (boton==3) ? 1 : -1;
      escena->ratonMovido(x,y);
   }
   
   // INFO DE PIXEL Y RATÓN
   else if ( boton == GLUT_LEFT_BUTTON && estado == GLUT_UP ){
      infoClic(x,y);
   }
   
   glutPostRedisplay();
}


/**
 * @brief Función llamada cuando el gestor de eventos detecta
 * el movimiento del ratón mientras se pulsa un botón
 * @param x de ratón en coord. de pantalla
 * @param y de ratón en coord. de pantalla
 * 
 * Callback --> glutMotionFunc
 */
void ratonMovido( int x, int y ) {
   escena->ratonMovido(x,y);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main( int argc, char **argv )
{
   using namespace std ;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit( &argc, argv );

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   // SUSTITUIR EL NOMBRE DEL ALUMNO
   glutCreateWindow("Practicas IG: Jose Maria Navas Cabrera");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   // asignación de la función llamada "funcion_idle" al evento correspondiente
   glutIdleFunc( funcion_idle );

   // asignación de la función llamada "clickRaton" al evento correspondiente
   glutMouseFunc( clickRaton );

   // asignación de la función llamada "ratonMovido" al evento correspondiente
   glutMotionFunc( ratonMovido );

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );



   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
