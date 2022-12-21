#include "esfera.h"

Esfera::Esfera ( const int num_vert_perfil ,
                     const int num_instancias_perf ,
                     const float radio )
{
    float aux;
    perfil.resize(num_vert_perfil);
    // usamos -cos() en el eje Y para que empiece desde abajo: -cos(0) = -1
    for(int i = 0; i < num_vert_perfil; i++){
        aux = (float)(i*PI)/(num_vert_perfil-1);
        perfil[i] = { (float)sin(aux)*radio, (float)-cos(aux)*radio, 0.0f};
    }
    perfil[0](X)=0.0f;
    perfil[num_vert_perfil-1] = {0.0f,radio,0.0f};

    //t = new Textura("./p5/earth.jpg");
    crearMalla(perfil,num_instancias_perf);
    if(t!=nullptr) genNormales();
    else genNormales();
}
