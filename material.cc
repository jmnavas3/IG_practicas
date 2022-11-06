#include "material.h"

Material::Material() {
    difuso = amb_dif_defecto;
    especular = esp_defecto;
    ambiente = amb_dif_defecto;
    brillo = brillo_defecto;
}

Material::Material ( Tupla4f mdifuso,
                   Tupla4f mespecular=esp_defecto,
                   Tupla4f mambiente=amb_dif_defecto,
                   float brillo=brillo_defecto )
{
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;

    if (brillo <= 128.0f && brillo >= 0.0f) this->brillo = brillo;
}

// -----------------------------------------------------------------------------
// Aplica la reflectividad y brillo de un material a una malla, llamada desde Malla3D:Draw 
void Material::aplicar () {

    glMaterialfv(GL_FRONT,GL_SPECULAR,ambiente);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb_dif_defecto);
    // glMaterialfv(GL_FRONT,GL_AMBIENT,difuso);
    // glMaterialfv(GL_FRONT,GL_DIFFUSE,especular);


    glMaterialf(GL_FRONT,GL_SHININESS,brillo);
}