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
#include "material.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum {PUNTOS, LINEAS, SOLIDO, CULL, SOMBRA};
class Malla3D
{
   public:

   void draw(std::vector<bool> a, bool luz) ;
   void setMaterial (Material mat);


   protected:

   // material para los objetos con iluminacion
   Material m;

   // tablas de datos para las mallas
   std::vector<Tupla3f> nv;               // tabla de normales de vértices
   std::vector<Tupla3f> v ;               // tabla de coordenadas xyz de vértices
   std::vector<Tupla3i> f ;               // tabla de triángulos (caras) con los índices de los vértices que los forman
   std::vector<std::vector<Tupla3f>> cl;  // tablas de colores RGB para los vértices en modo punto, línea y sólido

   // identificadores de cada vbo
   std::vector<GLuint> id_vbos_c{0, 0, 0};   // puntos, lineas y sólido
   GLuint id_vbo_nv = 0;                     // normales de vértices
   GLuint id_vbo_v=0;                        // vértices
   GLuint id_vbo_f=0;                        // caras

   // otros atributos de Malla3D
   const float PI = 3.14159265f;
   
   void genNormales();
   void setBufferColor(GLuint id_c);
   void genColor(float r, float g, float b, int n_vert);
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid * puntero_ram);
   
} ;


#endif
