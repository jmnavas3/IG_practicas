#ifndef PATIN_H
#define PATIN_H

#include "../cilindro.h"

class Patin
{
private:
    Cilindro *c = nullptr;
public:
    Patin();
    ~Patin();
    void draw(std::vector<bool> activo, bool luz);
};



#endif