/**
 * @file helicoptero.h
 * @author jose maria navas cabrera (jmnavas@correo.ugr.es)
 * @brief Modelo jerarquico. Práctica 4. Informática Gráfica 22/23 UGR.
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include "estructura.h"
#include "rotorPrincipal.h"
#include "gancho.h"

class Helicoptero
{
private:
    float rotacionPrincipal, rotacionCola;
    float movimientoGancho, escaladoGancho;

    Estructura * estructura = nullptr;
    RotorPrincipal * rotorp = nullptr;
    Gancho         * gancho = nullptr;
public:
    Helicoptero();
    ~Helicoptero();

    void draw(std::vector<bool> a, bool luz=false);
    
    // movimiento del modelo
    void moverGancho(float valor=0.0f);
    void modificaRotacionCola(float valor=0.0f);
    void modificaRotacionPrincipal(float valor=0.0f);
};




#endif