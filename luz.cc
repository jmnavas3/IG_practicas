// #include "auxiliar.h"
#include "luz.h"

void Luz::activar() {

    // Cap.6, Color, Pág.138. RedBook OpenGL: "if u want realistic effect, set GL_SPECULAR = GL_DIFFUSE"
    if(id != GL_LIGHT0){
        // Definir los colores de las luces (luz 0: blanco (defect.) , luz 1-8: oscuridad (defect.))
        glLightfv(id,GL_AMBIENT,colorAmbiente);
        glLightfv(id,GL_SPECULAR,colorEspecular);
        glLightfv(id,GL_DIFFUSE,colorDifuso);

        // GL_LIGHT1 (spotlight)
        if(id == GL_LIGHT1){
            // SPOT_CUTOFF: define el doble del angulo pasado por parametro,
            // por defecto, es 180(maximo) (2*180=360º), así, ilumina toda la escena. No poner en Direccionales
            glLightf(id,GL_SPOT_CUTOFF,20.0);
            
            // SPOT_DIRECTION: define los ejes a los que apunta la luz, por defecto (0,0,1)
            // glLightfv(id,GL_SPOT_DIRECTION,{-1.0,})
            
            // SPOT_EXPONENT: indica la intensidad de la luz en el centro del angulo (Default=0)
            // RedBook, pg.141.
            // glLightf(id,GL_SPOT_EXPONENT,2.0);

            // ATENUACIONES
            glLightf(id,GL_CONSTANT_ATTENUATION,1.5);
            // glLightf(id,GL_LINEAR_ATTENUATION,0.5);
            // glLightf(id,GL_QUADRATIC_ATTENUATION,0.2);
        }

        // Definir y "dibujar" la posicion de la luz
        glLightfv(id,GL_POSITION,posicion);
    }

    
    // si la luz activada es la 0, dejamos sus valores por defecto
    glEnable(id);           // activar fuente de luz "GL_LIGHTid"
}