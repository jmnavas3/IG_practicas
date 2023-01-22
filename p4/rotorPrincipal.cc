#include "rotorPrincipal.h"

RotorPrincipal::RotorPrincipal(/* args */)
{
    rotor = new Rotor();
    heli = new Helice(HELI,LARGO);
}

RotorPrincipal::~RotorPrincipal()
{
    if(rotor!=nullptr) delete rotor;
    if (heli!=nullptr) delete heli;
    rotor = nullptr;
    heli = nullptr;
    std::cout << "destructor rotor principal\n";
}

void RotorPrincipal::draw(std::vector<bool> activo, bool luz)
{
    rotor->draw(activo,luz);
    heli->draw(activo,luz);
}