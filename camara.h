#ifndef CAMARA_H
#define CAMARA_H

#include "auxiliar.h"

class Camara
{
private:
    // nota: (vector) VPN = (punto)eye - (punto)at

    Tupla3f eye; // PUNTO donde está el observador (VRP)
    Tupla3f  at; // PUNTO al que se está mirando
    Tupla3f  up; // VECTOR del sentido con el que mira
                 // suele ser (0,1,0)
    
    float alpha, beta;
    const float zoom_factor = 1.2, dist = 200;
    int tipo; // ortogonal y perspectiva
    // parametros de volumen de visualización (frustum)
    float left,
          right,
          near,     // define mínimo del eje z de los objetos (si obj(z)< near, no se verá)
          far;      // igual que el anterior, si obj(z) > far, no se verá
public:
    Camara();
    Camara( Tupla3f eye1, Tupla3f at1);

    // "examinar" es lo mismo que hacíamos antes, en torno al origen
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    void mover(float x, float y, float z);
    
    // se invoca cuando se detecta la rueda del ratón (cambiar ejeZ)
    void zoom (int factor);
    
    // nota: calcular el VPN para la vista en primera persona
    // recalcula el valor de los parámetros de giro
    // en X (observer_angle_x) y en Y (observer_angle_y)
    void girar (int x, int y);
    
    void setObserver ();    // transformación de vista
    void setProyeccion();   // transformación de proyección
};



#endif