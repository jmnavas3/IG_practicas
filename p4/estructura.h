#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "cuerpo.h"
#include "cola.h"

class Estructura
{
private:
    Cuerpo *cuerpo = nullptr;
    Cola *cola = nullptr;
public:
    Estructura(/* args */);
    ~Estructura();
    void draw(std::vector<bool> activo, bool luz=false);
};



#endif
