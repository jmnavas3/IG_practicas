// ** P2

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
    public:
    Esfera ( const int num_vert_perfil ,
               const int num_instancias_perf ,
               const float radio=1 );
    void genNormales() override;
} ;

#endif