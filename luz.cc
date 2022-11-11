#include "luz.h"

/**
 * @brief Método que enciende/apaga la luz que lo invoca en función del parámetro.
 * GL_LIGHT0 usa sus valores por defecto.
 * 
 * @param interruptor booleano para activar dicha luz
 */
void Luz::activar(bool interruptor) {

    if(interruptor && id != GL_LIGHT0){
        glLightfv(id,GL_AMBIENT,colorAmbiente);
        glLightfv(id,GL_SPECULAR,colorEspecular);
        glLightfv(id,GL_DIFFUSE,colorDifuso);

        // GL_LIGHT4 (spotlight)
        if(id == GL_LIGHT4){
            // SPOT_CUTOFF: define el doble del angulo pasado por parametro,
            // por defecto, es 180(maximo) (2*180=360º), así, ilumina toda la escena. No poner en Direccionales
            glLightf(id,GL_SPOT_CUTOFF,45.0);
            
            // SPOT_DIRECTION: define los ejes a los que apunta la luz, por defecto (0,0,1)
            // glLightfv(id,GL_SPOT_DIRECTION,...);
            
            // SPOT_EXPONENT: indica la intensidad de la luz en el centro del angulo (Default=0)
            // RedBook, pg.141.
            glLightf(id,GL_SPOT_EXPONENT,2.0);

            // ATENUACIONES
            glLightf(id,GL_CONSTANT_ATTENUATION,3.0); //constante, da más realismo al rotar la camara
            // glLightf(id,GL_LINEAR_ATTENUATION,1.5);
            // glLightf(id,GL_QUADRATIC_ATTENUATION,0.5);
        }

        glLightfv(id,GL_POSITION,posicion);
    }

    if(interruptor) glEnable(id);
    else            glDisable(id);
}