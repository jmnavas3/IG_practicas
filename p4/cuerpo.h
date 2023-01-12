#ifndef CUERPO_H
#define CUERPO_H

#include "../esfera.h"
#include "../cilindro.h"
#include "aterrizaje.h"

class Cuerpo
{
private:
    Esfera *esfera = nullptr;
    Cilindro *cilindro = nullptr;
    Aterrizaje *aterrizaje = nullptr;
public:
    Cuerpo();
    ~Cuerpo();
    void draw(std::vector<bool> activo, bool luz);
};



#endif
