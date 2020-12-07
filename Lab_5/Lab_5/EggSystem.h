  // Copyright 2020 JeLLek
#pragma once
#include "Egg.h"
#include <Windows.h>
#include <gl/GL.h>
#include <list>

// System składający się z podsystemów i centralnego jajka
class EggSystem {
 private:
    // lista podsystemów
    std::list<EggSystem*> systems;
    // jajko centralne systemu
    Egg* center;

 public:
    // promień obrotu systemu
    GLfloat radius;
    // ilość stopni wykonywanych przejść po orbicie na sekundę
    GLfloat circlePerSec;
    // obecna ilośc stopni obrotu po orbicie
    GLfloat curentCircleAngle;
    // obecna ilość stopni obrotu w okół własnej osi
    GLfloat currentRotateAngle;
    // ilość stopni obrotów na sekundę w okół własnej osi
    GLfloat rotatePerSec;
    // konstruktor (jajko centralne, promień obrotu, ilość stopni w okół
    // własnej osi, ilośc stopni obtoru po orbicie na sekundę,
    // ilość stopni początkowej pozycji orbity)
    EggSystem(Egg* center, GLfloat radius = 0.f, GLfloat rotatePerSec = 0.f,
        GLfloat circlePerSec = 0.f, GLfloat initialCircle = 0.f);
    // Wyrysowanie systemu
    void draw();
    // aktualizacja pozycji w systemie
    void update();
    // dodanie podsystemu
    void push(EggSystem* system);
    // destruktor
    ~EggSystem();
};

