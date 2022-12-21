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
    
      // glRotatef(-rot_idle,0,1,0);
      glPushMatrix();
        // base del rotor principal
        glPushMatrix();
            glTranslatef(0,10,0);
            glScalef(15,10,5);
            cilindro->draw(activo,luz);
        glPopMatrix();
         // cuerpo
         glTranslatef(0,-17,0);
         glScalef(20,20,20);
         glRotatef(-15, 0, 0, 1);
         glScalef(3,2,2);
         esfera->draw(activo,luz);
      glPopMatrix();

glPopMatrix();
}