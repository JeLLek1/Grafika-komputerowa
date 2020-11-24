  // Copyright 2020 JeLLek
#pragma once
#include "Light.h"
class CirculatingLight : public Light {
    GLfloat angleA = 0;  // kont azymutu
    GLfloat angleB = 0;  // kont elewacji

    GLfloat circlePerSec;  // ilość stopni na sekundę animacji

 public:
    // konstruktor
    // indeks światła, ilość stopni na seknudę, światło otoczenia,
    // światło odbicia kierunkowego, światło odbicia dyfuzyjnego
    CirculatingLight(GLenum lightNumber, GLfloat circlePerSec,
        Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
        Vector4<GLfloat> diffuse);
    // aktualizacja pozycji na bazie dt App
    void update();
    // ustawienie pozycji i parametrów światła według danych obiektu
    void setLight();
};

