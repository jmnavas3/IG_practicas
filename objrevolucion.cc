#include "auxiliar.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

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
// nota: para los objetos cilindro, cono y esfera no se pasan los vertices
// **                                               M                N
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int n = num_instancias;
   int m = perfil_original.size();
   int v_tam;
   float angulo = (2*PI)/(float)n;
   Tupla3f p_norte, p_sur, tupla;
   bool tapa_inf = 0, tapa_sup = 0;
   int a,b;

   // si el perfil esta al reves, lo añadimos a un vector auxiliar desde el ultimo vertice del array
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
   // bucle externo que recorre el nº de instancias y bucle interno que crea sus vértices rotados 2*PI/N rad.
   for (int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++){
         angulo = 2*PI*i/n;
         tupla(X) = cos(angulo)*perfil_original[j](X) + sin(angulo)*perfil_original[j](Z);
         tupla(Y) = perfil_original[j](Y);
         tupla(Z) = cos(angulo)*perfil_original[j](Z) - sin(angulo)*perfil_original[j](X);

         v.push_back(tupla);
      }
   }


   // creación de caras
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m-1; j++) {        // m-1: ignorar ultimo vertice de cada instancia
         a = m*i+j;                          // primer vertice de instancia actual
         b = m*((i+1)%n)+j;                  // primer vertice de instancia siguiente
         f.push_back({a,b,b+1});
         f.push_back({a,b+1,a+1});
      }
   }


   // caras del polo sur (tapa inferior)
   if(tapa_inf){
      v.push_back(p_sur);
      v_tam = v.size()-1;
      for(int i = 0; i < n; i++){
         f.push_back( {m*((i+1)%n),          // primer vertice de instancia siguiente
                       m*i ,                 // primer vertice de instancia actual
                       v_tam} );             // polo sur
      }
   }
   // caras del polo norte (tapa superior)
   if(tapa_sup){
      v.push_back(p_norte);
      v_tam = v.size()-1;
      for(int i = 0; i < n; i++){
         a = m*(i+1)-1;                      // último vertice de instancia actual
         b = m*((i+1)%n)+m-1;                // último vertice de instancia siguiente
         f.push_back({a,b,v_tam});           // polo norte
      }
   }

   genColor(0.3,0.6,1.0);
}