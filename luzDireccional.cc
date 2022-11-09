#include "luzDireccional.h"

LuzDireccional::LuzDireccional (const Tupla2f & orientacion,
                              GLenum idLuz,
                              Tupla4f colorAmbiente,
                              Tupla4f colorEspecular,
                              Tupla4f colorDifuso)
{
    this->posicion = Tupla4f(orientacion(0), orientacion(1), 1.0, 0.0);
    this->id = idLuz;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlpha (float incremento) {
    alpha += incremento;
    // glRotatef(alpha,0.0,1.0,0.0);
}

void LuzDireccional::variarAnguloBeta (float incremento) {
    beta += incremento;
    // glRotatef(beta,1.0,0.0,0.0);
}

void LuzDireccional::cambiarAngulo () {
        // glLoadIdentity();
        glRotatef(alpha,0.0,1.0,0.0);
        glRotatef(beta,1.0,0.0,0.0);
}