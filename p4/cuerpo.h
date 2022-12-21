#ifndef CUERPO_H
#define CUERPO_H

#include "../esfera.h"
#include "../cilindro.h"

class Cuerpo
{
private:
    Esfera *esfera = nullptr;
    Cilindro *cilindro = nullptr;
public:
    Cuerpo();
    ~Cuerpo();
    void draw(std::vector<bool> activo, bool luz=false);
};



#endif
