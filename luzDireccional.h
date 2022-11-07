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
        LuzDireccional(const Tupla2f & orientacion,
                       GLenum idLuz,
                       Tupla4f colorAmbiente,
                       Tupla4f colorEspecular,
                       Tupla4f colorDifuso) ;

        void variarAnguloAlpha (float incremento) ;
        void variarAnguloBeta (float incremento) ;
        void cambiarAngulo();
};

#endif