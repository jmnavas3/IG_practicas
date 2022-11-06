// #include "auxiliar.h"
#include "luz.h"

// similar a Malla3D::draw
void Luz::activar() {

    // Definir los colores de las luces (luz 0: blanco (defect.) , luz 1-8: oscuridad (defect.))
    glLightfv(id,GL_AMBIENT,colorAmbiente);
    glLightfv(id,GL_SPECULAR,colorEspecular);
    glLightfv(id,GL_DIFFUSE,colorDifuso);
    
    // Definir y "dibujar" la posicion de la luz
    glLightfv(id,GL_POSITION,posicion);

    glEnable(GL_LIGHTING);  // activar modelo de iluminacion local
    glEnable(id);           // activar fuente de luz "GL_LIGHTid"
}