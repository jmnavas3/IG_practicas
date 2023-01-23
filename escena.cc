

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

   //*********** P6 ************
   moviendoCamara = false;
   camaras[0] = new Camara();
   camaras[1] = new Camara({0,5,200},{0,0,0});
   camaras[2] = new Camara({30,10,200},{0,5,0});
   haciendoZoom = 0;
   xant = 0;
   yant = 0;
   
   //*********** P1 ************
   objetos[CUBO] = new Cubo();
   objetos[PIRAMIDE] = new PiramidePentagonal();
   //*********** P2 ************
   // objetos[ESFERA] = new Esfera(20,20);
   objetos[CONO] = new Cono(20,20);
   objetos[CILINDRO] = new Cilindro(20,20);
   //this->objetos[LATA] = new Lata(10);
   this->objetos[HORMIGA] = new ObjPLY("./plys/ant");
   this->objetos[CAZA] = new ObjPLY("./plys/f16");
   //*********** P3 ************
   //       objetos
   this->objetos[PEONB] = new ObjPLY("./plys/seta");
   this->objetos[PEONN] = new ObjRevolucion("./plys/peon",30);
   this->objetos[OCEANO] = new ObjPLY("./plys/ocean1");
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
   this->luzAnimada = new LuzAnimada();
   //       materiales
   this->blanco_difuso   = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 0.0} , {0.3, 0.3, 0.3, 1.0}, 40.0);
   //this->negro_especular = new Material({1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 1.0, 1.0} , {1, 1, 1, 1.0}, 40.0);
   this->negro_especular = new Material({0.2, 0.2, 0.2, 1.0} , {1.0, 1.0, 1.0, 1.0} , {0.0, 0.0, 0.0, 1.0}, 80.0);
   //*********** P5 ************
   material_text = new Material({1.0, 1.0, 1.0, 1.0} , {1.0, 1.0, 1.0, 1.0} , {0.3, 0.3, 0.3, 1.0}, 80.0);
   objetos[ESFERA] = new Esfera(40,40,false,20);
   objetos[LATA] = new Lata(30,true);
   objetos[CHOPPER] = new Cuadro();
   this->objetos[ESFERA]->setMaterial(*material_text);
   this->objetos[LATA]->setMaterial(*material_text);
   this->objetos[CHOPPER]->setMaterial(*material_text);
   
   //************ PROYECTO FINAL **************
   this->modelo = new HelicopteroCarga();
   gradoSeleccionado = -1;
   
   this->objetos[PEONN]->setMaterial(*negro_especular);
   this->objetos[PEONB]->setMaterial(*blanco_difuso);
   this->objetos[CAZA]->setMaterial(*negro_especular);

}


//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(RGBA)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);

   std::cout << "ancho=" << UI_window_width << " alto=" << UI_window_height << "\n";

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   camaras[cam_activa]->reajustar(UI_window_width, UI_window_height);
   cambia_proyeccion();
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
	// change_observer();
   change_observer_p6();

   luzAnimada->draw(activo,interruptor[2]);
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
   glPushMatrix();
      glTranslatef(0,120,0);
      this->modelo->draw(activo,luz);
   glPopMatrix();
   
   glPushMatrix();
      ScalefUniforme(escala);
      
      if(objeto==LATA)
         ScalefUniforme(2);
      else if(objeto==ESFERA)
         ScalefUniforme(0.1);
      else if (objeto==HORMIGA)
         ScalefUniforme(0.5);

      objetos[objeto]->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,100,-200);
      glRotatef(180,0,1,0);
      ScalefUniforme(15);
      objetos[CAZA]->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,0,-200);
      ScalefUniforme(100);
      objetos[CHOPPER]->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0,-200,-200);
      glRotatef(-90,1,0,0);
      ScalefUniforme(50);
      objetos[OCEANO]->draw(activo,luz);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-50,-200,-500);
      glRotatef(-90,1,0,0);
      ScalefUniforme(5);
      objetos[PEONB]->draw(activo,luz);
   glPopMatrix();

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-------------------- Métodos adicionales añadidos a la escena -------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// método que se invoca cada vez que se mueve el ratón con algún
// botón pulsado. Sólo realiza acciones si es el botón derecho
void Escena::ratonMovido(int x, int y)
{
   if (moviendoCamara) {
      // std::cout << "x=" << x-xant << " y=" << y-yant << "  ";
      camaras[cam_activa]->girar(x - xant, y - yant, 0.01);
      xant = x;
      yant = y;
   }

   if (haciendoZoom!=0) {
      camaras[cam_activa]->zoom(haciendoZoom);
      cambia_proyeccion();
      haciendoZoom=0;
   }
}

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

   if(modelo!=nullptr) delete modelo;
   if(blanco_difuso != nullptr) delete blanco_difuso;
   if(negro_especular != nullptr) delete negro_especular;
   if(material_text != nullptr) delete material_text;

   blanco_difuso=nullptr;
   negro_especular=nullptr;
   modelo = nullptr;

}

