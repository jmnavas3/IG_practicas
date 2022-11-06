#include "luzPosicional.h"

LuzPosicional::LuzPosicional (const Tupla3f & posicion,
                              GLenum idLuz,
                              Tupla4f colorAmbiente,
                              Tupla4f colorEspecular,
                              Tupla4f colorDifuso)
{
    this->posicion = Tupla4f(posicion(0), posicion(1), posicion(2), 1.0);
    this->id = idLuz;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}