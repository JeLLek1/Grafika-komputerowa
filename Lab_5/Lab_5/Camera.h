  // Copyright 2020 JeLLek
#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Vector3.h"

// obsługa obserwatora
class Camera {
 private:
    // pozycja obserwatora
    Vector3<GLdouble> eye;
    // pozycja punktu obserwowanego
    Vector3<GLdouble> center;

 public:
    // konstruktor
    Camera();
    // obsługa gluLookAt z odpowiednimi przypisaniami
    void setView();
    // przywracanie ustawień początkowych kamery
    void reset();
    // obsługa zmiany odległości do punktu obserwowanego
    void zoom(GLdouble distance);
};

