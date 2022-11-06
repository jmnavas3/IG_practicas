#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"

class Material
{
    private:
        static const Tupla4f amb_dif_defecto(0.1,0.5,0.8,1.0);
        static const Tupla4f esp_defecto(0.0,0.0,0.0,1.0);
        static const float brillo_defecto = 40.0f;
        // Tuplas RGBA, A=1
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    public:
        Material ();
        Material ( Tupla4f mdifuso,
                   Tupla4f mespecular,
                   Tupla4f mambiente,
                   float brillo );
        void aplicar();
};

#endif