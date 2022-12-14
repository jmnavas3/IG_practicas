#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "auxiliar.h"
#include "jpg_imagen.hpp"

class Textura
{
    GLuint textura_id = 0;              // identificador de textura de OpenGL
    std::vector<unsigned char> data;    // datos de la textura
    int width, height;                  // ancho y alto

    jpg::Imagen * pimg = nullptr;       // puntero a los pixels en memoria dinamica
    unsigned char * texels=nullptr;
    bool nuevo = true;

    public:
    
    Textura(std::string archivo);
    ~Textura();
    void activar();
};

#endif