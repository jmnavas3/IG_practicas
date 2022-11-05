#ifndef POSICIONAL_H_INCLUDED
#define POSICIONAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class LuzPosicional : public Luz
{
    public:
        LuzPosicional(const Tupla3f & posicion) ;

};

#endif