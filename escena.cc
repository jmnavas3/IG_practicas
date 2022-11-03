

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   //objetos de la escena
   this->cubo = new Cubo(50.0);
   this->piramide = new PiramidePentagonal(90.0,45.0);

   // this->objetoply = new ObjPLY("./plys/beethoven");
   this->objrevolucion = new ObjRevolucion("./plys/peon",15);
   this->cilindro = new Cilindro(10,10,80.0,40.0);
   this->cono = new Cono(20,20,80.0,40.0);
   this->esfera = new Esfera(20,20,40.0);
   this->lata = new Lata(20);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();


   glPushMatrix();
      glTranslatef(-190,0,-150);
      cubo->draw(activo,1);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100,0,-150);
      piramide->draw(activo,1);
   glPopMatrix();

   // ** objetos practica 2
   
   glPushMatrix();
      glTranslatef(-70,0,-80);
      glScalef(30,30,30);
      objrevolucion->draw(activo,1);   //peón
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,-80,0);
      cilindro->draw(activo,1);
   glPopMatrix();

   glPushMatrix();
      cono->draw(activo,1);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,var,0);
      esfera->draw(activo,1);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(70,0,0);
      glScalef(70,70,70);
      lata->draw(activo,1);
   glPopMatrix();

   var += 0.5;
/*    glPushMatrix();
      glScalef(3,3,3);
      glTranslatef(0,40,0);
      objetoply->draw(activo,1);
   glPopMatrix(); */



}


//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   bool apagar_luz=false;

   switch( toupper(tecla) )
   {
      case 'Q' :
         if(modoMenu == SELVISUALIZACION) {
            modoMenu=NADA;
            std::cout << "Saliendo de modo visualización...\n";
         }
         else {
            salir=true ;
         }
         break ;
      case 'C' :
         activo[CULL] = !activo[CULL];
         break;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Modo selección de visualización\n";
         break ;
      // OPCIONES MODO VISUALIZACION
      case 'D' :
         if(modoMenu==SELVISUALIZACION) activo[PUNTOS] = !activo[PUNTOS];
         break;
      case 'L' :
         if(modoMenu==SELVISUALIZACION) activo[LINEAS] = !activo[LINEAS];
         break;
      case 'S' :
         if(modoMenu==SELVISUALIZACION) activo[SOLIDO] = !activo[SOLIDO];
         break;
      case 'G' :
         if(modoMenu==SELVISUALIZACION) activo[SUAVE] = !activo[SUAVE];
         break;
   }

   // si iluminacion activa y (puntos ó lineas ó solido) están activos, apagar luz
   apagar_luz = activo[PUNTOS] | activo[LINEAS] | activo[SOLIDO];
   if (activo[SUAVE] && apagar_luz) activo[SUAVE] = 0;

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
