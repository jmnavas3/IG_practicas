#ifndef ATERRIZAJE_H
#define ATERRIZAJE_h

#include "../cilindro.h"

class Aterrizaje
{
private:
    Cilindro *c = nullptr;
public:
    Aterrizaje();
    ~Aterrizaje();
    void draw(std::vector<bool> activo, bool luz);
    void patin(std::vector<bool> activo, bool luz);
};



#endif