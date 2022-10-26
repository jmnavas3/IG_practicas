#include "lata.h"

Lata::Lata(const int num_instancias_perf)
{
    // obtenemos los 3 perfiles de lata, 
    // guardamos cada uno en un vector de tuplas diferente
    // y los juntamos en el perfil final

    ply::read_vertices("./plys/lata-psup",superior); //perfil superior
    ply::read_vertices("./plys/lata-pcue",cuerpo); //perfil cuerpo
    ply::read_vertices("./plys/lata-pinf", inferior); //perfil inferior

    perfil = superior;
    perfil.insert(perfil.end(), cuerpo.begin(), cuerpo.end());
    perfil.insert(perfil.end(), inferior.begin(), inferior.end());

    crearMalla(perfil,num_instancias_perf);
}