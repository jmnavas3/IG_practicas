#ifndef COLA_H
#define COLA_H

#include "../cono.h"
#include "../cubo.h"

class Cola
{
private:
    Cubo *cubo = nullptr;
    Cono *cono = nullptr;
public:
    Cola();
    ~Cola();
    void draw(std::vector<bool> activo, bool luz=false);
};



#endif
