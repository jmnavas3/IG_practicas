#ifndef COLA_H
#define COLA_H

#include "../cono.h"
#include "../cubo.h"
#include "rotor.h"

class Cola
{
private:
    Cubo *cubo = nullptr;
    Cono *cono = nullptr;
    Rotor *rotorC = nullptr;
public:
    float anguloRotacion;
    Cola();
    ~Cola();
    void draw(std::vector<bool> activo, bool luz=false);
};



#endif
