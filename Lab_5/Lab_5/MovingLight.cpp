  // Copyright 2020 JeLLek
#include "MovingLight.h"

// konstruktor
// indeks światła, pozycja początkowa
MovingLight::MovingLight(GLenum lightNumber, Vector3<GLfloat> center)
    : Light(lightNumber, Light::LigtType::POINT, center) {
    this->center = this->initialCenter = center;
    // kolor początkowy
    this->setColor(0);
}

// zmiana pozycji światła
void MovingLight::changePos(GLfloat x, GLfloat y) {
    // zmiana pozycji obserwatora
    center += Vector3<GLfloat>(x, -y, 0.0);
}
// przywracanie ustawień początkowych światła
void MovingLight::reset() {
    this->center = this->initialCenter;
    this->setColor(0);
}
// zmiana koloru światła (
//  0 - czerwony
//  1 - zielony
//  2 - niebieski
// )
void MovingLight::setColor(int color) {
    switch (color) {
        // zielony
    case 1:
        Light::changeParams(Vector4<GLfloat>(0.f, 0.1f, 0.f, 1.f),
            Vector4<GLfloat>(0.f, 1.f, 0.f, 1.f),
            Vector4<GLfloat>(0.f, 1.f, 0.f, 1.f));
        break;
        // niebieski
    case 2:
        Light::changeParams(Vector4<GLfloat>(0.f, 0.f, 0.1f, 1.f),
            Vector4<GLfloat>(0.f, 0.f, 1.f, 1.f),
            Vector4<GLfloat>(0.f, 0.f, 1.f, 1.f));
        break;
        // czerwony
    default:
        Light::changeParams(Vector4<GLfloat>(0.1f, 0.f, 0.f, 1.f),
            Vector4<GLfloat>(1.f, 0.f, 0.f, 1.f),
            Vector4<GLfloat>(1.f, 0.f, 0.f, 1.f));
        break;
    }
}
// ustawienie pozycji i parametrów światła według danych obiektu
void MovingLight::setLight() {
    Light::setPosition(this->center);
    Light::setLight();
}
