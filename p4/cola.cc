#include "cola.h"
#include "../auxiliar.h"

Cola::Cola(/* args */)
{
    anguloRotacion = 1;
    cubo = new Cubo();
    cono = new Cono (20,20);
    rotorC = new Rotor();
}

Cola::~Cola()
{
    if (cubo!=nullptr)  delete cubo;
    if (cono!=nullptr) delete cono;
    if (rotorC!=nullptr) delete rotorC;

    cono = nullptr;
    cubo = nullptr;
    rotorC = nullptr;
    std::cout << "destructor cola\n";
}

void Cola::draw(std::vector<bool> activo, bool luz)
{

// cola
glPushMatrix();
    glScalef(1.5,15,1.5);
    cono->draw(activo,luz);
glPopMatrix();

// rotor cola
glPushMatrix();
    glTranslatef(0,10,0);  // los movemos hacia la punta de la cola
    
    glRotatef(anguloRotacion,0,0,1);
    glRotatef(90,1,0,0);
    rotorC->draw(activo,luz);
    // helices
    glPushMatrix();
        glTranslatef(0,1,0);
        for(int i = 0; i<4; i++){
            glRotatef(90,0,1,0);
            rotorC->drawHelice(activo,luz,15);
        }
    glPopMatrix();
glPopMatrix();


}