#include "lata.h"

Lata::Lata(const int num_instancias_perf, bool ponerTextura)
{
    ply::read_vertices("./plys/lata-pinf", perfil);
    // perfil.pop_back();

    ply::read_vertices("./plys/lata-pcue",cuerpo);
    for(int i =0; i < (int)cuerpo.size(); i++)
        perfil.push_back(cuerpo[i]);

    ply::read_vertices("./plys/lata-psup",cuerpo);
    for(int i =0; i < (int)cuerpo.size(); i++)
        perfil.push_back(cuerpo[i]);

    repetidos();

    if(ponerTextura) t = new Textura("./p5/text-lata-1.jpg");
    crearMalla(perfil,num_instancias_perf);
    genNormales();
    //genNormales( (t!=nullptr)? perfil.size(): -1 );
}

Lata::~Lata(){
    if(t != nullptr) delete t;
    t = nullptr;
}