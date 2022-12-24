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

   // creacion de buffers
   if(id_vbo_v == 0) id_vbo_v   = CrearVBO(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data() );
   if(id_vbo_f == 0) id_vbo_f   = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(f[0]) * f.size(), f.data());
   if(id_vbo_nv == 0) id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, sizeof(nv[0]) * nv.size(), nv.data() );
   if(t!=nullptr && id_vbo_ct == 0) id_vbo_ct = CrearVBO(GL_ARRAY_BUFFER, sizeof(ct[0]) * ct.size(), ct.data() );
   for ( int i=0; i<3; i++ ) {
      if(id_vbos_c[i] == 0)id_vbos_c[i] = CrearVBO(GL_ARRAY_BUFFER, cl[i].size()*sizeof(cl[i][0]), cl[i].data());
   }


   // vertices
   if(id_vbo_v != 0){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
      glVertexPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_VERTEX_ARRAY);
   }
   
   // luz y normales
   if(luz && id_vbo_nv != 0){
      m.aplicar();
      if (a[SOMBRA]) glShadeModel(GL_FLAT);
      else glShadeModel(GL_SMOOTH);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);
      glNormalPointer(GL_FLOAT,0,0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_NORMAL_ARRAY);
   }

   // texturas
   if(t != nullptr){
      t->activar();
      glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ct);
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   }

   // índices de caras
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);

   // modos de visualizacion
   if (luz) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   }
   else {
      // color
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


   }
   

   // Desactivamos buffer de índices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   
   
   // Desactivamos uso de arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   if(luz) glDisableClientState(GL_NORMAL_ARRAY);
   else glDisableClientState(GL_COLOR_ARRAY);
   
   if(t!=nullptr){
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisable(GL_TEXTURE_2D);
   }

}



/**
 * @brief Creación de VBO (Vertex Buffer Object)
 * 
 * @param tipo_vbo ARRAY_BUFFER | ELEMENT_ARRAY_BUFFER
 * @param tam tamaño del buffer
 * @param puntero_ram a los datos del buffer
 * @return id_vbo::GLuint 
 */
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


/**
 * @brief Indica el buffer que hay que usar para colorear
 * 
 * @param id_c id del vbo de colores que queramos usar
 */
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


/**
 * @brief Redimensiona las tablas de colores y asigna una combinación de colores diferentes a cada una
 * 
 * @param r rojo (red)
 * @param g verde (green)
 * @param b azul (blue)
 */
void Malla3D::genColor(float r, float g, float b){
   if (cl.size()!=3){
      int n_vert = v.size();
      cl.resize(3);
      cl[0].resize(n_vert);   // puntos
      cl[1].resize(n_vert);   // líneas
      cl[2].resize(n_vert);   // sólido
      
      if(t!=nullptr){
         r=1;
         g=1;
         b=1;
      }
      
      for(int j=0; j<n_vert; j++){
         cl[2][j] = {r,g,b};
         cl[1][j] = {b,r,g};
         cl[0][j] = {g,b,r};
      }
   }
}


/**
 * @brief Asigna el material pasado por parámetro a una Malla3D
 * 
 * @param mat material que se va a asignar a la malla
 */
void Malla3D::setMaterial (Material mat) {
   m = mat;
}


/**
 * @brief Calcula los vectores normales de los vértices de la malla en O(n)
 * 
 * @details Para objetos de @class ObjRevolucion , el nº de instancias y
 * el nº de vertices de perfil tienen que ser divisibles entre ellos, ya que, si no,
 * se generarán números decimales largos y menores a 0.0, que es el límite de normalized()
 */
void Malla3D::genNormales(){
   Tupla3f va, vb, perp; //perp : vector perpendicular a la cara
   Tupla3f nCaras; // normales de las caras
   int vt0, vt1, vt2;           // indices de vertices de una cara
   
   nv.resize(v.size());

   for(int i = 0; i < (int)f.size(); i++){
      // indice de vertices del triangulo i-esimo
      vt0 = f[i](X);
      vt1 = f[i](Y);
      vt2 = f[i](Z);

      // obtencion del vector normal al triangulo i-esimo
      va = v[vt1] - v[vt0];
      vb = v[vt2] - v[vt0];
      perp = va.cross(vb);
      // nCaras = perp / sqrt(perp.dot(perp));
      nCaras = perp.normalized();

      // suma del vector normal obtenido a cada uno de los vertices del triangulo
      nv[vt0] = nv[vt0] + nCaras;
      nv[vt1] = nv[vt1] + nCaras;
      nv[vt2] = nv[vt2] + nCaras;
   }

   // obtencion de tabla de normales de vértices
   for (int i = 0; i < (int)nv.size(); i++)
      nv[i] = nv[i].normalized();

   std::cout << f.size() << " caras\t" << v.size() << " vertices\t" << nv.size() << " normales\t";
   if(!ct.empty())
      std::cout << ct.size() << " coord.textura";
   
   std::cout << "\n";
}