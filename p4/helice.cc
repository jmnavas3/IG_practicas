#include "helice.h"

Helice::Helice(/* args */)
{
    cubo = new Cubo ();
    largoHelice = 50;
    nHelices = 2;
}

Helice::Helice(int numero, int largo){
    nHelices=numero;
    largoHelice=largo;
    cubo = new Cubo();
}

Helice::~Helice()
{
    if(cubo != nullptr) delete cubo;
    cubo = nullptr;
}

void Helice::draw(std::vector<bool> activo, bool luz) {
    ajuste = ((float)largoHelice/2) + 0.25;
    // helice dcha
    for (int i = 0; i < nHelices; i++) // dibujamos nHelices rotando por cada una 360/nhelices grados
    {
        glRotatef(GRADOS/(float)nHelices, 0, 1, 0);
        glPushMatrix();
            glTranslatef(1, 1.125, 0); //1.125 para ajustarlo con parte superior de rotor
            // glTranslatef(1,0.125,0);
            glScalef(0.25,0.25,0.25);
            cubo->draw(activo,luz); // union de la pala con la base
            glPushMatrix();
                glTranslatef(ajuste,0.25,0);
                glScalef(largoHelice,0.1,6);
                cubo->draw(activo,luz);
            glPopMatrix();
        glPopMatrix();
    }
}