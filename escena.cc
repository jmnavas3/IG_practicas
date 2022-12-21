

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
   this->objetos[LATA] = new Lata(10);
   this->objetos[HORMIGA] = new ObjPLY("./plys/ant");

   //*********** P3 ************
   //       objetos
   this->objetos[PEONN] = new ObjRevolucion("./plys/peon_inverso",20);
   this->objetos[PEONB] = new ObjRevolucion("./plys/peon",30);
   //       control luces
   luz = false;
   alpha_l = beta_l = false;
   posicionLuz = { 0.0 , 10.0  , 0.0 };
   direccionLuz= { 0.0 , 0.0 };
   ambiental   = { 0.3 , 0.0 , 0.4 , 1.0 };
   especular   = { 1.0 , 0.7 , 1.0 , 1.0 };
   difusa      = { 0.7 , 0.0 , 0.7 , 1.0 };
   //       fuentes de luz
   this->luzDefecto     = new LuzDireccional(direccionLuz, GL_LIGHT0, {1,1,1,1}, {1,1,1,1}, {1,1,1,1});
   this->luzPosicional1 = new LuzPosicional(posicionLuz, GL_LIGHT1, ambiental, especular, difusa);
   //       materiales
   this->blanco_difuso   = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 0.0} , {0.3, 0.3, 0.3, 1.0}, 40.0);
   //this->negro_especular = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 1.0, 1.0} , {1, 1, 1, 1.0}, 40.0);
   this->negro_especular = new Material({0.2, 0.2, 0.2, 1.0} , {1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 1.0}, 80.0);
   
   //************ PROYECTO FINAL **************
   this->modelo = new Helicoptero();
   /* this->objetos[CONO] = new Cono(20,20,1,0.5);
   this->objetos[PIRAMIDE] = new PiramidePentagonal(1,0.5);
   this->objetos[CILINDRO] = new Cilindro(20,20,1,0.5);
   this->objetos[ESFERA] = new Esfera(20,20,0.5);
   this->objetos[CHOPPER] = new ObjPLY("./plys/chopper");
   this->objetos[CAZA] = new ObjPLY("./plys/f16");
   */
   this->objetos[ESFERA]->setMaterial(*negro_especular);
   this->objetos[LATA]->setMaterial(*blanco_difuso);
   this->objetos[PEONN]->setMaterial(*negro_especular);
   this->objetos[PEONB]->setMaterial(*blanco_difuso);

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
   
   // Definir transformación de vista
	change_observer();

   // Fijar luz a la cámara
   glPushMatrix();                           // C := M (copia de M en C)
      glLoadIdentity();                      // M := Identidad
      luzDefecto->activar(interruptor[0]);   // luz direccional fijada a la cámara
   glPopMatrix();                            // restaurar transformaciones de la cámara

   if(luz){
         glDisable(GL_LIGHTING);
         ejes.draw();
         glEnable(GL_LIGHTING);
   }else
      ejes.draw();
   
   luzPosicional1->activar(interruptor[1]);

   // MODELO JERARQUICO
   this->modelo->draw(activo,luz);
