#include "luzDireccional.h"

LuzDireccional::LuzDireccional (const Tupla2f & orientacion,
                              GLenum idLuz,
                              Tupla4f colorAmbiente,
                              Tupla4f colorEspecular,
                              Tupla4f colorDifuso)
{
    alpha = orientacion(0);
    beta = orientacion(1);
    coordenadas();
    this->id = idLuz;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlpha (float incremento) {
    alpha += incremento;
    coordenadas();
}

void LuzDireccional::variarAnguloBeta (float incremento) {
    beta += incremento;
    coordenadas();
}


/**
 * @brief Obtiene las coordenadas esféricas a partir de alpha y beta y
 * actualiza la posicion de la luz direccional cada vez que se varía
 * alguno de los dos ángulos
 * 
 */
void LuzDireccional::coordenadas(){
    x = cos(alpha)*sin(beta);
    y = sin(alpha);
    z = cos(alpha)*cos(beta);
    this->posicion = {x,y,z,0.0};
}