#include "camara.h"

Camara::Camara () {
    eye= {0,0,200};
    at = {0,0,0};
    up = {0,1,0};
}

Camara::Camara(Tupla3f eye1, Tupla3f at1){
    eye = eye1;
    at1 = at1;
    up = {0,1,0};
}

void Camara::girar ( int x, int y ) {
    eye(X) = x;
    eye(Y) = y;
}

void Camara::mover ( float x, float y, float z) {

}

void Camara::zoom ( float factor ) {
    eye(Z) *=factor; // observer_distance
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
