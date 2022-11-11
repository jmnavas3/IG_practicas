#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------

/**
  * Dibuja y visualiza la malla en modo diferido
  * @param a booleanos que activan los modos de visualizacion
  * @param luz si es 0, se usan las tablas de colores
  */

void Malla3D::draw(std::vector<bool> a, bool luz)
{
   if(id_vbo_v == 0) id_vbo_v   = CrearVBO(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data() );
   if(id_vbo_f == 0) id_vbo_f   = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(f[0]) * f.size(), f.data());
   for ( int i=0; i<3; i++ ) {
      if(id_vbos_c[i] == 0)id_vbos_c[i] = CrearVBO(GL_ARRAY_BUFFER, cl[i].size()*sizeof(cl[i][0]), cl[i].data());
   }
   if(id_vbo_nv == 0) id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, sizeof(nv[0]) * nv.size(), nv.data() );


   // temporal
   if(a[CULL]) glEnable(GL_CULL_FACE);
   else glDisable(GL_CULL_FACE);
   
   if(id_vbo_v != 0){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
      glVertexPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_VERTEX_ARRAY);
   }
   
   if(luz && id_vbo_nv != 0){
      m.aplicar();
      if (a[SOMBRA]) glShadeModel(GL_FLAT);
      else glShadeModel(GL_SMOOTH);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);
      glNormalPointer(GL_FLOAT,0,0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_NORMAL_ARRAY);
   }

   // Activamos buffer VBO de índices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);

   if (luz) {
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   }
   else {
      //MODOS DE VISUALIZACIÓN SIN ILUMINACIÓN
      glEnableClientState(GL_COLOR_ARRAY);
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

      // glDisableClientState(GL_COLOR_ARRAY);
   }

   // Desactivamos buffer de índices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   
   
   // Desactivamos uso de arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   if(luz) glDisableClientState(GL_NORMAL_ARRAY);
   else glDisableClientState(GL_COLOR_ARRAY);

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
      // Activamos buffer de colores con su id
         glBindBuffer(GL_ARRAY_BUFFER, id_c);
      // Usar como buffer de colores el actualmente activo
         glColorPointer(3, GL_FLOAT, 0, 0);
      // Desactivamos buffer de colores
         glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
}

// -----------------------------------------------------------------------------
// Redimensiona las tablas de colores en caso de no estar redimensionadas y les asigna diferentes valores a cada una

void Malla3D::genColor(float r, float g, float b){
   if (cl.size()!=3){
      int n_vert = v.size();
      cl.resize(3);
      cl[0].resize(n_vert);   // puntos
      cl[1].resize(n_vert);   // líneas
      cl[2].resize(n_vert);   // sólido
      
      for(int j=0; j<n_vert; j++){
         cl[2][j] = {r,g,b};
         cl[1][j] = {b,r,g};
         cl[0][j] = {g,b,r};
      }
   }
}

// -----------------------------------------------------------------------------
// Modificador del material de cada malla
void Malla3D::setMaterial (Material mat) {
   m = mat;
}

// -----------------------------------------------------------------------------
// Función de generación de normales de las caras
void Malla3D::genNormales(){
   Tupla3f va;
   Tupla3f vb;
   Tupla3f pvectorial;
   std::vector<Tupla3f> nCaras;
   int p,q,r;
   

   nv.resize(v.size());

   // nota: no es necesario puesto que todas las tuplas se inicializan a 0
   // nv = std::vector<Tupla3f>(v.size(),Tupla3f(0.0f,0.0f,0.0f));

   // El vector normal a un vertice se define como la normalización de la suma de todos los vectores normales de los triángulos adyacentes a dicho vértice.
   // Para cada triángulo ó cara de la tabla de caras (f), guardamos los índices de sus vértices en 'p', 'q' y 'r' y calculamos la normal a dicho triangulo.
   // Seguidamente, sumamos dicha normal a la posición correspondiente a cada uno de los vértices del triángulo dentro de la tabla de normales de vertices.
   // Tras recorrer todos los triángulos, se habrá obtenido para cada vértice su vector perpendicular, sólo quedaría normalizar cada perpendicular.

   for(int i = 0; i < f.size(); i++){
      // indice de vertices del triangulo i-esimo
      p = f[i](X);
      q = f[i](Y);
      r = f[i](Z);

      // obtencion del vector normal al triangulo i-esimo
      va = v[q] - v[p];
      vb = v[r] - v[p];
      pvectorial = va.cross(vb);
      nCaras.push_back(pvectorial.normalized());

      // suma del vector normal obtenido a cada uno de los vertices del triangulo
      nv[p] = nv[p] + nCaras.back();
      nv[q] = nv[q] + nCaras.back();
      nv[r] = nv[r] + nCaras.back();
   }

   // obtencion de tabla de normales de vértices
   for (int i = 0; i < nv.size(); i++)
      nv[i] = nv[i].normalized();

}