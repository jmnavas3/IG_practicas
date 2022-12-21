#ifndef GANCHO_H
#define GANCHO_H

#include "../cilindro.h"

class Gancho
{
private:
    int velocidad;
    Cilindro *cilindro = nullptr;
public:
    Gancho(/* args */);
    ~Gancho();
    void draw(std::vector<bool> activo, bool luz=false);
};


#endif
