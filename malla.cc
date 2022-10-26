#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,

void Malla3D::draw(std::vector<bool> a, int color)
{

   if(id_vbo_v == 0) id_vbo_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data() );
   if(id_vbo_f == 0) id_vbo_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(f[0]) * f.size(), f.data());
   for ( int i=0; i<3; i++ ) {
      if(id_vbos_c[i] == 0) id_vbos_c[i] = CrearVBO(GL_ARRAY_BUFFER, cl[i].size()*sizeof(cl[i][0]), cl[i].data());
   }
   glEnableClientState(GL_COLOR_ARRAY);

   if(id_vbo_v != 0){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
      glVertexPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_VERTEX_ARRAY);
   }

   if(a[CULL]) glEnable(GL_CULL_FACE);
   else glDisable(GL_CULL_FACE);

   if (color==0) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);
   }
   else {

      // Activamos buffer VBO de índices
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f);

      //MODO DE VISUALIZACIÓN
      if(a[SOLIDO]){
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         setBufferColor(id_vbos_c[SOLIDO]);
         glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
      }
      
      if(a[LINEAS]){
         glLineWidth(1.5);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         setBufferColor(id_vbos_c[LINEAS]);
         glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT,0);
      }

      if(a[PUNTOS]){
         glPointSize(10);
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         setBufferColor(id_vbos_c[PUNTOS]);
         glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT,0);
      }

      // Desactivamos buffer de índices
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   }
   
   //desactivar uso de array de vertices
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);

}

// -----------------------------------------------------------------------------
// Función de creación de VBO

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid * puntero_ram)
{
   GLuint id_vbo;
   // creamos nuevo vbo y obtenemos su id
   glGenBuffers(1, &id_vbo);
   // activamos el vbo con su id
   glBindBuffer(tipo_vbo, id_vbo);

   // transferencia de datos desde ram a gpu
   glBufferData(tipo_vbo, tam, puntero_ram, GL_STATIC_DRAW);
   // desactivamos el vbo (activar a 0)
   glBindBuffer(tipo_vbo, 0);
   return id_vbo;
}

void Malla3D::setBufferColor(GLuint id_c){
   if(id_c != 0){
      // Habilita array de colores 
         // glEnableClientState(GL_COLOR_ARRAY);
      // Activamos buffer de colores con su id
         glBindBuffer(GL_ARRAY_BUFFER, id_c);
      // Usar como buffer de colores el actualmente activo
         glColorPointer(3, GL_FLOAT, 0, 0);
      // Desactivamos buffer de colores
         glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
}

// -----------------------------------------------------------------------------
// Función de generación de colores para los distintos modos: 0.puntos 1.lineas 2.solido

void Malla3D::genColor(float r, float g, float b, int n_vert){
   if (cl.size()!=3){
      cl.resize(3);
      cl[0].resize(n_vert);
      cl[1].resize(n_vert);
      cl[2].resize(n_vert);
      
      for(int j=0; j<n_vert; j++){
         cl[0][j] = {r,g,b};
         cl[1][j] = {b,r,g};
         cl[2][j] = {g,b,r};
      }
   }
}