/**
 * @brief Elimina los objetos Malla3D que se han inicializado.
 * 
 */
void Escena::eliminarObjetos()
{
   for (int i = 0; i < TAM; i++) {
      if(objetos[i] != nullptr){
         delete objetos[i];
         objetos[i] = nullptr;
      }
   }
   for (int i = 0; i < NUM_CAMS; i++) {
      if(camaras[i] != nullptr){
         delete camaras[i];
         camaras[i] = nullptr;
      }
   }

   delete [] objetos;
   delete [] camaras;
   
   objetos=nullptr;
   camaras=nullptr;
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
   if (luzAnimada != nullptr) delete luzAnimada;

   luzDireccional = nullptr;
   luzDefecto = nullptr;
   luzPosicional1 = nullptr;
   luzPosicional2 = nullptr;
   luzAnimada = nullptr;
}

/**
 * @brief Invoca a los diferentes métodos que alteran los valores
 * de rotación o traslación del modelo jerárquico.
 * 
 */
void Escena::animarModeloJerarquico(){
   if( automatica ){
      luzAnimada->animar();
      modelo->animar(incremento);
      incremento = 0;
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y ) {
   using namespace std ;
   // cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   string menuprincipal = "\tMENU PRINCIPAL\nV:seleccionar modo visualización\nA:activar/desactivar animacion automatica\nM:activar seleccion grado libertad\nQ:salir\n \
+ ó - : variar velocidad de animación\nC: activar selección de cámaras\n";

   if ( modoMenu == SELVISUALIZACION || modoMenu == SELILUMINACION )
   switch ( toupper(tecla) ) {
   // ------------------- OPCIONES VISUALIZACION ---------------
   case 'Q' :
      if(alpha_l || beta_l) cout << "\nALPHA Y BETA REESTABLECIDOS\n";
      cout << menuprincipal;
      alpha_l = beta_l = false;
      modoMenu = NADA;
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
   // ----------------- OPCIONES ILUMINACION ---------------
   case 'I' :
      activo[SOMBRA] = !activo[SOMBRA];
      if (activo[PUNTOS])  activo[PUNTOS] = false;
      if (activo[LINEAS])  activo[LINEAS] = false;
      if (!activo[SOLIDO]) activo[SOLIDO] = true;
      luz = true;
      modoMenu = SELILUMINACION;
      break;
   case 'A':
      if(modoMenu==SELILUMINACION){
         alpha_l = true;
         beta_l = false;
         cout << "\nALPHA\n < : Decrementar ángulo\n > : Incrementar ángulo \n";
      }
      break;
   case 'B':
      if(modoMenu==SELILUMINACION){
         alpha_l = false;
         beta_l = true;
         cout << "\nBETA\n < : Decrementar ángulo\n > : Incrementar ángulo \n";
      }
      break;
   case '>':
      if(modoMenu==SELILUMINACION && alpha_l) var_a=0.5;
      if(modoMenu==SELILUMINACION && beta_l)  var_b=0.5;
      break;
   case '<':
      if(modoMenu==SELILUMINACION && alpha_l) var_a= -0.5;
      if(modoMenu==SELILUMINACION && beta_l)  var_b= -0.5;
      break;
   default :
      break;
   }
   // ---------------- MENU PRINCIPAL ----------------
   else if (modoMenu == NADA)
   switch( toupper(tecla) )
   {
   case 'O' :
      objeto++;
      objeto %= TAM-1;
      break;
   case 'C':
      cout << "\tSELECCIONAR CAMARA DE 0 a " << NUM_CAMS-1 << "\n";
      modoMenu = SELCAMARA;
      break;
   case 'A' :
      automatica = !automatica;
      break;
   case 'M' :
      cout << "\tSELECCIONAR GRADO DE LIBERTAD\n0: bajar/subir gancho\n1: rotar hélices superiores\n2: rotar hélices cola\n";
      automatica = false;
      manual = true;
      break;
   case '+' :
      if(automatica) incremento = 1;
      if(manual) modelo->moverGrado(gradoSeleccionado,1);
      break;
   case '-' :
      if(automatica) incremento = -1;
      if(manual) modelo->moverGrado(gradoSeleccionado,-1);
      break;
   case 'Q' :
      if(manual) {
         cout << menuprincipal;
         manual = false;
         gradoSeleccionado = -1;
      }
      else{
         cout << "\n\nFIN PROGRAMA\n\n";
         salir = true ;
      }
      
      break ;
   case 'V' :
      modoMenu=SELVISUALIZACION;
      cout << "\tSELECCIONAR TIPO DE VISUALIZACIÓN\nP:puntos\nL:lineas\nS:solido\nI:activar iluminacion plana/suave\n" <<
            "0-" << Luz::nluces <<  ":apagar/encender luz\nA:seleccionar ALPHA\nB:seleccionar BETA\n";
      break ;
   default:
      cout << menuprincipal;
      break;
   }

   // ---------------- MENÚ CÁMARA ----------------
   if (modoMenu==SELCAMARA)
   {
      std::cout << "\tMENU DE CAMARA\nQ:salir\nF: First Person\nE: Examinar (por defecto)\n";
      switch (toupper(tecla))
      {
      case 'Q':
         modoMenu = NADA;
         cout << menuprincipal;
         break;
      case 'F':
         std::cout << "\tMOVIMIENTO: W:avanzar, S:retroceder, A:izquierda, D:derecha\nPara mirar a los sitios, usar ratón\n";
         camaras[cam_activa]->modo=1;
         break;
      case 'E':
         camaras[cam_activa]->modo=0;
         std::cout << "\tEXAMINAR: para mover cámara, usar flechas o ratón";
         break;
      case 'D':
         if (camaras[cam_activa]->modo==1)
         camaras[cam_activa]->mover(0.1,0);
         break;
      case 'A':
         if (camaras[cam_activa]->modo==1)
         camaras[cam_activa]->mover(-0.1,0);
         break;
      case 'S':
         if (camaras[cam_activa]->modo==1)
         camaras[cam_activa]->mover(0,-0.1);
         break;
      case 'W':
         if (camaras[cam_activa]->modo==1)
         camaras[cam_activa]->mover(0,0.1);
         break;
      default:
         break;
      }
      
      for(int i = 0; i < NUM_CAMS; i++)
         if ((tecla-'0')==i){
            cam_activa = i;
            std::cout << "CAMARA " << cam_activa;
            if(cam_activa==1) std::cout << ": ORTOGONAL\n";
            else std::cout << ": PERSPECTIVA\n";
            cambia_proyeccion();
         } 
   }
   // ---------------- SELECCIONAR LUZ ----------------
   else if(modoMenu==SELILUMINACION) {
      for(int i = 0; i < Luz::nluces; i++)
         if ((tecla-'0')==i) interruptor[i] = !interruptor[i];
   }
   // ---------------- SELECCIONAR GRADO DE LIBERTAD ----------------
   else if(manual) {
      for(int i = 0; i < modelo->numGradosLibertad; i++){
         if ((tecla-'0') == i){
            gradoSeleccionado = i;
            cout << "Seleccionado grado " << i << "\n";
         }
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
         camaras[cam_activa]->girar(1,0,0.05);
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         camaras[cam_activa]->girar(-1,0,0.05);
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         camaras[cam_activa]->girar(0,-1,0.05);
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         camaras[cam_activa]->girar(0,1,0.05);
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         camaras[cam_activa]->zoom(1.2);
         cambia_proyeccion();
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         camaras[cam_activa]->zoom(-1.2);
         cambia_proyeccion();
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

/**
 * @brief Función para definir la transformación de proyección
 * (P6) --> con ratio_yx no genera problemas al redimensionar la ventana
 * 
 * @param ratio_xy relación de aspecto del viewport en anchura ( ancho(X) / alto(Y) )
 * @param ratio_yx relación de aspecto del viewport en altura ( alto(Y) / ancho(X) )
 */
void Escena::cambia_proyeccion(){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   camaras[cam_activa]->setProyeccion();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   // Width  = newWidth/10;
   // Height = newHeight/10;
   std::cout << "VIEWPORT: ancho=" << newWidth << " alto=" << newHeight << "\n";
   // change_projection( float(newHeight)/float(newWidth) );
   
   for (int i = 0; i < NUM_CAMS; i++) camaras[i]->reajustar(newWidth, newHeight);
   cambia_proyeccion();
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
   glTranslatef( 0.0, 0.0, -Observer_distance ); // translada el observador -200 unidades
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

void Escena::change_observer_p6()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   if(haciendoZoom!=0){
      camaras[cam_activa]->zoom(haciendoZoom);
      haciendoZoom=0;
   }
   camaras[cam_activa]->setObserver();
}
