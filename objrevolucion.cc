#include "auxiliar.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::~ObjRevolucion(){
   if(t!=nullptr){
      delete t;
   }
   t = nullptr;
   std::cout << "objeto destruido";
}

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias) {

   ply::read_vertices(archivo, perfil);
   std::cout << perfil.size() << " vertices\n";
   if(perfil.size()!=0){
      crearMalla(perfil,num_instancias);
      genNormales();
   }

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

                                                // perfil
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias) {
   if(archivo.size()!=0){
      crearMalla(archivo,num_instancias);
   }
}


// *****************************************************************************
// malla de revolución obtenida a partir de un perfil y un numero de instancias
// **                                               M                N
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int n = num_instancias;
   int m = perfil_original.size();
   int v_tam;
   float angulo;
   Tupla3f p_norte, p_sur, tupla;
   bool tapa_inf = 0, tapa_sup = 0;
   int a,b;
   // variables de textura
   bool text_activa = false;
   float d, s, t;
   std::vector<float> dist;

   // si el perfil esta al reves, lo ordenamos ascendentemente
   if(perfil_original.front()(Y) > perfil_original.back()(Y)){
      std::vector<Tupla3f> aux;
      for(int i=0;i<m;i++){
         aux.push_back(perfil_original.back());
         perfil_original.pop_back();
      }
      perfil_original = aux;
      std::cout << "perfil ordenado ascendentemente...\n";
   }

   // comrobar existencia de tapas
   if(fabs(perfil_original[0](X)) < EPSILON &&
      fabs(perfil_original[0](Z)) < EPSILON){
      tapa_inf = 1;
      p_sur = perfil_original.front();
      perfil_original.erase(perfil_original.begin());
      std::cout << "\nquitando tapa inferior...\n";
   }

   if(fabs(perfil_original.back()(X)) < EPSILON &&
      fabs(perfil_original.back()(Z)) < EPSILON)
   {
      tapa_sup = 1;
      p_norte = perfil_original[perfil_original.size()-1];
      perfil_original.pop_back();
      std::cout << "\nquitando tapa superior...\n";
   }


   m = perfil_original.size();

   if( Malla3D::t != nullptr){
      std::cout << "\ntextura activa\n";
      dist.push_back(0);   // d0 = 0
      text_activa = true;
      n++;   // instancia extra necesaria para las coord. de textura 
   }

   // bucle externo que recorre el nº de instancias y bucle interno que crea m vértices rotados 2*PI/N rad para las n instancias
   for (int i = 0; i < n; i++)
   {
      angulo = 2*PI*i/num_instancias;
      for(int j = 0; j < m; j++)
      {
         if(i<num_instancias){
            tupla(X) = cos(angulo)*perfil_original[j](X) + sin(angulo)*perfil_original[j](Z);
            tupla(Y) = perfil_original[j](Y);
            tupla(Z) = cos(angulo)*perfil_original[j](Z) - sin(angulo)*perfil_original[j](X);
            v.push_back(tupla);
         }
         else {
            v.push_back(v[j]); // instancia extra similar al perfil original en coordenadas pero con diferente coord. textura
         }

         // DISTANCIA DE LOS VERTICES DEL PERFIL
         if (i==0 && text_activa && j>0) {
            d = (v[j]-v[j-1]).lengthSq(); // modulo ( v[1]-v[0] )
            d += dist[j-1];               // d1 = 0 + modulo(...)
            dist.push_back(d);   // dj+1
         }    
      }
      

      if (text_activa) {
         // 's' igual para todos los vertices de cada instancia
         // 't' unica para cada vertice de cada instancia
         s = (float)i/(float)num_instancias;
         for(int j = 0; j < m; j++){
            t = dist[j] / d;
            ct.push_back({ s , t });
            //if(i>=num_instancias-1 || i==0){
            //   std::cout << ct[m*i+j] << "\t--> v[" << m*i+j << "]\n";
            //}
            //std::cout << "t = " << t << "\n";
         }
         //std::cout << "s =" << s << "\n";
      }
   
   }

   // creación de caras
   for (int i = 0; i < num_instancias; i++) {
      for (int j = 0; j < m-1; j++) {        // m-1: ignorar ultimo vertice de cada instancia
         a = m*i+j;                          // primer vertice de instancia actual
         b = m*((i+1)%n)+j;                  // primer vertice de instancia siguiente
         f.push_back({a,b,b+1});
         f.push_back({a,b+1,a+1});

         //if(i==num_instancias-1){
         //   std::cout << f.back() << "\t" << f[f.size()-2] << "\n";
         //}
      }
   }
   std::cout << f.size() << " caras sin tapas\n";
   // caras del polo sur (tapa inferior)
   if(tapa_inf){
      v.push_back(p_sur);
      if(text_activa) ct.push_back({0,0});
      v_tam = v.size()-1;
      for(int i = 0; i < num_instancias; i++){
         f.push_back( {m*((i+1)%n),          // primer vertice de instancia siguiente
                       m*i ,                 // primer vertice de instancia actual
                       v_tam} );             // polo sur
         
         /* if(i==num_instancias-1 || i==0){
            std::cout << f.back() << "\n";
         } */
      }
   }
   // caras del polo norte (tapa superior)
   if(tapa_sup){
      v.push_back(p_norte);
      v_tam = v.size()-1;
      if(text_activa) ct.push_back({1,1});
      for(int i = 0; i < num_instancias; i++){
         a = m*(i+1)-1;                      // último vertice de instancia actual
         b = m*((i+1)%n)+m-1;                // último vertice de instancia siguiente
         f.push_back({a,b,v_tam});           // polo norte         
         
         /* if(i==num_instancias-1 || i==0){
            std::cout << f.back() << "\n";
         } */
      }
   }

   std::cout << ct.size() << " coord.textura\t" << v.size() << " vertices\t" << f.size() << " caras\n";


   genColor(0.3,0.6,1.0);
}


/**
 * @brief Comprueba que no haya vértices repetidos en un perfil.
 * Ejemplo: lata
 * 
 */
void ObjRevolucion::repetidos() {
   for(int i = 0; i< (int)perfil.size()-1; i++){
      if(perfil[i](X) == perfil[i+1](X) &&
         perfil[i](Y) == perfil[i+1](Y) &&
         perfil[i](Z) == perfil[i+1](Z))
         perfil.erase(perfil.begin()+i+1);
   }
}