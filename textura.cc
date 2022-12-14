#include "textura.h"


/**
 * @brief Constructor de Textura que estará asociada a una malla
 * 
 * @param archivo ubicacion del archivo jpeg
 */
Textura::Textura(std::string archivo) {

    // obtenemos atributos de la imagen
    pimg   = new jpg::Imagen(archivo);
    width  = pimg->tamX(); // columnas j
    height = pimg->tamY(); // filas    i

    for(int i = height-1; i >= 0; i--){     // recorre filas de la imagen de ultima a primera
        for(int j = 0; j < width; j++)      // recorre columnas de la imagen de primera a ultima
        {
            texels = pimg->leerPixel(j,i);  // devuelve puntero a w*j_fila + i_columna
            data.push_back(*texels);
            data.push_back(*(texels+1));
            data.push_back(*(texels+2));
        }
    }

}

/**
 * @brief Activa las texturas en función de si la iluminación está activada o no
 * !luz, sustituye a glColor
 * luz, sustituye a material difuso y ambiental
 * Ejecutar dentro del contexto de OpenGL
 * 
 */
void Textura::activar() {
    
    glEnable( GL_TEXTURE_2D );
    
    if(nuevo){
        // generamos el identificador de textura
        glGenTextures(1, &textura_id);
        // transferimos los texels a la gpu
        glBindTexture(GL_TEXTURE_2D,textura_id);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
        glBindTexture(GL_TEXTURE_2D,0);
        nuevo = false;
    }else{
        glBindTexture( GL_TEXTURE_2D, textura_id ); // activa el id de textura del objeto que llama a la funcion
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

}


/**
 * @brief Destructor del puntero de imagen
 * 
 */
Textura::~Textura() {
    if(pimg != nullptr) delete pimg;
    if(texels!=nullptr) delete texels;
    pimg = nullptr;
    texels = nullptr;
}