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
    Tupla3f p;
    if (modo==0){
     p = rotarX(eye-at,angle);
     eye = at + p;
    }
    else {
        p = rotarX(at-eye,angle);
        at = eye + p;
    }
}

void Camara::rotarYExaminar (float angle) {
                             // nuevo VPN == eje_Z rotado en Y
    if (modo==0) eye = at + rotarY(eye-at,angle);
    else         at = eye + rotarY(at-eye, angle);
}

void Camara::rotarZExaminar (float angle) {
    Tupla3f p;      // VPN
    p = (modo==0) ? (eye-at) : (at-eye);
    p = rotarZ(p, angle);
    if (modo==0) eye = at + p;
    else         at = eye + p;
}

// método de cámara primera persona
void Camara::mover ( float x, float z) {
    eye(X) += x;
    eye(Z) += z;
}
void Camara::girar ( int x, int y, float ratio ) {
    // eye sería el origen de coordenadas de la camara
    Tupla3f n;
    Tupla3f u;
    Tupla3f v;

    alpha+=(float)(x*ratio);
    beta+=(float)(y*ratio);

    if(modo==0){
        eye(X) = dist*sin(alpha);
        eye(Y) = dist*cos(alpha)*sin(beta);
        eye(Z) = dist*cos(alpha)*cos(beta);

        n = eye - at; // eje z, VPN ó n de sistema de referencia de camara
        u = (up.cross(n)).normalized(); // eje x, "sentido a la derecha" de sistema de ref. camara
        v = (n.cross(u)).normalized();   
        
        up(Y) = v(Y);
        up(Z) = v(Z);
    }
    else if (modo==1){
        at(X) = dist*alpha;
        at(Y) = dist*beta;
        // at(Z) = dist*cos(alpha)*cos(beta);
    }

}