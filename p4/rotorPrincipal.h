#ifndef ROTORP_H
#define ROTORP_H

#include "../cilindro.h"
#include "../cubo.h"

class RotorPrincipal
{
private:
    Cilindro * cilindro = nullptr;
    Cubo * cubo = nullptr;
public:
    RotorPrincipal(/* args */);
    ~RotorPrincipal();

    void draw(std::vector<bool> activo, bool luz=false);
};


#endif
