  // Copyright 2020 JeLLek
#include "Point3f.h"
// konstruktor pozycje x,y,z punktu
Point3f::Point3f(GLfloat x, GLfloat y, GLfloat z) {
    this->cords = Vector3<GLfloat>(x, y, z);
}

// ustawienie koloru i pozycji punktu do wyrysowania
void Point3f::setGlVertex() {
    glNormal3fv(this->normalVector.cords);
    glVertex3fv(this->cords.cords);
}
