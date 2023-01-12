#ifndef GANCHO_H
#define GANCHO_H

#include "../cilindro.h"

class Gancho
{
private:
    Cilindro *cilindro = nullptr;
public:
    int velocidad;
    
    Gancho(/* args */);
    ~Gancho();
    void draw(std::vector<bool> activo, bool luz=false);
};


#endif
