#ifndef ATERRIZAJE_H
#define ATERRIZAJE_H

#include "patin.h"

class Aterrizaje
{
private:
    Patin *p = nullptr;
public:
    Aterrizaje();
    ~Aterrizaje();
    void draw(std::vector<bool> activo, bool luz);
};



#endif