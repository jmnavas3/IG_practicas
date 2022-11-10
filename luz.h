
#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "auxiliar.h"

class Luz
{

    public:

    void activar(bool interruptor);

    protected:

    Tupla4f posicion;           // vector de 4 coordenadas, la 4ª indica si la luz es direccional (0) o posicional (!0)
    GLenum id;                  // "interruptores": GL_LIGHTi
    Tupla4f colorAmbiente;      // valor defecto: (0.0f, 0.0f, 0.0f, 1.0f) 
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

};


#endif