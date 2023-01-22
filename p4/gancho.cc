#include "gancho.h"
#include "../auxiliar.h"


Gancho::Gancho(/* args */)
{
    velocidad = 0;
    cilindro = new Cilindro (40,40);
}

Gancho::~Gancho()
{
    if (cilindro!=nullptr) delete cilindro;
    cilindro = nullptr;

    std::cout<<"destructor gancho\n";
}

void Gancho::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();
        glTranslatef(0,velocidad,0);
        glScalef(3, 50-velocidad ,3);
        cilindro->draw(activo,luz);
glPopMatrix();
}