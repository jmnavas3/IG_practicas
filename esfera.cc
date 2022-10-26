#include "esfera.h"

Esfera::Esfera ( const int num_vert_perfil ,
                     const int num_instancias_perf ,
                     const float radio )
{
    //crear perfil original de una esfera
    float aux;
    perfil.resize(num_vert_perfil);
    for(int i = 0; i < num_vert_perfil; i++){
        aux = (float)(i*PI)/num_vert_perfil;
        perfil[i] = { (float)sin(aux)*radio, (float)-cos(aux)*radio, 0.0f};
    }
    // perfil[0] = {0.0f,perfil[1](Y),0.0f};
    perfil[num_vert_perfil-1] = {0.0f,radio,0.0f};

    crearMalla(perfil,num_instancias_perf);
    
}