
#include "helicoptero.h"
#include "../auxiliar.h"

Helicoptero::Helicoptero()
{
    rotacionCola = 1;
    rotacionPrincipal = 1;
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

    glPushMatrix();
        glTranslatef(0,-88,0);
        gancho->draw(a,luz);
    glPopMatrix();
    
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
    if(incrementar==1){
        movimientoGancho+=0.01;
        velocidad += 0.1;
        std::cout << "velocidad=" << velocidad << "\n";
    }
    else if(incrementar == -1){
        if(movimientoGancho > 0) movimientoGancho-=0.01;
        if(velocidad > 0) velocidad -=0.1;
        std::cout << "velocidad=" << velocidad << "\n";
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
        modificaRotacionPrincipal(velocidad);
        // modificaRotacionPrincipal(signo*velocidad);
        std::cout << "Rotor principal = " << rotacionPrincipal << "\n";
        break;
    case 2:
        // modificaRotacionCola(signo*velocidad);
        estructura->setRotacionCola(velocidad); // aumenta 5% valor de angulo de rotacion de cola
        std::cout << "Rotor de cola = " << estructura->getRotacionCola() << "\n";
    default:
        break;
    }
}

void Helicoptero::bajarGancho(float valor) {
    gancho->velocidad += (subir) ? valor : -valor;
    if (gancho->velocidad <= MAX_GANCHO){
        subir = true;
    } 
    else if(gancho->velocidad>=0){
        subir = false;
    }
}

void Helicoptero::modificaRotacionPrincipal(float valor) {
    rotacionPrincipal += velocidad;
    if (rotacionPrincipal>360) rotacionPrincipal = 0;

}

void Helicoptero::modificaRotacionCola(float valor) {
    estructura->setRotacionCola(velocidad);
}