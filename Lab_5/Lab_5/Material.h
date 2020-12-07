  // Copyright 2020 JeLLek
#pragma once
#include "Material.h"
#include <Windows.h>
#include <gl/GL.h>
#include "Vector4.h"

// definiowanie materiału elementu
class Material {
    Vector4<GLfloat> ambient;  // współczynniki światła otoczenia
    Vector4<GLfloat> specular;  // współczynniki światła odbitego
    Vector4<GLfloat> diffuse;  // współczynniki światła rozproszonego
    GLfloat shiness;  // współczynnik połysku powierzchni

 public:
    // konstruktor
    // ambient, specular, diffuse, shiness
    Material(Vector4<GLfloat> ambient, Vector4<GLfloat> sepcular,
        Vector4<GLfloat> diffuse, GLfloat shiness);
    // użycie opisanego opisu materiału
    void setMaterial();
};

