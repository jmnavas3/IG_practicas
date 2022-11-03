// #############################################################################
//
// Informática Gráfica D (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum {PUNTOS, LINEAS, SOLIDO, CULL};
class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   // si color==0 dibuja sin usar buffer de colores
   void draw(std::vector<bool> a, int color) ;

   protected:



   std::vector<Tupla3f> v ;               // tabla de coordenadas de vértices (una tupla por vértice, con tres floats) vertices
   std::vector<Tupla3i> f ;               // una terna de 3 enteros por cada cara o triángulo  caras (faces)
   std::vector<std::vector<Tupla3f>> cl;  // tablas de colores que se inicializan en método genColor
   std::vector<Tupla3f> nv;               //normales de vertices

   GLuint id_vbo_v=0;
   GLuint id_vbo_f=0;
   std::vector<GLuint> id_vbos_c{0, 0, 0}; // inicializado con tamaño 3 y todos a 0
   const float PI = 3.14159265f;
   
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid * puntero_ram);
   void setBufferColor(GLuint id_c);

   // Inicializa la tabla de colores para cada vbo de colores pasandole los vertices
   void genColor(float r, float g, float b, int n_vert);
   void genNormales();
   
} ;


#endif
