  // Copyright 2020 JeLLek
#define _USE_MATH_DEFINES

#include "CirculatingLight.h"
#include <cmath>
#include "App.h"
// konstruktor
// indeks światła, ilość stopni na seknudę, światło otoczenia,
// światło odbicia kierunkowego, światło odbicia dyfuzyjnego
CirculatingLight::CirculatingLight(GLenum lightNumber,
    GLfloat circlePerSec, Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
    Vector4<GLfloat> diffuse)
    : Light(lightNumber, Light::LigtType::DIRECTIONAL,
        Vector3<GLfloat>(0.f, 0.f, 0.f), ambien, diffuse, specular) {
    this->circlePerSec = circlePerSec;
}
// aktualizacja pozycji na bazie dt App
void CirculatingLight::update() {
    this->angleA
        += this->circlePerSec * App::getInstance()->dt * this->circlePerSec;

    if (this->angleA > 360.f)
        this->angleA -= 360.f * static_cast<int>(this->angleA / 360);
}
// ustawienie pozycji i parametrów światła według danych obiektu
void CirculatingLight::setLight() {
    // kąt w radianach
    GLfloat aPI = this->angleA * (M_PI / 180);
    GLfloat bPI = this->angleB * (M_PI / 180);
    // ustawienie pozycji światła
    Light::setPosition(Vector3<GLfloat>(
        std::cosf(aPI) * std::cosf(bPI),
        std::sinf(bPI),
        std::sinf(aPI) * std::cosf(bPI)));

    // wywołanie metody ustawiającej pozycję i parametry światła
    Light::setLight();
}
