#include "cola.h"
#include "../auxiliar.h"

Cola::Cola(/* args */)
{
    anguloRotacion = 1;
    cono = new Cono (40,40);
    rotorC = new RotorCola();
}

Cola::~Cola()
{
    if (cono!=nullptr)  delete cono;
    if (rotorC!=nullptr) delete rotorC;

    cono = nullptr;
    rotorC = nullptr;
    std::cout << "destructor cola\n";
}

void Cola::draw(std::vector<bool> activo, bool luz)
{

glRotatef(90,0,0,1);
glPushMatrix();
    glPushMatrix();
        // rotor cola
        glTranslatef(0,10,0);  // los movemos hacia la punta de la cola
        glRotatef(anguloRotacion,0,0,1);
        rotorC->draw(activo,luz);
    glPopMatrix();
    //cola
    glScalef(1.5,15,1.5);
    cono->draw(activo,luz);
glPopMatrix();


}