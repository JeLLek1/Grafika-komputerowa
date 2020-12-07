  // Copyright 2020 JeLLek
#pragma once
#include "Light.h"
class MovingLight : public Light {
    // pozycja światła
    Vector3<GLfloat> center;
    // początkowa pozycja światła
    Vector3<GLfloat> initialCenter;

 public:
    // konstruktor
    // indeks światła, pozycja początkowa
    MovingLight(GLenum lightNumber, Vector3<GLfloat> center);
    // zmiana pozycji światła
    void changePos(GLfloat x, GLfloat y);
    // przywracanie ustawień początkowych światła
    void reset();
    // zmiana koloru światła
    void setColor(int color);
    // ustawienie pozycji i parametrów światła według danych obiektu
    void setLight();
};

