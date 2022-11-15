

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
   
   //*********** P1 ************
   objetos[CUBO] = new Cubo();
   objetos[PIRAMIDE] = new PiramidePentagonal();
   //*********** P2 ************
   objetos[ESFERA] = new Esfera(20,20);   
   objetos[CONO] = new Cono(20,20);
   objetos[CILINDRO] = new Cilindro(10,10);
   objetos[LATA] = new Lata(20);
   //*********** P3 ************
   //       control luces
   luz = false;
   alpha_l = beta_l = false;
   posicionLuz = { 0.0 , 20  , 0.0 };
   ambiental   = { 1.0 , 1.0 , 1.0 , 1.0 };
   difusa      = { 1.0 , 0.0 , 1.0 , 1.0 };
   especular   = { 1.0 , 0.0 , 1.0 , 1.0 };
   //       fuentes de luz
   this->luzDefecto     = new LuzDireccional({Observer_angle_x,Observer_angle_y}, GL_LIGHT0, {1,1,1,1}, {1,1,1,1}, {1,1,1,1});
   this->luzPosicional1 = new LuzPosicional(posicionLuz, GL_LIGHT1, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0}, {1.0,0.0,0.0,1.0});
   //       materiales
   this->blanco_difuso   = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 0.0} , {0.3, 0.3, 0.3, 1.0}, 40.0);
   this->negro_especular = new Material({0.2, 0.2, 0.2, 1.0} , {1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 1.0}, 80.0);
   //       objetos
   objetos[PEONN] = new ObjRevolucion("./plys/peon_inverso",20);
   objetos[PEONB] = new ObjRevolucion("./plys/peon",30);
   objetos[PEONN]->setMaterial(*negro_especular);
   objetos[PEONB]->setMaterial(*blanco_difuso);
   // nota: los objetos a los que no se les ha asignado ningún material, ya tienen uno por defecto
   /* //************ PROYECTO FINAL **************
   // P1
   this->cubo = new Cubo();
   this->piramide = new PiramidePentagonal();
   // P2
   this->esfera = new Esfera(20,20);
   this->cono = new Cono(20,20);
   this->cilindro = new Cilindro(10,10);
   this->lata = new Lata(20);
   // P3
   this->luzPosicional2  = new LuzPosicional(posicionLuz, GL_LIGHT2, ambiental, especular, difusa);
   this->luzDireccional = new LuzDireccional({0.0f,0.0f}, GL_LIGHT3, ambiental, especular, difusa);
   this->peonNegro = new ObjRevolucion("./plys/peon_inverso",20);
   this->peonBlanco = new ObjRevolucion("./plys/peon",30);
   this->esfera->setMaterial(Material());
   this->cono->setMaterial(Material());
   this->cilindro->setMaterial(Material());
   this->lata->setMaterial(*negro_especular);
   this->peonNegro->setMaterial(*negro_especular);
   this->peonBlanco->setMaterial(*blanco_difuso);
   // Proyecto Final
   this->helicoptero = new ObjPLY("./plys/chopper");
   this->caza = new ObjPLY("./plys/f16");
   this->helicoptero->setMaterial(*negro_especular);
   this->caza->setMaterial(*blanco_difuso);
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

   // FLAGS INICIALES
   glEnable(GL_CULL_FACE);
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
   // Limpiar ventana
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   
   // Activar luces
   if(luz) glEnable(GL_LIGHTING);
   else    glDisable(GL_LIGHTING);
   
   // Rotar luz direccional
   if(alpha_l){
      luzDefecto->variarAnguloAlpha(var_a);
      var_a=0;
   }
   if(beta_l){
      luzDefecto->variarAnguloBeta(var_b);
      var_b=0;
   }
   
	change_observer();

   if(luz){
   glPushMatrix();
      glDisable(GL_LIGHTING);
      ejes.draw();
      glEnable(GL_LIGHTING);
   glPopMatrix();
      // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiental);
      // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
      // glEnable(GL_COLOR_MATERIAL);
      // ejes.draw();
      // glDisable(GL_COLOR_MATERIAL);
   }else
      ejes.draw();
   

   
   luzPosicional1->activar(interruptor[1]);
   glPushMatrix();
      //P3 peones blanco y negro
      ScalefUniforme(escala);
      glTranslatef(3,0,1);
      objetos[PEONN]->draw(activo,luz);
      glPushMatrix();
         glTranslatef(0,0,-2);
         objetos[PEONB]->draw(activo,luz);
      glPopMatrix();
   glPopMatrix();
  
   glPushMatrix();
      ScalefUniforme(escala2);
      // ** objetos practica 2
      glPushMatrix();
         glTranslatef(0,0,-5);
         objetos[CILINDRO]->draw(activo,luz);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0,0,-2);
         objetos[CONO]->draw(activo,luz);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0,0,1);
         objetos[ESFERA]->draw(activo,luz);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0,0,-7);
         ScalefUniforme(3);
         objetos[LATA]->draw(activo,luz);
      glPopMatrix();
   glPopMatrix();

   glPushMatrix();
      ScalefUniforme(escala2);
      glTranslatef(-3,0,0);
   // ** objetos practica 1
      glPushMatrix();
         glTranslatef(0,0,1);
         objetos[CUBO]->draw(activo,luz);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0,0,-1);
         objetos[PIRAMIDE]->draw(activo,luz);
      glPopMatrix();
   glPopMatrix();
   
   /* // ** objetos PROYECTO FINAL (chopper + f16)
   glPushMatrix();
      glTranslatef(-30,70,0);
      glPushMatrix();
         glRotatef(180,0,1,0);
         ScalefUniforme(10);
         glTranslatef(-10,10,0);
         caza->draw(activo,luz);  // f16 caza
      glPopMatrix();
      glPushMatrix();
         // OJO: no tiene ningún punto centrado en el origen, aunque está muy cerca (cuidado con rotate)
         glTranslatef(20,50,0);
         glRotatef(90,0,1,0);
         glRotatef(-90,1,0,0);
         // lo trasladamos al eje X para poder aplicar rotacion
         glTranslatef(0,-10,5);
         helicoptero->draw(activo,luz);   // chopper helicoptero
      glPopMatrix();
   glPopMatrix();
    */
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
         if (activo[PUNTOS]) activo[PUNTOS] = false;
         if (activo[LINEAS]) activo[LINEAS] = false;
         if (!activo[SOLIDO]) activo[SOLIDO] = true;
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
            var_a=0.5;
         if(modoMenu==SELILUMINACION && beta_l)
            var_b=0.5;
         break;
      case '<':
         if(modoMenu==SELILUMINACION && alpha_l)
            var_a= -0.5;
         if(modoMenu==SELILUMINACION && beta_l)
            var_b= -0.5;
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
      cout << "SELECCIONAR TIPO DE VISUALIZACIÓN\nP:puntos\nL:lineas\nS:solido\nI:iluminacion" <<
            " 0-" << Luz::nluces <<  ":INTERRUPTORES\n";
      break ;
   default:
      break;
   }

   if(modoMenu==SELILUMINACION)
      for(int i = 0; i < Luz::nluces; i++){
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
   luzDefecto->activar(interruptor[0]);
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-------------------- Métodos adicionales añadidos a la escena -------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
 * @brief Escalado uniforme
 * 
 * @param escalado aplicado a los ejes X Y Z
 */
void Escena::ScalefUniforme(GLfloat escalado)
{
   if(escalado != 0)
   glScalef(escalado,escalado,escalado);
}

/**
 * @brief Destructor de los punteros a heap usados para evitar pérdida de memoria
 * 
 */
Escena::~Escena()
{
   eliminarObjetos();
   eliminarLuces();

   delete blanco_difuso;
   delete negro_especular;

   blanco_difuso=nullptr;
   negro_especular=nullptr;
   
   /* // Mallas sin array
   delete cubo;
   delete piramide;
   delete esfera;
   delete cono;
   delete cilindro;
   delete lata;
   delete peonNegro;
   delete peonBlanco;

   cubo = nullptr;
   piramide = nullptr;
   esfera = nullptr;
   cono = nullptr;
   cilindro = nullptr;
   lata = nullptr;
   peonNegro = nullptr;
   peonBlanco = nullptr;  */

}


/**
 * @brief Elimina los objetos Malla3D que se han inicializado.
 * 
 */
void Escena::eliminarObjetos()
{
   for (int i = 0; i < TAM; i++)
   {
      if(objetos[i] != nullptr){
         delete objetos[i];
         objetos[i] = nullptr;
      }
   }

   delete [] objetos;
   objetos=nullptr;
}


/**
 * @brief Elimina las luces que se han inicializado
 * 
 */
void Escena::eliminarLuces()
{
   if (luzDireccional != nullptr) delete luzDireccional;
   if (luzDefecto != nullptr)     delete luzDefecto;
   if (luzPosicional1 != nullptr) delete luzPosicional1;
   if (luzPosicional2 != nullptr) delete luzPosicional2;

   luzDireccional = nullptr;
   luzDefecto = nullptr;
   luzPosicional1 = nullptr;
   luzPosicional2 = nullptr;
}