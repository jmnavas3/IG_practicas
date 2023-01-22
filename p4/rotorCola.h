#ifndef ROTORC_H
#define ROTORC_H

#include "rotor.h"
#include "helice.h"

class RotorCola
{
private:
    Rotor * rotor = nullptr;
    Helice * heli = nullptr;
    const int HELI = 2, LARGO = 15;
public:
    RotorCola(/* args */);
    ~RotorCola();

    void draw(std::vector<bool> activo, bool luz);
};


#endif
