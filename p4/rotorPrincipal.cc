#include "rotorPrincipal.h"
#include "../auxiliar.h"

RotorPrincipal::RotorPrincipal(/* args */)
{
    cilindro = new Cilindro(40,40);
    cubo = new Cubo();
    rotor = new Rotor();
}

RotorPrincipal::~RotorPrincipal()
{
    if (cilindro!=nullptr) delete cilindro;
    if(cubo!=nullptr) delete cubo;
    if(rotor!=nullptr) delete rotor;
    cubo = nullptr;
    cilindro = nullptr;
    std::cout << "destructor rotor principal\n";
}

void RotorPrincipal::draw(std::vector<bool> activo, bool luz)
{
    rotor->draw(activo,luz);
    
    glPushMatrix();
        glTranslatef(0,1,0);
        
        rotor->drawHelice(activo,luz);
        glRotatef(180,0,1,0);
        rotor->drawHelice(activo,luz);
    glPopMatrix();
}