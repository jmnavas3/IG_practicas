#ifndef HELICE_H
#define HELICE_H

#include "../malla.h"
#include "../cubo.h"

class Helice
{
private:
    Cubo *cubo = nullptr;
    float ajuste;
    int largoHelice, nHelices;
    const float GRADOS = 360;
public:
    Helice();
    Helice(int numero, int largo);
    ~Helice();

    void draw (std::vector<bool> activo, bool luz);
};


#endif