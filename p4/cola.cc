#include "cola.h"
#include "../auxiliar.h"

Cola::Cola(/* args */)
{
    cubo = new Cubo();
    cono = new Cono (20,20);
}

Cola::~Cola()
{
    if (cubo!=nullptr)  delete cubo;
    if (cono!=nullptr) delete cono;

    cono = nullptr;
    cubo = nullptr;
    std::cout << "destructor cola\n";
}

void Cola::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();
    // cola
    glTranslatef(-20,-5,0);
    glRotatef(90,0,0,1);
    glScalef(10,70,10);
    cono->draw(activo,luz);
    // parte donde van las "aletas" de la cola
    glPushMatrix();
        glTranslatef(0,1,0);
        glScalef(0.5,1,0.5);
        cubo->draw(activo,luz);
        
        glScalef(10,10,10);
        glPushMatrix();
            glTranslatef(0,1,0);
            glScalef(0.1,2,0.1);
            glRotatef(-45,0,0,1);
            cubo->draw(activo,luz);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-1,0);
            glScalef(0.1,2,0.1);
            glRotatef(45,0,0,1);
            cubo->draw(activo,luz);
        glPopMatrix();
    glPopMatrix();

glPopMatrix();
}