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
    perfil[0](X)=0.0f; // CUIDADO CON COMA FLOTANTE, SON UNA APROXIMACION
    perfil[num_vert_perfil-1] = {0.0f,radio,0.0f};

    crearMalla(perfil,num_instancias_perf);
    genNormales();
}

// para una esfera, las normales de sus vértices se pueden
// hacer restando al vector que define a cada vértice el vector del
// vértice central, que en nuestro caso es {0,0,0}, entonces, basta
// con normalizar cada vértice
void Esfera::genNormales() {
    for(int i=0; i<v.size();i++){
        nv.push_back(v[i].normalized());
    }
}