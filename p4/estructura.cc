#include "estructura.h"
#include "../auxiliar.h"

Estructura::Estructura(/* args */)
{
    cuerpo = new Cuerpo();
    cola = new Cola();
}

Estructura::~Estructura()
{
    delete cuerpo;
    delete cola;

    cuerpo = nullptr;
    cola = nullptr;

    std::cout << "destructor estructura\n";
}

void Estructura::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();
    
    cuerpo->draw(activo,luz);
    cola->draw(activo,luz);

glPopMatrix();
}