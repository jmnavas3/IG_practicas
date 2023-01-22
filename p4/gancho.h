#ifndef GANCHO_H
#define GANCHO_H

#include "../cilindro.h"

class Gancho
{
private:
    Cilindro *cilindro = nullptr;
public:
    float velocidad;
    float pos;
    
    Gancho(/* args */);
    ~Gancho();
    void draw(std::vector<bool> activo, bool luz=false);
};


#endif
