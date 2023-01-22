#include "aterrizaje.h"
#include "../auxiliar.h"

Aterrizaje::Aterrizaje(){
    p = new Patin();
}

Aterrizaje::~Aterrizaje(){
    if(p!=nullptr) delete p;
    p = nullptr;
}

void Aterrizaje::draw(std::vector<bool> activo, bool luz) {
    glPushMatrix();
        glTranslatef(0,0,2);
        p->draw(activo,luz);
    glPopMatrix();

    glPushMatrix();
        glRotatef(180,0,1,0);
        glTranslatef(0,0,2);
        p->draw(activo,luz);
    glPopMatrix();
}