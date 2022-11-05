#ifndef DIRECCIONAL_H_INCLUDED
#define DIRECCIONAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class LuzDireccional : public Luz
{
    protected:
        float alpha;
        float beta;


    public:
        LuzDireccional(const Tupla2f & orientacion) ;

        void variarAnguloAlpha (float incremento) ;
        void variarAnguloBeta (float incremento) ;
};

#endif