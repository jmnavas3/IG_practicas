

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
   this->cubo = new Cubo();
   this->piramide = new PiramidePentagonal();
   //** objetos P2
   std::cout << "\nGenerando esfera...\n";
   this->esfera = new Esfera(20,20,40.0);
   std::cout << "Generando peon... \n";
   this->peon = new ObjRevolucion("./plys/peon",10);
   std::cout << "Generando cono...\n";
   this->cono = new Cono(20,20,80.0,40.0);
   this->cono->setMaterial(Material());
   std::cout << "Generando cilindro...\n";
   this->cilindro = new Cilindro(10,10);
   this->cilindro->setMaterial(Material());
   // std::cout << "Generando lata... ";
   // this->lata = new Lata(20);
   // this->objetoply = new ObjPLY("../../ideas/chopper");
  
   //*********** P3 ************
   //       control luces
   luz = false;
   posicionLuz = {0.0f,0.0f,5.0f};
   ambiental   = { 1.0 , 1.0 , 0.0 , 1.0 };
   difusa      = { 1.0 , 1.0 , 0.0 , 1.0 };
   especular   = { 1.0 , 1.0 , 0.0 , 1.0 };
   //       fuentes de luz
   this->luzEspectador  = new LuzPosicional(posicionLuz, GL_LIGHT0, ambiental, especular, difusa);
   this->luzDireccional = new LuzDireccional({0.0f,0.0f}, GL_LIGHT1, ambiental, especular, difusa);
   this->luzPosicional1 = new LuzPosicional(posicionLuz, GL_LIGHT2, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0});
   //       materiales
   this->defecto         = new Material();
   this->blanco_difuso   = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 0.0} , {1.0, 0.9, 0.9, 0.9}, 40.0);
   this->negro_especular = new Material({0.2, 0.2, 0.2, 1.0} , {1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 1.0}, 40.0);
   //       objetos
   /* 
   this->esfera = new Esfera(20,20,2);
   this->peonNegro = new ObjRevolucion("./plys/peon_inverso",20);
   this->peonBlanco = new ObjRevolucion("./plys/peon",30);

   this->esfera->setMaterial(*negro_especular);
   this->peonNegro->setMaterial(*negro_especular);
   this->peonBlanco->setMaterial(*blanco_difuso);
   */

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

   // **FLAGS INICIALES**
   // glEnable(CULL_FACE); // comentado solo para pruebas
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
   // luz que cambia con el espectador
   luzEspectador->activar(interruptor[0]);
	change_observer();
   ejes.draw();

   if(luz) glEnable(GL_LIGHTING);
   else    glDisable(GL_LIGHTING);
   
   
  /*  //P3 peones blanco y negro
   glPushMatrix();
      if(alpha_l){
         luzDireccional->variarAnguloAlpha(var_a);
         var_a=0;
      }
      if(beta_l){
         luzDireccional->variarAnguloBeta(var_b);
         var_b=0;
      }
      luzDireccional->cambiarAngulo();
      luzDireccional->activar(interruptor[2]);
   glPopMatrix();
   glPushMatrix();
      glScalef(escala,escala,escala);
      luzPosicional1->activar(interruptor[1]);
      peonNegro->draw(activo,luz);
      glPushMatrix();
         glTranslatef(-3,0,0);
         peonBlanco->draw(activo,luz);
      glPopMatrix();
      // P3 esfera
      glPushMatrix();
         glTranslatef(3,0,0);
         esfera->draw(activo,luz);
      glPopMatrix();
   glPopMatrix();
   */

   


   glPushMatrix();
      glTranslatef(-190,0,-150);
      glScalef(30,30,30);
      cubo->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100,0,-150);
      glScalef(30,30,30);
      piramide->draw(activo,luz);
   glPopMatrix();

   // ** objetos practica 2
   glPushMatrix();
      glTranslatef(-70,0,-80);
      glScalef(30,30,30);
      peon->draw(activo,luz);   //peón
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,-90,0);
      glScalef(40,40,40);
      cilindro->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      cono->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,120,0);
      esfera->draw(activo,luz);
   glPopMatrix();

   /* glPushMatrix();
      glTranslatef(70,0,0);
      glScalef(70,70,70);
      lata->draw(activo,luz);
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

   // OPCIONES MODO VISUALIZACION
   if ( modoMenu == SELVISUALIZACION || modoMenu == SELILUMINACION ) {
      switch ( toupper(tecla) )
      {
      case 'Q' :
         modoMenu = NADA;
         alpha_l = beta_l = false;
         cout << "MENU PRINCIPAL\nV:seleccionar modo visualización\nQ:salir\n";
         break;
      case 'C' : // opcion para pruebas
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
         modoMenu = SELILUMINACION;
         break;
      case 'A':
         if(modoMenu==SELILUMINACION){
            alpha_l = true;
            beta_l = false;
         }
         break;
      case 'B':
         if(modoMenu==SELILUMINACION){
            alpha_l = false;
            beta_l = true;
         }
         break;
      case '>':
         if(modoMenu==SELILUMINACION && alpha_l)
            var_a=4;
         if(modoMenu==SELILUMINACION && beta_l)
            var_b=4;
         break;
      case '<':
         if(modoMenu==SELILUMINACION && alpha_l)
            var_a= -4;
         if(modoMenu==SELILUMINACION && beta_l)
            var_b= -4;
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
      cout << "SELECCIONAR TIPO DE VISUALIZACIÓN\nP:puntos\nL:lineas\nS:solido\nC:caras trasesras\nI:iluminacion\n0-2:INTERRUPTORES\n";
      break ;
   default:
      break;
   }

   if(modoMenu==SELILUMINACION)
      for(int i = 0; i < interruptor.size(); i++){
         if((tecla-'0')==i){
            interruptor[i] = !interruptor[i];
         }
      }
   


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
