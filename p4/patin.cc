#include "patin.h"
#include "../auxiliar.h"

Patin::Patin(){
    c = new Cilindro(10,10);    // h=1 r=1 d=2
}

Patin::~Patin(){
    if(c!=nullptr) delete c;
    c = nullptr;
}

void Patin::draw(std::vector<bool> activo, bool luz) {
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