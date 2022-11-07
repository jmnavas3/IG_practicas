#include "auxiliar.h"
#include "malla.h"
#include "piramidepentagonal.h"
PiramidePentagonal::PiramidePentagonal(float h, float r)
{

   // inicializar la tabla de vértices (6 vertices)
   v.resize(6);
   float aux, angulo = 72.0*PI/5.0; // angulo central en radianes
   for(int i = 0; i<5; i++){
      aux = i * angulo;
      v[i] = {(float)cos(aux)*r, 0.0f, (float)sin(aux)*r};
   }
   v[5] = { 0.0f, h, 0.0f };   // altura de piramide

   // inicializar la tabla de caras o triángulos: (6 caras)
   f.resize(8);
   f[0] = {0,1,4}; //caras inferiores
   f[1] = {1,2,4};
   f[2] = {2,3,4};
   f[3] = {0,5,1}; // cara frontal dcha.
   f[4] = {1,5,2}; // cara frontal central
   f[5] = {3,2,5}; // cara frontal izda.
   f[6] = {3,5,4}; // cara trasera izda.
   f[7] = {4,5,0}; // cara trasera dcha.

   // generar colores y normales
   genColor(0.0,0.5,1.0,6);
   genNormales();

   
}

