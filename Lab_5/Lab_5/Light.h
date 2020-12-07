  // Copyright 2020 JeLLek
#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Vector3.h"
#include "Vector4.h"

class Light {
 public:
    enum class LigtType {
        POINT,
        DIRECTIONAL
    };

 private:
    GLenum lightNumber;  // indeks światła
    LigtType lightType;  // typ światła punktowe/kierynkowe
    Vector3<GLfloat> position;  // pozycja światła
    Vector4<GLfloat> ambien;  // składowe światła otoczenia
    Vector4<GLfloat> specular;  // składowa światła odbicia kierunkowego
    Vector4<GLfloat> diffuse;  // składowa światła odbicia dyfuzyjnego

    // parametry światła punktowego zmiany odległości
    static GLfloat att_constant;
    static GLfloat att_linear;
    static GLfloat att_quadratic;

 public:
    // konstruktor
    // indeks światłą, typ światła, pozycja/wektor, światło otoczenia,
    // odbicie kierunkowe, odbicie dyfuzyjne
    Light(GLenum lightNumber, LigtType lightType, Vector3<GLfloat> position,
        Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
        Vector4<GLfloat> diffuse);
    // konstruktur
    // indeks światłą, typ światła, pozycja/wektor
    Light(GLenum lightNumber, LigtType lightType, Vector3<GLfloat> position);
    // zmiana wetkora/pozycji światła
    void setPosition(Vector3<GLfloat> position);
    // zmiana ustawień parametrów
    // ambien, specular, diffuse
    void changeParams(Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
        Vector4<GLfloat> diffuse);
    // ustawienie parametrów światła
    void setLight();
};

