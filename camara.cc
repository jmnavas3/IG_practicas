#include "camara.h"

Camara::Camara () {
    eye= {0,0,dist};
    at = {0,0,0};
    up = {0,1,0};
    alpha = 0;
    beta = 0;
}

Camara::Camara(Tupla3f eye1, Tupla3f at1){
    eye = eye1;
    at1 = at1;
    up = {0,1,0};
}

// método de cámara orbital. Modifica el VRP ó eye (posición de la cámara)
// esto implica un cambio en el vector VPN (view plane normal) perpendicular al plano de proyección
void Camara::girar ( int x, int y ) {
    
    alpha+=(float)(x*0.01);
    beta+=(float)(y*0.01);

    eye(Z) = dist*cos(alpha)*cos(beta);
    eye(Y) = dist*cos(alpha)*sin(beta);
    eye(X) = dist*sin(alpha);

    std::cout << eye << "\n";
   
}

// método de cámara primera persona
void Camara::mover ( float x, float y, float z) {

}

// si factor es negativo, zoom_out, sino, zoom_in
void Camara::zoom ( int factor ) {
    eye(Z) = (factor<0) ? eye(Z)/zoom_factor : eye(Z)*zoom_factor;
    // if(tipo==ortho)
    // glOrtho(0.5*-wx,wx,0.5*-wy,0.5*wy)
}

void Camara::setObserver ( ) {
    gluLookAt(eye(X), eye(Y), eye(Z),
              at(X),  at(Y),  at(Z),
              up(X),  up(Y),  up(Z));
}

void Camara::setProyeccion ( ) {
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // const float wx = float(Height)*ratio_xy ;
    // glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}

// -------- métodos rotar -----------

void Camara::rotarXExaminar (float angle) {

}

void Camara::rotarYExaminar (float angle) {

}

void Camara::rotarZExaminar (float angle) {

}

void Camara::rotarXFirstPerson (float angle) {

}

void Camara::rotarYFirstPerson (float angle) {

}

void Camara::rotarZFirstPerson (float angle) {

}
