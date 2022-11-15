#include "material.h"

/**
 * @brief Constructor por defecto
 * 
 */
Material::Material() {
    difuso    = {0.1, 0.5, 0.8, 1.0};
    especular = {1.0, 0.5, 0.7, 1.0};
    ambiente  = {0.0, 0.0, 0.2, 1.0};
    brillo    = 35;
}

/**
 * @brief Constructor de copia
 * 
 * @param m material existente
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
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,difuso);
    // glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb_dif_defecto);

    glMaterialf(GL_FRONT,GL_SHININESS,brillo);
}