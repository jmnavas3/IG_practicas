
#include "helicoptero.h"
#include "../auxiliar.h"

Helicoptero::Helicoptero()
{
    rotacionCola = 0.4;
    rotacionPrincipal = 0.2;
    movimientoGancho = 1;
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
    gancho->draw(a,luz);

    glScalef(10,10,10);
    glPushMatrix();
        estructura->draw(a,luz);
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(rotacionPrincipal,0,1,0);
        glTranslatef(0,4.4,0);
        rotorp->draw(a,luz);
    glPopMatrix();


glPopMatrix();
}

void Helicoptero::animar( int incrementar ) {
    if(incrementar==1){
        movimientoGancho+=0.01;
        rotacionCola+=0.01;
        rotacionPrincipal+=0.01;
        velocidad += 0.05;
    }
    else if(incrementar == -1){
        if(movimientoGancho > 0) movimientoGancho-=0.01;
        if(rotacionCola > 0) rotacionCola-=0.01;
        if(rotacionPrincipal > 0) rotacionPrincipal-=0.01;
        if(velocidad > 0) velocidad -=0.05;
    }

    bajarGancho(velocidad);
    modificaRotacionPrincipal(velocidad);
    modificaRotacionCola(velocidad);
}

void Helicoptero::moverGrado (int seleccion, int signo) {
    switch (seleccion) {
    case 0:
        bajarGancho(signo*velocidad);
        std::cout << "Gancho = " << gancho->velocidad << "\n";
        break;
    case 1:
        modificaRotacionPrincipal(signo*velocidad);
        std::cout << "Rotor principal = " << rotacionPrincipal << "\n";
        break;
    case 2:
        modificaRotacionCola(signo*velocidad);
        std::cout << "Rotor de cola = " << estructura->getRotacionCola() << "\n";
    case 3:
        animar(signo);  // todos los casos
        break;
    default:
        break;
    }
}

void Helicoptero::bajarGancho(float valor) {
    if (!subir){
        gancho->velocidad += valor;
        if (gancho->velocidad >= MAX_GANCHO) subir = true;
    }
}

void Helicoptero::modificaRotacionPrincipal(float valor) {
    rotacionPrincipal += valor;
    if (rotacionPrincipal>360) rotacionPrincipal = 0;

}

void Helicoptero::modificaRotacionCola(float valor) {
    estructura->setRotacionCola(valor);
}