#include "camara.h"

void Camara::init(){
    alpha = beta = 0;
    ratio_xy = ratio_yx = 1;
    near = 50;
    far = 2000;
    up = {0,1,0};
    modo = 0;
}

Camara::Camara () {
    init();
    eye = {0,0,dist};
    at = {0,0,0};
    tipo = 0;
}

Camara::Camara(Tupla3f eye1, Tupla3f at1){
    init();
    eye = eye1;
    at1 = at1;
    tipo = 1;
}

// si factor es negativo, zoom_out, sino, zoom_in
void Camara::zoom ( int factor ) {
    factor_z = (factor<0) ? factor_z*0.95 : factor_z*1.05;
    if(factor_z<0.6 || factor_z>6){
        factor_z = 1;
        std::cout << "\nLIMITE DE ZOOM\n";
    }
}

void Camara::setObserver ( ) {
    gluLookAt(eye(X), eye(Y), eye(Z),
              at(X),  at(Y),  at(Z),
              up(X),  up(Y),  up(Z));
}

void Camara::setProyeccion (  ) {
    if (tipo == 0){
        glFrustum( -width*factor_z, width*factor_z, -height*factor_z, height*factor_z, near, far );
    }
    else if (tipo== 1){
        glOrtho(-width*5*factor_z, width*5*factor_z, -height*5*factor_z, height*5*factor_z, near, far);
    }
}

void Camara::reajustar(float x_width, float y_height){
    ratio_xy = y_height/x_width;
    ratio_yx = x_width/y_height;
    width = x_width/10;
    height = y_height/10;
    
}

// -------- métodos rotar -----------
Tupla3f Camara::rotarX(Tupla3f punto, float angle){
    return {punto(X), cos(angle)*punto(Y)-sin(angle)*punto(Z), sin(angle)*punto(Y)+cos(angle)*punto(Z)};
}

Tupla3f Camara::rotarY(Tupla3f punto, float angle){
    return {cos(angle)*punto(X)+sin(angle)*punto(Z), punto(Y) , -sin(angle)*punto(X)+cos(angle)*punto(Z)};
}

Tupla3f Camara::rotarZ(Tupla3f punto, float angle){
    return {cos(angle)*punto(X)-sin(angle)*punto(Y), sin(angle)*punto(X)+cos(angle)*punto(Y), punto(Z)};
}

void Camara::rotarXExaminar (float angle) {
    Tupla3f p = (modo==0) ? (eye-at) : (at-eye);      // VPN
    float modulo = sqrt(p.lengthSq());
    
    p = rotarX(p,angle);
    p = p.normalized()*modulo;
    // up = rotarX(up,angle);

    if (modo==0) eye = at + p;
    else         at = eye + p;
    
}

void Camara::rotarYExaminar (float angle) {
    Tupla3f p = (modo==0) ? (eye-at) : (at-eye);      // VPN
    float modulo = sqrt(p.lengthSq());

    p = rotarY(p, angle);
    p = p.normalized()*modulo;
    up = rotarY(up,angle);

    if (modo==0) eye = at + p;
    else         at = eye + p;
}

void Camara::rotarZExaminar (float angle) {
    Tupla3f p = (modo==0) ? (eye-at) : (at-eye);      // VPN
    float modulo = sqrt(p.lengthSq());

    p = rotarZ(p, angle);
    p = p.normalized()*modulo;
    // up = rotarZ(up,angle);

    if (modo==0) eye = at + p;
    else         at = eye + p;
}

// solo puede tomar valor x o z cada vez que se llama, no los dos a la vez
// si se pasa x, se calcula el eje de referencia de la cámara u = up x n ,
// si se pasa z, se calcula el sentido opuesto del vector VPN (at-eye)
void Camara::mover ( float x, float z) {
    Tupla3f p = (x==0) ? at-eye : up.cross(eye-at); // si x==0, z!=0
    eye = eye + p*(x+z);
    at  = at + p*(x+z);
}
void Camara::girar ( int x, int y, float ratio ) {
    // eye sería el origen de coordenadas de la camara
    Tupla3f p;
    float longitud, a, b, win_x, win_y;

    win_x = width*10;
    win_y = height*10;

    a = y*M_PI/win_y;
    // multiplicamos por 2 para que desde la izqda. de la ventana a la derecha se haga una vuelta de 360º completa
    b = (x*2*M_PI)/win_x;
    p = (modo==0) ? (eye-at) : (at-eye);
    longitud = sqrt(p.lengthSq());
    rotarXExaminar(a*p(Z)/longitud);
    rotarZExaminar(-a*p(X)/longitud);
    if      (modo==1) rotarYExaminar(-b);
    else if (modo==0) rotarYExaminar(b);
    


}