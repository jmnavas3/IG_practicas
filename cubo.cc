#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.resize(8);
   float h = lado;
   lado = lado/2.0;
   v[0] = {lado,0.0f,-lado}; //vertices inferiores
   v[1] = {lado,0.0f,lado};
   v[4] = {-lado,0.0f,-lado};
   v[5] = {-lado,0.0f,lado};
   v[2] = {lado,h,lado}; // vertices superiores
   v[3] = {lado,h,-lado};
   v[6] = {-lado,h,lado};
   v[7] = {-lado,h,-lado};

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
   
   genColor(1.0,1.0,0.0,8); //generar color
   genNormales();
}

