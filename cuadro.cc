#include "cuadro.h"

Cuadro::Cuadro(float l)
{
    t = new Textura("./p5/sample.jpg");

    v.resize(4);
    float arista = l/2;

    v[0] = {-arista,0,0}; // P0
    v[1] = { arista,0,0}; // P1
    v[2] = {-arista,l,0}; // P2
    v[3] = { arista,l,0}; // P3

    f.push_back({2,0,1});
    f.push_back({1,3,2});

    // coord. textura manual
    ct.resize(4);
    ct[0] = {0,0};
    ct[1] = {1,0};
    ct[2] = {0,1};
    ct[3] = {1,1};

    genColor(1,0,1);

}

Cuadro::~Cuadro(){
    if(t!=nullptr)
        delete t;
    t = nullptr;
}