#include "cono.h"

Cono::Cono ( const int num_vert_perfil ,
                     const int num_instancias_perf ,
                     const float altura ,
                     const float radio )
{
    //crear perfil original de un cono
    std::vector<Tupla3f> perfil;
    float aux;
    perfil.resize(num_vert_perfil);
    for(int i = 0; i < num_vert_perfil-1; i++){
        aux = (float)(num_vert_perfil-i)/num_vert_perfil;
        perfil[i+1] = {radio*aux , altura*((float)i/num_vert_perfil), 0.0f};
    }
    perfil[0] = {0.0f,perfil[1](Y),0.0f};
    perfil[num_vert_perfil-1] = {0.0f,altura,0.0f};

    crearMalla(perfil,num_instancias_perf);
    
}