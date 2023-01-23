
#include "helicoptero.h"
#include "../auxiliar.h"

Helicoptero::Helicoptero()
{
    rotacionCola = 1;
    rotacionPrincipal = 1;
    rotorp = new RotorPrincipal();
    estructura = new Estructura();
}

Helicoptero::~Helicoptero()
{
    if ( rotorp!=nullptr) delete rotorp;
    if ( estructura!=nullptr) delete estructura;

    rotorp  = nullptr;
    estructura  = nullptr;

    std::cout << "destructor HELICOPTERO\n";

}

void Helicoptero::draw(std::vector<bool> a, bool luz)
{
glPushMatrix();

    glScalef(10,10,10);
    glPushMatrix();
        glTranslatef(0,4.4,0);
        glRotatef(rotacionPrincipal,0,1,0);
        rotorp->draw(a,luz);
    glPopMatrix();
    
    estructura->draw(a,luz);

glPopMatrix();
}

void Helicoptero::animar( int incrementar ) {

    modificaRotacionPrincipal(incrementar);
    modificaRotacionCola(incrementar);
}

void Helicoptero::modificaRotacionPrincipal(float valor) {
    rotacionPrincipal += valor;
    if (rotacionPrincipal>360) rotacionPrincipal = 0;

}

void Helicoptero::modificaRotacionCola(float valor) {
    estructura->setRotacionCola(valor);
}