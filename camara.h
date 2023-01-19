#ifndef CAMARA_H
#define CAMARA_H

#include "auxiliar.h"

class Camara
{
private:
    // nota: (vector) VPN = (punto)eye - (punto)at

    Tupla3f eye, // PUNTO donde está el observador (VRP)
            at, // PUNTO al que se está mirando
            up; // VECTOR del sentido con el que mira
                 // suele ser (0,1,0)
    
    int tipo; // 0: PERSPECTIVA, 1: ORTOGONAL

    float alpha, beta, ratio_xy, ratio_yx,
          zoom_factor = 1.2, dist = 200, factor_z = 1;

    // parametros de volumen de visualización (frustum)
    float left,
          right,
          near,     // define mínimo del eje z de los objetos (si obj(z)< near, no se verá)
          far;      // igual que el anterior, si obj(z) > far, no se verá

    void init();
    Tupla3f rotarX(Tupla3f punto, float angle);
    Tupla3f rotarY(Tupla3f punto, float angle);
    Tupla3f rotarZ(Tupla3f punto, float angle);
public:
    float width, height,
          modo; // 0: examinar 1:first person
    Camara();
    Camara( Tupla3f eye1, Tupla3f at1);


    // "examinar" es lo mismo que hacíamos antes, en torno al origen
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    void mover(float x, float z);
    
    // se invoca cuando se detecta la rueda del ratón (cambiar ejeZ)
    void zoom (int factor);
    void reajustar(float x_width, float y_height);
    
    // nota: calcular el VPN para la vista en primera persona
    // recalcula el valor de los parámetros de giro
    // en X (observer_angle_x) y en Y (observer_angle_y)
    void girar (int x, int y, float ratio=0.1);
    
    void setObserver ();    // transformación de vista
    void setProyeccion();   // transformación de proyección
};



#endif