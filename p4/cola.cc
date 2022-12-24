#include "cola.h"
#include "../auxiliar.h"

Cola::Cola(/* args */)
{
    cubo = new Cubo();
    cono = new Cono (20,20);
    rotorC = new RotorPrincipal();
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
glPushMatrix();
    // parte alargada que parte del inicio
    glTranslatef(-35,5,0);     // movemos la cola a su parte correspondiente
    glRotatef(90,0,0,1);
    glScalef(10,50,10);

    glPushMatrix();
        // cola
        glPushMatrix();
            glScalef(1,1.5,1);
            cono->draw(activo,luz);
        glPopMatrix();
        // parte adherida a la cola
        glPushMatrix();
            glTranslatef(0,1,0);  // los movemos hacia la punta de la cola
            // rotor cola
            glPushMatrix();
                glScalef(0.3,0.3,0.3);
                rotorC->draw(activo,luz);
            glPopMatrix();
            // estabilizadores
            glRotatef(90,0,0,1);
            glScalef(1,0.2,1);  // tamaño proporcional
            // estabilizador superior
            glPushMatrix();
                glRotatef(20,1,0,0);
                glScalef(1,1,0.1);
                cubo->draw(activo,luz);
            glPopMatrix();
            // estabilizador inferior
            glPushMatrix();
                glRotatef(-20,1,0,0);
                glTranslatef(0,-1,0);   // lo movemos abajo
                glScalef(1,1,0.1);
                cubo->draw(activo,luz);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();

glPopMatrix();
}