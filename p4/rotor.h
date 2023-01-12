#ifndef ROTOR_H
#define ROTOR_H

#include "../cilindro.h"
#include "../cubo.h"

class Rotor
{
private:
    Cilindro * cilindro = nullptr;
    Cubo * cubo = nullptr;
    float ajuste;
public:
    Rotor(/* args */);
    ~Rotor();

    void draw (std::vector<bool> activo, bool luz);
    void drawHelice (std::vector<bool> activo, bool luz, int largoHelice=50);
};


#endif