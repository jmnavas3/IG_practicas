
#include "helicoptero.h"
#include "../auxiliar.h"

Helicoptero::Helicoptero()
{
    rotacionPrincipal = 0.4;
    rotacionCola = 0.2;
    movimientoGancho = 0.1;
    escaladoGancho = 0.1;
    gancho = new Gancho();
    rotorp = new RotorPrincipal();
    estructura = new Estructura();
}

Helicoptero::~Helicoptero()
{
    if ( gancho!=nullptr) delete gancho;
    if ( rotorp!=nullptr) delete rotorp;
    if ( estructura!=nullptr) delete estructura;

    gancho  = nullptr;
    rotorp  = nullptr;
    estructura  = nullptr;

    std::cout << "destructor HELICOPTERO\n";

}

void Helicoptero::draw(std::vector<bool> a, bool luz)
{
glPushMatrix();
    //glTranslatef(-10,10,40);
    estructura->draw(a,luz);

    glPushMatrix();
        rotorp->draw(a,luz);
    glPopMatrix();

    gancho->draw(a,luz);

glPopMatrix();
}


void Helicoptero::animar() {
    //moverGancho();
    //modificaRotacionCola();
    //modificaRotacionPrincipal();
}