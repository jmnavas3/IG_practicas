#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "cuerpo.h"
#include "cola.h"
#include "aterrizaje.h"

class Estructura
{
private:
    Cuerpo *cuerpo = nullptr;
    Cola *cola = nullptr;
    Aterrizaje *aterrizaje = nullptr;
public:
    Estructura(/* args */);
    ~Estructura();
    void draw(std::vector<bool> activo, bool luz=false);
    void setRotacionCola(float valor = 0.05);
    float getRotacionCola();
};



#endif
