#include "helicopteroCarga.h"

HelicopteroCarga::HelicopteroCarga()
{
    gancho = new Gancho();
    helicoptero = new Helicoptero();
}

HelicopteroCarga::~HelicopteroCarga()
{
    if ( gancho!=nullptr) delete gancho;
    if (helicoptero!=nullptr) delete helicoptero;

    gancho  = nullptr;
    helicoptero = nullptr;

    std::cout << "destructor MODELO JERARQUICO\n";
}

void HelicopteroCarga::draw(std::vector<bool> a, bool luz)
{
glPushMatrix();    
    helicoptero->draw(a,luz);
    
    glTranslatef(0,-88,0);
    gancho->draw(a,luz);
glPopMatrix();
}

void HelicopteroCarga::animar( int incrementar ) {
    if(incrementar==1){
        velocidad += 0.1;
    }
    else if(incrementar == -1){
        if(velocidad > 0) velocidad -=0.1;
    }

    bajarGancho(velocidad);
    helicoptero->animar(velocidad);
}

void HelicopteroCarga::moverGrado (int seleccion, int signo) {
    switch (seleccion) {
    case 0:
        bajarGancho(signo*velocidad);
        break;
    case 1:
        helicoptero->modificaRotacionPrincipal(velocidad);
        break;
    case 2:
        helicoptero->modificaRotacionCola(velocidad);
    default:
        break;
    }
}

void HelicopteroCarga::bajarGancho(float valor) {
    gancho->velocidad += (subir) ? valor : -valor;
    if (gancho->velocidad <= MAX_GANCHO){
        subir = true;
    } 
    else if(gancho->velocidad>=0){
        subir = false;
    }
}
