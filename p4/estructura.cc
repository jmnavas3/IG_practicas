#include "estructura.h"
#include "../auxiliar.h"

Estructura::Estructura(/* args */)
{
    cuerpo = new Cuerpo();
    cola = new Cola();
    aterrizaje = new Aterrizaje();
}

Estructura::~Estructura()
{
    delete cuerpo;
    delete cola;
    delete aterrizaje;
    cuerpo = nullptr;
    cola = nullptr;
    aterrizaje = nullptr;
}

void Estructura::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();

    cuerpo->draw(activo,luz);
    glPushMatrix();
        glTranslatef(-5.8,0,0);
        cola->draw(activo,luz);
    glPopMatrix();

    glTranslatef(0,-5,0);
    aterrizaje->draw(activo,luz);
glPopMatrix();
}

void Estructura::setRotacionCola(float valor) {
    cola->anguloRotacion += valor;
    if(cola->anguloRotacion > 360) cola->anguloRotacion = 0;
}

float Estructura::getRotacionCola() {
    return cola->anguloRotacion;
}