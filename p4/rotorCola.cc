#include "rotorCola.h"

RotorCola::RotorCola(/* args */)
{
    rotor = new Rotor();
    heli = new Helice(HELI,LARGO);
}

RotorCola::~RotorCola()
{
    if(rotor!=nullptr) delete rotor;
    if (heli!=nullptr) delete heli;
    rotor = nullptr;
    heli = nullptr;
    std::cout << "destructor rotor cola\n";
}

void RotorCola::draw(std::vector<bool> activo, bool luz)
{
    glRotatef(90,1,0,0);
    rotor->draw(activo,luz);
    heli->draw(activo,luz);
}