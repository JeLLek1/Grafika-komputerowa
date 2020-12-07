  // Copyright 2020 JeLLek
#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "Vector3.h"
// punkt ułatwiający operacjie na punktach openGl
class Point3f {
 public:
    // pozycjia punktu
    Vector3<GLfloat> cords;
    // wektor normalny
    Vector3<GLfloat> normalVector;

    // konstruktor
    explicit Point3f(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

    // Ustawienie punktu dla elementów rysowania openGL
    void setGlVertex();
};

