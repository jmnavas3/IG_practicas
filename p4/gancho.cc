#include "gancho.h"
#include "../auxiliar.h"


Gancho::Gancho(/* args */)
{
    velocidad = 0;
    cilindro = new Cilindro (20,20);
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
    
    glScalef(0.3, 10 ,0.3);
    glTranslatef(0,-1,0);
    cilindro->draw(activo,luz);

glPopMatrix();
}