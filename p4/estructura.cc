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
}

void Estructura::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();

    cuerpo->draw(activo,luz);
    glPushMatrix();
        glTranslatef(-5.8,0,0);
        glRotatef(90,0,0,1);
        cola->draw(activo,luz);
    glPopMatrix();

glPopMatrix();
}

void Estructura::setRotacionCola(float valor) {
    cola->anguloRotacion += valor;
    if(cola->anguloRotacion > 360) cola->anguloRotacion = 0;
}

float Estructura::getRotacionCola() {
    return cola->anguloRotacion;
}