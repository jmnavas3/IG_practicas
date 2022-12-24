#ifndef LUZANIMADA_H
#define LUZANIMADA_H

#include "luzPosicional.h"
#include "luzDireccional.h"
#include "esfera.h"

class LuzAnimada
{
private:
    Esfera * esfera  = nullptr;
    float angulo;
    float velocidad;
    Tupla3f posicionLuz;
public:
    LuzPosicional *luz = nullptr;
    LuzDireccional *luzD = nullptr;

    LuzAnimada();
    ~LuzAnimada();

    void draw(std::vector<bool> activo, bool luz=false);
    void animar();
};

#endif