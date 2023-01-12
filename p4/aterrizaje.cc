#include "aterrizaje.h"
#include "../auxiliar.h"

Aterrizaje::Aterrizaje(){
    c = new Cilindro(20,20);    // h=1 r=1 d=2
}

Aterrizaje::~Aterrizaje(){
    if(c!=nullptr) delete c;
    c = nullptr;
}

void Aterrizaje::draw(std::vector<bool> activo, bool luz) {
    glPushMatrix();
        glTranslatef(0,0,2);
        patin(activo,luz);
    glPopMatrix();

    glPushMatrix();
        glRotatef(180,0,1,0);
        glTranslatef(0,0,2);
        patin(activo,luz);
    glPopMatrix();
}

void Aterrizaje::patin(std::vector<bool>activo, bool luz) {
    glPushMatrix();
        glTranslatef(-4,0,0);
        glRotatef(-90,0,0,1);
        glScalef(0.5,8,0.5);
        c->draw(activo,luz);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2,0,0);
        glRotatef(-45,1,0,0);
        glScalef(0.5,2,0.5);
        c->draw(activo,luz);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2,0,0);
        glRotatef(-45,1,0,0);
        glScalef(0.5,2,0.5);
        c->draw(activo,luz);
    glPopMatrix();
}