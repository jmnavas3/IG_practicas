#include "rotor.h"
#include "../auxiliar.h"

Rotor::Rotor(/* args */)
{
    cilindro = new Cilindro(40,40);
    cubo = new Cubo ();
}

Rotor::~Rotor()
{
    if (cilindro!=nullptr) delete cilindro;
    if(cubo != nullptr) delete cubo;
    cilindro = nullptr;
    cubo = nullptr;
    std::cout << "destructor Rotor\n";
}

void Rotor::draw(std::vector<bool> activo, bool luz)
{
    glPushMatrix();
        glScalef(0.25,1,0.25);
        cilindro->draw(activo,luz);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1,0);
        glScalef(1,0.5,1);
        cilindro->draw(activo,luz);
    glPopMatrix();
}

void Rotor::drawHelice(std::vector<bool> activo, bool luz, int largoHelice) {
    ajuste = ((float)largoHelice/2) + 0.25;
    // helice izda
    glPushMatrix();
        glTranslatef(-1,0.125,0);
        glScalef(0.25,0.25,0.25);
        cubo->draw(activo,luz); // union de la pala con la base
        glPushMatrix();
            glTranslatef(-ajuste,0.25,0);
            glScalef(largoHelice,0.1,6);
            cubo->draw(activo,luz);
        glPopMatrix();
    glPopMatrix();
}