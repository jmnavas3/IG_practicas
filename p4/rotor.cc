#include "rotor.h"

Rotor::Rotor(/* args */)
{
    cilindro = new Cilindro(40,40);
}

Rotor::~Rotor()
{
    if (cilindro!=nullptr) delete cilindro;
    cilindro = nullptr;
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