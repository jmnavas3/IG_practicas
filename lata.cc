#include "lata.h"

Lata::Lata(const int num_instancias_perf)
{
    ply::read_vertices("./plys/lata-pinf", perfil);
    perfil.pop_back();

    ply::read_vertices("./plys/lata-pcue",cuerpo);
    for(int i =0; i<cuerpo.size(); i++)
        perfil.push_back(cuerpo[i]);

    ply::read_vertices("./plys/lata-psup",cuerpo);
    for(int i =0; i<cuerpo.size(); i++)
        perfil.push_back(cuerpo[i]);

    repetidos();

    t = new Textura("./p5/text-lata-1.jpg");
    std::cout << "vertices perfil original " << perfil.size() << "\n"; 
    crearMalla(perfil,num_instancias_perf);
    genNormales();
}

Lata::~Lata(){
    if(t != nullptr) delete t;
    t = nullptr;
    std::cout << "objeto destruido\n";
}