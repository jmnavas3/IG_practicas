#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "malla.h"

class Cuadro : public Malla3D
{
    public:
    Cuadro(float l=1);
    ~Cuadro();
};

#endif