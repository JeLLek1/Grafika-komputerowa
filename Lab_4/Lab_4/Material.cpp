  // Copyright 2020 JeLLek
#include "Material.h"

// konstruktor
// ambient, specular, diffuse, shiness
Material::Material(Vector4<GLfloat> ambient, Vector4<GLfloat> specular,
    Vector4<GLfloat> diffuse, GLfloat shiness) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shiness = shiness;
}

// użycie opisanego opisu materiału
void Material::setMaterial() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient.cords);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular.cords);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse.cords);
    glMaterialf(GL_FRONT, GL_SHININESS, this->shiness);
}
