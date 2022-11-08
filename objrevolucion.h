// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#define EPSILON 0.00000000

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************

class ObjRevolucion : public Malla3D
{
public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias);
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias) ;
protected:
    std::vector<Tupla3f> perfil;
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);

} ;




#endif
