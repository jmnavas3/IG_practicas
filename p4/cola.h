#ifndef COLA_H
#define COLA_H

#include "../cono.h"
#include "../cubo.h"
#include "rotorCola.h"

class Cola
{
private:
    Cono *cono = nullptr;
    RotorCola *rotorC = nullptr;
    const int HELI = 4, LARGO = 15;
public:
    float anguloRotacion;
    Cola();
    ~Cola();
    void draw(std::vector<bool> activo, bool luz=false);
};



#endif
