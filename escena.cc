

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

   //** objetos P1
   #ifdef P1
   this->cubo = new Cubo(50.0);
   this->piramide = new PiramidePentagonal(90.0,45.0);
   #endif
   //** objetos P2
   #ifdef P2
   this->lata = new Lata(20);
   this->esfera = new Esfera(20,20,40.0);
   this->cono = new Cono(20,20,80.0,40.0);
   this->cilindro = new Cilindro(10,10,80.0,40.0);
   // this->objetoply = new ObjPLY("./plys/beethoven");
   #endif

   //** objetos + iluminacion P3
    // Cap.6, Color, Pág.138. RedBook OpenGL: "if u want realistic effect, set GL_SPECULAR = GL_DIFFUSE"
   luz = false;
   posicionLuz = Tupla3f(30.0f, 30.0f, 50.0f);
   Tupla4f ambiental(0.6, 0.6, 1.0, 1.0);
   Tupla4f difusa(0.5,0.4,0.7,1.0);
   Tupla4f especular(1.0,1.0,1.0,0.7);

   this->peon = new ObjRevolucion("./plys/peon",20);
   this->luzPosicional = new LuzPosicional(posicionLuz, GL_LIGHT1, ambiental, especular, difusa);
   this->cubo = new Cubo();
   this->piramide = new PiramidePentagonal();

   Material nuevo(ambiental,difusa,especular,100.0);
   Material defecto;
   this->cubo->setMaterial(defecto);
   this->piramide->setMaterial(nuevo);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(RGBA)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

   // FLAGS INICIALES
   // glEnable(CULL_FACE);
   glEnable(GL_NORMALIZE);

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

   glScalef(30.0,30.0,30.0);
   if(luz) glEnable(GL_LIGHTING);
   else glDisable(GL_LIGHTING);
   
   // glEnable(GL_LIGHT0);
   // luzPosicional->activar();


   #ifdef P1
   glPushMatrix();
      glTranslatef(-190,0,-150);
      cubo->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100,0,-150);
      piramide->draw(activo,luz);
   glPopMatrix();
   #endif

   // ** objetos practica 2
   #ifdef P2
   glPushMatrix();
      glTranslatef(-70,0,-80);
      glScalef(30,30,30);
      peon->draw(activo,luz);   //peón
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,-80,0);
      cilindro->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      cono->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,var,0);
      esfera->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(70,0,0);
      glScalef(70,70,70);
      lata->draw(activo,luz);
   glPopMatrix();
   #endif

   // ** objetos práctica 3
   // a nivel de iluminacion, se define el material del peon en el constructor de la escena
   // en caso de que el booleano luz este activo, se enciende la luz 0
   // dentro del draw, antes de DrawElements, se aplica dicho material
   // ERROR con Esfera, Cono y Cilindro por rotar sobre la base o algo asi
   #ifdef P3
   glPushMatrix();
      luzPosicional->activar();
      cubo->draw(activo,luz);   //peón
   glPopMatrix();

   glPushMatrix();
      glTranslatef(2,0,0);
   glEnable(GL_LIGHT0);
   piramide->draw(activo,luz);
   glPopMatrix();
   #endif




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
   //bool apagar_luz=false;

   // OPCIONES MODO VISUALIZACION
   if ( modoMenu == SELVISUALIZACION ) {
      switch ( toupper(tecla) )
      {
      case 'Q' :
         modoMenu = NADA;
         cout << "MENU PRINCIPAL\nV:seleccionar modo visualización\nQ:salir\n";
         break;
      case 'C' :
         activo[CULL] = !activo[CULL];
         luz = false;
         break;
      case 'P' :
         activo[PUNTOS] = !activo[PUNTOS];
         luz = false;
         break;
      case 'L' :
         activo[LINEAS] = !activo[LINEAS];
         luz = false;
         break;
      case 'S' :
         activo[SOLIDO] = !activo[SOLIDO];
         luz = false;
         break;
      case 'I' :
         activo[SOMBRA] = !activo[SOMBRA];
         luz = true;
         break;
      default :
         break;
      }
   }
   // MENU PRINCIPAL
   else if (modoMenu == NADA)
   switch( toupper(tecla) )
   {
   case 'Q' :
      salir=true ;
      break ;
   case 'V' :
      modoMenu=SELVISUALIZACION;
      cout << "SELECCIONAR TIPO DE VISUALIZACIÓN\nP:puntos\nL:lineas\nS:solido\nC:caras trasesras\nI:iluminacion\n";
      break ;
   default:
      break;
   }

   // si iluminacion activa y (puntos ó lineas ó solido) están activos, apagar luz
   //apagar_luz = activo[PUNTOS] | activo[LINEAS] | activo[SOLIDO];
   //if (activo[SUAVE] && apagar_luz) activo[SUAVE] = 0;

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
