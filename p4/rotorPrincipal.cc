#include "rotorPrincipal.h"
#include "../auxiliar.h"

RotorPrincipal::RotorPrincipal(/* args */)
{
    cilindro = new Cilindro(20,20);
    cubo = new Cubo();
}

RotorPrincipal::~RotorPrincipal()
{
    if (cilindro!=nullptr) delete cilindro;
    if(cubo!=nullptr) delete cubo;
    cubo = nullptr;
    cilindro = nullptr;
    std::cout << "destructor rotor principal\n";
}

void RotorPrincipal::draw(std::vector<bool> activo, bool luz)
{
glPushMatrix();
    
    glScalef(8,8,8);
    glTranslatef(0,1.9,0);
    glPushMatrix();
        glRotatef(0.2, 0, 1, 0);
        glPushMatrix();
        glTranslatef(0,1,0);
        glScalef(0.25,1,0.25);
        cilindro->draw(activo,luz);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0,2,0);
        glPushMatrix();
            glScalef(1,0.5,1);
            cilindro->draw(activo,luz);
        glPopMatrix();
        // hélice_dcha
        glPushMatrix();
            glRotatef(180,0,1,0);
            glTranslatef(-1,0.125,0);
            glScalef(0.25,0.25,0.25);
            cubo->draw(activo,luz);
            glPushMatrix();
                glTranslatef(-25.25,0.25,0);
                glScalef(50,0.1,6);
                cubo->draw(activo,luz);
            glPopMatrix();
        glPopMatrix();
        // hélice_izda
        glPushMatrix();
            glTranslatef(-1,0.125,0);
            glScalef(0.25,0.25,0.25);
            cubo->draw(activo,luz); // union de la pala con la base
            glPushMatrix();
                glTranslatef(-25.25,0.25,0);
                glScalef(50,0.1,6);
                cubo->draw(activo,luz);
            glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    glPopMatrix();

glPopMatrix();
}