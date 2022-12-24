#include "luzAnimada.h"
#include "auxiliar.h"

LuzAnimada::LuzAnimada() {
    angulo = 0;
    velocidad = 0.7;
    esfera = new Esfera (20,20); // dejamos material por defecto

    posicionLuz = { -2.0 , -1.0  , 0.0 };
    Tupla4f ambiental   = { 0.3 , 0.0 , 0.4 , 1.0 };
    Tupla4f especular   = { 1.0 , 0.7 , 1.0 , 1.0 };
    Tupla4f difusa      = { 0.7 , 0.4 , 0.7 , 1.0 };
    
    luz = new LuzPosicional(posicionLuz, GL_LIGHT2, ambiental, especular, difusa);
    luzD= new LuzDireccional({0,0}, GL_LIGHT3, {1,1,1,1}, {1,1,1,1}, {1,1,1,1});
}

LuzAnimada::~LuzAnimada(){
    if(luz!= nullptr) delete luz;
    if(luzD!=nullptr) delete luzD;

    luz = nullptr;
    luzD = nullptr;
}

void LuzAnimada::draw(std::vector<bool> activo, bool luzActivo){
    
    // luz direccional animada y fijada a la camara
    glPushMatrix();
        glLoadIdentity();
        luzD->activar(luzActivo);
    glPopMatrix();

    // luz posicional animada y fijada a objeto
    glPushMatrix();
        glScalef(10,10,10);
        glRotatef(angulo,0,1,0);
        glTranslatef(10,2,0);
        luz->activar(luzActivo);
        esfera->draw(activo,luzActivo);
    glPopMatrix();
}


void LuzAnimada::animar(){
    angulo += velocidad;
    if(angulo > 360){
        angulo = 0;
        if((int)angulo%10 == 0)
        luzD->animarColor();
    }
}