#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   //t = new Textura("./p5/sample.jpg");
   // inicializar la tabla de vértices
   v.resize(8);
   float h = lado;
   lado = lado/2.0;
   v[0] = {lado,0.0f,-lado}; //vertices inferiores 6
   v[1] = {lado,0.0f,lado};      // 1
   v[4] = {-lado,0.0f,-lado};    // 7
   v[5] = {-lado,0.0f,lado};     // 0
   v[2] = {lado,h,lado}; // vertices superiores 3
   v[3] = {lado,h,-lado};        // 5
   v[6] = {-lado,h,lado};        // 2
   v[7] = {-lado,h,-lado};       // 4
   
   if(t!=nullptr)
   {
      // v.size()=14
      v.push_back(v[7]); // 4 = 8
      v.push_back(v[3]); // 5 = 9
      v.push_back(v[0]); // 6 = 10
      v.push_back(v[4]); // 7 = 11
      v.push_back(v[3]); // 5 = 12
      v.push_back(v[0]); // 6 = 13

      // inicializar la tabla de coordenadas de texturas

      ct.resize(14);
      ct[5] = {0,0};    // 0
      ct[1] = {1,0};    // 1
      ct[6] = {0,1};    // 2
      ct[2] = {1,1};    // 3
      ct[7] = {0,0};    // 4
      ct[3] = {1,0};    // 5
      ct[0] = {1,1};    // 6
      ct[4] = {0,1};    // 7
      ct[8] = {1,1};    // 8 = 4
      ct[9] = {0,1};    // 9 = 5
      ct[10] = {0,0};   // 10 = 6
      ct[11] = {1,0};   // 11 = 7
      ct[12] = {0,1};   // 12 = 5
      ct[13] = {0,0};   // 13 = 6
   }


   // inicializar la tabla de caras o triángulos:
   f.resize(12);
   f[0] = {2,1,0}; // c11 DERECHA
   f[1] = {0,3,2}; // c12
   f[2] = {1,2,6}; // c21 FRONTAL
   f[3] = {6,5,1}; // c22
   f[4] = {6,4,5}; // c31 IZQUIERDA
   f[5] = {6,7,4}; // c32
   f[6] = {0,4,7}; // c41 TRASERA
   f[7] = {0,7,3}; // c42
   f[8] = {2,3,7}; // c51 SUPERIOR
   f[9] = {7,6,2}; // c52
   f[10] = {1,5,0}; //c61 INFERIOR
   f[11] = {5,4,0}; //c62
   

   genColor(1.0,1.0,0.0); //generar color
   if(t!=nullptr) genNormales(6);
   else genNormales();
}

Cubo::~Cubo() {
   if(t!=nullptr){
      delete t;
      t = nullptr;
   }
}