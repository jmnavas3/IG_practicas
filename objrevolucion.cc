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
   if(perfil.size()!=0)
      crearMalla(perfil,num_instancias);

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
   int v_tam = (n*m)-1; // indice de ultimo vertice de la tabla
   float angulo = (2*PI)/n;
   Tupla3f p_norte, p_sur, tupla;
   bool tapa_inf = 0,
        tapa_sup = 0;

   // comprobamos que los extremos no estén sobre el eje Y, si están, los guardamos aparte

   if(fabs(perfil_original[0](X)-perfil_original[0](Z)) < EPSILON){
      tapa_inf = 1;
      p_sur = perfil_original.front();
      perfil_original.erase(perfil_original.begin());
   }

   if(fabs(perfil_original[m-1](X)-perfil_original[m-1](Z)) < EPSILON){
      tapa_sup = 1;
      p_norte = perfil_original.back();
      perfil_original.pop_back();
   }

   //  bucle externo que recorre el nº de instancias
   //  bucle interno que ROTA 2*PI/N rad. los vértices de cada instancia y los añade al final
   //  de la tabla de vertices
   for (int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++){
         tupla(X) = (float)cos(i*angulo)*perfil_original[j](X) + (float)sin(i*angulo)*perfil_original[j](Z);
         tupla(Y) = perfil_original[j](Y);
         tupla(Z) = (float)cos(i*angulo)*perfil_original[j](Z) - (float)sin(i*angulo)*perfil_original[j](X);

         v.push_back(tupla);
      }
   }
   // al final de bucle doble, en v hay (m*n)-2 elementos en caso de que se hayan quitado los polos
   //por lo que el indice del ultimo elemento de v será: (m*n)-3

   // añadimos los vertices de las instancias a la tabla de caras
   int a, b;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m-1; j++) {
         a = m*i+j;
         b = m*((i+1)%n)+j;
         f.push_back({a,b,b+1});
         f.push_back({a,b+1,a+1});
      }
   }

   // creamos las caras de las tapas

   if(tapa_inf){
      v.push_back(p_sur);
      v_tam++; //indice de p_sur --> n*m
      for(int i = 0; i < n; i++){
         f.push_back( {m*((i+1)%n),          // primer vertice de instancia siguiente
                       m*i ,                 // primer vertice de instancia actual
                       v_tam} );             // polo sur
      }
      // la ultima iteracion del bucle crea la cara: {0,m*(n-1),polo sur}, donde m*(n-1) es el primer vertice
      // de la ultima instancia
   }

   if(tapa_sup){
      v.push_back(p_norte);
      v_tam++;
      for(int i = 1; i < n+1; i++){
         f.push_back( { v_tam ,              //polo norte
                        m*((i+1)%n)-1 ,      //ultimo vertice de instancia siguiente
                        (m*i)-1} );          //ultimo vertice de instancia actual
      }
      // la ultima iteracion del bucle crea la cara: {p_norte, m-1, (m*n)-1 } donde m-1 es el vertice inicial
      // de la tapa superior (m*n)-1 es el vertice final de la tapa superior
   }

   // generamos colores, lo suyo seria ponerlo random para cada objeto
   genColor(1.0,0.0,0.3,v_tam);
}
