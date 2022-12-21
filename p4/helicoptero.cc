
#include "helicoptero.h"
#include "../auxiliar.h"

Helicoptero::Helicoptero()
{
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
    glTranslatef(-10,10,40);
    estructura->draw(a,luz);

    rotorp->draw(a,luz);

    glScalef(10,15,10);
    gancho->draw(a,luz);

glPopMatrix();
}