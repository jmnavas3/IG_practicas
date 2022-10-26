// ** P2

#ifndef LATA_H_INCLUDED
#define LATA_H_INCLUDED

#include "objrevolucion.h"

class Lata : public ObjRevolucion
{
    private:
    std::vector<Tupla3f> superior;
    std::vector<Tupla3f> cuerpo;
    std::vector<Tupla3f> inferior;

    public:
    Lata ( const int num_instancias_perf );
} ;

#endif