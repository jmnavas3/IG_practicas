#include "cilindro.h"

Cilindro::Cilindro ( const int num_vert_perfil ,
                     const int num_instancias_perf ,
                     const float altura ,
                     const float radio )
{
    perfil.resize(num_vert_perfil);
    for(int i = 0; i < num_vert_perfil; i++){
        perfil[i] = {radio , i*(altura/num_vert_perfil), 0.0f};
    }
    perfil.insert(perfil.begin(), {0.0f, 0.0f, 0.0f});  // añade al principio el vertice de la tapa inf. (0,0,0)
    perfil.push_back({radio,altura,0.0f});              // añade al final el vertice superior
    perfil.push_back({0.0f,altura,0.0f});               // añade al final el vertice de la tapa superior (0,altura,0)

    crearMalla(perfil,num_instancias_perf);
    genNormales();
}