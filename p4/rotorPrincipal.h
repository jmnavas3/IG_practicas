#ifndef ROTORP_H
#define ROTORP_H

#include "../cilindro.h"
#include "../cubo.h"
#include "rotor.h"

class RotorPrincipal
{
private:
    Cilindro * cilindro = nullptr;
    Cubo * cubo = nullptr;
    Rotor * rotor = nullptr;
public:
    RotorPrincipal(/* args */);
    ~RotorPrincipal();

    void draw(std::vector<bool> activo, bool luz);
};


#endif
