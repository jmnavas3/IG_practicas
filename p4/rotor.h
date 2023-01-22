#ifndef ROTOR_H
#define ROTOR_H

#include "../cilindro.h"

class Rotor
{
private:
    Cilindro * cilindro = nullptr;
    float ajuste;
public:
    Rotor();
    ~Rotor();

    void draw (std::vector<bool> activo, bool luz);
};


#endif