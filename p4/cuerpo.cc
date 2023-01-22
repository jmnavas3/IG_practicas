#include "cuerpo.h"
#include "../auxiliar.h"

Cuerpo::Cuerpo(/* args */)
{
    esfera = new Esfera(40,40);
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

    // cabina
    glPushMatrix();
        glScalef(6,4,4);            // rx=2 dx=4 ry=1 dy=2
        esfera->draw(activo,luz);
    glPopMatrix();
    // base del rotor principal
    glPushMatrix();
        glTranslatef(0,3.9,0);
        glScalef(1,0.5,1);
        cilindro->draw(activo,luz);
    glPopMatrix();

}