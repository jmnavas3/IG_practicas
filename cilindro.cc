#include "cilindro.h"

Cilindro::Cilindro ( const int num_vert_perfil ,
                     const int num_instancias_perf ,
                     const float altura ,
                     const float radio )
{
    //crear perfil original de un cilindro
    // nota: dentro del bucle restamos 3 al numero de vertices del denominador
    // para que la altura del último vértice sea igual a la pasada por parametro
    perfil.resize(num_vert_perfil);
    for(int i = 1; i < num_vert_perfil-1; i++){
        perfil[i] = {radio , altura*((float)(i-1)/(num_vert_perfil-3)), 0.0f};
    }
    // perfil[0] es la tapa inferior y perfil[num_vert_perfil-1] es la superior
    perfil[0] = {0.0f,perfil[1](Y),0.0f};
    perfil[num_vert_perfil-1] = {0.0f,perfil[num_vert_perfil-2](Y),0.0f};

    crearMalla(perfil,num_instancias_perf);
}