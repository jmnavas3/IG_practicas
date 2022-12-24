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
    nluces++;
}

/**
 * @brief Rotación en torno al eje Y (longitud)
 * 
 * @param incremento en grados del eje Y
 */
void LuzDireccional::variarAnguloAlpha (float incremento) {
    alpha += incremento;
    coordenadas();
}

/**
 * @brief Rotación en torno al eje X (latitud)
 * 
 * @param incremento en grados del eje X
 */
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
    x = sin(alpha)*cos(beta);
    y = sin(beta);
    z = cos(alpha)*cos(beta);
    this->posicion = {x,y,z,0.0};
}

void LuzDireccional::animarColor(){
    if(colorDifuso(1) < 1) colorDifuso(1) += 0.1;
    else                   colorDifuso(1) = 0.1;

    if(colorDifuso(2) > 0) colorDifuso(2) -= 0.1;
    else                   colorDifuso(2) = 1;
}