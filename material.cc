#include "material.h"

//** Para este archivo se ha usado la herramienta: Doxygen Documentation Generator

/**
 * @brief Constructor por defecto
 * 
 */
Material::Material() {
    difuso = amb_dif_defecto;
    especular = esp_defecto;
    ambiente = amb_dif_defecto;
    brillo = brillo_defecto;
}

/**
 * @brief Constructor de copia
 * 
 * @param m 
 */
Material::Material (const Material &m) {
    *this = m;
}

/**
 * @brief Sobrecarga del operador de asignación
 * 
 * @param m 
 * @return Material& 
 */
Material &Material::operator =(const Material &m){
    difuso = m.difuso;
    especular = m.especular;
    ambiente = m.ambiente;
    brillo = m.brillo;

    return *this;
}

/**
 * @brief Constructor del diagrama de clases de la P3
 * 
 * @param mdifuso RGBA
 * @param mespecular RGBA
 * @param mambiente RGBA
 * @param brillo valor real entre 0 y 128
 */
Material::Material ( Tupla4f mdifuso,
                   Tupla4f mespecular,
                   Tupla4f mambiente,
                   float brillo )
{
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;

    if (brillo <= 128.0f && brillo >= 0.0f) this->brillo = brillo;
}

/**
 * @brief Aplica la reflectividad y brillo de un material
 * @cite Malla3D::draw
 * 
 */
void Material::aplicar () {

    glMaterialfv(GL_FRONT,GL_SPECULAR,especular);
    // glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb_dif_defecto);
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,difuso);


    glMaterialf(GL_FRONT,GL_SHININESS,brillo);
}