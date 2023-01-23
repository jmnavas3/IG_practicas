/**
 * @file helicopteroCarga.h
 * @author jose maria navas cabrera (jmnavas@correo.ugr.es)
 * @brief Modelo jerarquico. Práctica 4. Informática Gráfica 22/23 UGR.
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef HELICOPTEROCARGA_H
#define HELICOPTEROCARGA_H

#include "gancho.h"
#include "helicoptero.h"

class HelicopteroCarga
{
private:
    float velocidad = 1 ;
    const float MAX_GANCHO = -80;
    bool subir = false;

    Gancho         * gancho = nullptr;
    Helicoptero    *helicoptero = nullptr;
public:
    const int numGradosLibertad = 3;

    HelicopteroCarga();
    ~HelicopteroCarga();

    void draw(std::vector<bool> a, bool luz=false);
    
    // movimiento del modelo
    void animar(int incrementar = 0);
    void moverGrado (int seleccion, int signo);

    void bajarGancho(float valor);
};




#endif