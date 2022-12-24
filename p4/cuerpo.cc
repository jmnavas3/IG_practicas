#include "cuerpo.h"
#include "../auxiliar.h"

Cuerpo::Cuerpo(/* args */)
{
    esfera = new Esfera(20,20);
    cilindro = new Cilindro(20,20);
}

Cuerpo::~Cuerpo()
{
    if (esfera!=nullptr) delete esfera;
    if (cilindro!=nullptr) delete cilindro;

    esfera = nullptr;
    cilindro = nullptr;
    std::cout << "destructor cuerpo\n";
}

void Cuerpo::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();

    glScalef(20,20,20);
    // glTranslatef(-0.3,0,0);
    // cabina
    glPushMatrix();
        glRotatef(-15,0,0,1);
        glScalef(2,1,1);            // r=2 d=4
        esfera->draw(activo,luz);
    glPopMatrix();
    // base del rotor principal
    glPushMatrix();
        glTranslatef(0,0.9,0);
        glScalef(0.3,0.3,0.3);
        //glRotatef(15,0,0,1);
        cilindro->draw(activo,luz);
    glPopMatrix();

glPopMatrix();
}