/*
   if(automatica){
   // ** objetos PROYECTO FINAL (chopper + f16)
      // estructura helicoptero
   glPushMatrix();
      // glRotatef(-rot_idle,0,1,0);
      glPushMatrix();
         // cuerpo
         glTranslatef(0,-15,0);
         ScalefUniforme(20);
         glRotatef(-15, 0, 0, 1);
         glScalef(3,2,2);
         objetos[ESFERA]->draw(activo,luz);
      glPopMatrix();
      glPushMatrix();
         glScalef(15,10,5);
         objetos[CILINDRO]->draw(activo,luz);
      glPopMatrix();
         // cola
         glTranslatef(-20,-5,0);
         glRotatef(90,0,0,1);
         glScalef(10,70,10);
         objetos[CONO]->draw(activo,luz);
         glPushMatrix();
            glTranslatef(0,1,0);
            glScalef(0.5,1,0.5);
            objetos[CUBO]->draw(activo,luz);
         glPopMatrix();
   glPopMatrix();
      // ROTOR PRINCIPAL
   glPushMatrix();
      ScalefUniforme(8);
      glPushMatrix();
         glRotatef(rot_idle, 0, 1, 0);
         glPushMatrix();
            glTranslatef(0,1,0);
            glScalef(0.25,1,0.25);
            objetos[CILINDRO]->draw(activo,luz);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,2,0);
            glPushMatrix();
               glScalef(1,0.5,1);
               objetos[CILINDRO]->draw(activo,luz);
            glPopMatrix();
            // hélice_dcha
            glPushMatrix();
               glRotatef(180,0,1,0);
               glTranslatef(-1,0.125,0);
               ScalefUniforme(0.25);
               objetos[CUBO]->draw(activo,luz);
               glPushMatrix();
                  glTranslatef(-25.25,0.25,0);
                  glScalef(50,0.1,6);
                  objetos[CUBO]->draw(activo,luz);
               glPopMatrix();
            glPopMatrix();
            // hélice_izda
            glPushMatrix();
               glTranslatef(-1,0.125,0);
               ScalefUniforme(0.25);
               objetos[CUBO]->draw(activo,luz); // union de la pala con la base
               glPushMatrix();
                  glTranslatef(-25.25,0.25,0);
                  glScalef(50,0.1,6);
                  objetos[CUBO]->draw(activo,luz);
               glPopMatrix();
            glPopMatrix();
         glPopMatrix();
      glPopMatrix();
   glPopMatrix();
   }
*/   


   if(automatica){
   glPushMatrix();
      //P3 peones blanco y negro
      ScalefUniforme(escala);
      glTranslatef(3,0,1);
      objetos[PEONB]->draw(activo,luz);
      glPushMatrix();
         glTranslatef(0,0,-2);
         objetos[PEONN]->draw(activo,luz);
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

      glPushMatrix();
         glTranslatef(0,0,-15);
         ScalefUniforme(0.3);
         objetos[HORMIGA]->draw(activo,luz);
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
   }

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

   // OPCIONES MODO VISUALIZACION (Leeme.txt para ver funcionamiento)
   if ( modoMenu == SELVISUALIZACION || modoMenu == SELILUMINACION ) {
      switch ( toupper(tecla) )
      {
      case 'Q' :
         modoMenu = NADA;
         if(alpha_l || beta_l){
            cout << "\nEstado angulo: sin seleccionar\n";
         }
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
            cout << "\nEstado angulo: ALPHA\n < : Decrementar ángulo\n > : Incrementar ángulo \n";
         }
         break;
      case 'B':
         if(modoMenu==SELILUMINACION){
            alpha_l = false;
            beta_l = true;
            cout << "\nEstado angulo: BETA\n < : Decrementar ángulo\n > : Incrementar ángulo \n";
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
      cout << "SELECCIONAR TIPO DE VISUALIZACIÓN\nP:puntos\nL:lineas\nS:solido\nI:activar iluminacion plana/suave\n" <<
            " 0-" << Luz::nluces <<  ":apagar/encender luz\nA:seleccionar ALPHA\nB:seleccionar BETA\n";
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

   delete modelo;
   delete blanco_difuso;
   delete negro_especular;

   blanco_difuso=nullptr;
   negro_especular=nullptr;
   modelo = nullptr;

   std::cout << "destructor escena\n";
   
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

/**
 * @brief Invoca a los diferentes métodos que alteran los valores
 * de rotación o traslación del modelo jerárquico.
 * 
 * Escena no debe conocer ni cómo se llaman esos atributos ni su
 * velocidad
 */
void Escena::animarModeloJerarquico(){
   /* if( automatica ){
      modelo->moverGancho(0.05);
      modelo->modificaRotacionCola(0.05);
      modelo->modificaRotacionPrincipal(1.0);
   } */
}