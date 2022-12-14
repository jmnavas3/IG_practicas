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
#include "textura.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum {PUNTOS, LINEAS, SOLIDO, SOMBRA};
class Malla3D
{
   public:

   void draw(std::vector<bool> a, bool luz) ;
   void setMaterial (Material mat);
   void genNormales(int perfil=-1);
   // textura para los objetos
   Textura *t = nullptr;


   protected:

   // material para los objetos con iluminacion
   Material m = Material();

   // tablas de datos para las mallas
   std::vector<Tupla3f> nv;               // tabla de normales de vértices
   std::vector<Tupla3f> v ;               // tabla de coordenadas xyz de vértices
   std::vector<Tupla2f> ct;               // tabla de coordenadas (u,v) de textura
   std::vector<Tupla3i> f ;               // tabla de triángulos (caras) con los índices de los vértices que los forman
   std::vector<std::vector<Tupla3f>> cl;  // tablas de colores RGB para los vértices en modo punto, línea y sólido

   // identificadores de cada vbo
   std::vector<GLuint> id_vbos_c{0, 0, 0};   // puntos, lineas y sólido
   GLuint id_vbo_nv = 0;                     // normales de vértices
   GLuint id_vbo_ct= 0;                      // vbo texturas
   GLuint id_vbo_v = 0;                      // vértices
   GLuint id_vbo_f = 0;                      // caras

   // otros atributos de Malla3D
   const float PI = 3.14159265f;
   const float EPSILON = 0.00001f;
   
   void setBufferColor(GLuint id_c);
   void genColor(float r, float g, float b);
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid * puntero_ram);
   
} ;


#endif
