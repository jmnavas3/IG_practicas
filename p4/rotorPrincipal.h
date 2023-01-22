#ifndef ROTORP_H
#define ROTORP_H

#include "rotor.h"
#include "helice.h"

class RotorPrincipal
{
private:
    Rotor * rotor = nullptr;
    Helice * heli = nullptr;
    const int HELI = 4, LARGO = 50;
public:
    RotorPrincipal(/* args */);
    ~RotorPrincipal();

    void draw(std::vector<bool> activo, bool luz);
};


#endif
