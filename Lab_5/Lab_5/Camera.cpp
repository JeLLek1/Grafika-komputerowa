  // Copyright 2020 JeLLek

#include "Camera.h"
#include <gl/GL.h>
#include <gl/glut.h>
#include "Settings.h"

// konstruktor
Camera::Camera() {
    this->reset();
}
// obsługa gluLookAt z odpowiednimi przypisaniami
void Camera::setView() {
    gluLookAt(eye.cords[0], eye.cords[1], eye.cords[2],
        center.cords[0], center.cords[1], center.cords[2], 0.0, 1.0, 0.0);
}

// przywracanie ustawień początkowych kamery
void Camera::reset() {
    // przywracanie ustawienia początkowego obserwatora
    eye = Vector3<GLdouble>(EYE_X, EYE_Y, EYE_Z);
    // przywracanie ustawienia początkowego punktu obserwowanego
    center = Vector3<GLdouble>(CENTER_X, CENTER_Y, CENTER_Z);
}
// obsługa zmiany odległości do punktu obserwowanego
void Camera::zoom(GLdouble distance) {
    // znormalizowany wektor od środka do obserwatora
    Vector3<GLdouble> vector = this->eye - this->center;
    vector.normalize();

    // obliczenie pozycji obserwatora po zmianie dystansu
    Vector3<GLdouble> eyeChanged = this->eye + vector * distance;

    // znormalizowany wektor od środka do obserwatora po zmianie dystansu
    Vector3<GLdouble> newEyeVector = eyeChanged - this->center;
    newEyeVector.normalize();

    // test, czy nie zmienił się wektor (aby uniknąć sytuacji
    // "wyjechania" poza jajko podczas przybliżania)
    if (vector.distance(newEyeVector) < EPSILON) {
        // operator przypisania jest przeciążony
        // i powoduje przypisanie kolejnych koordynatów
        this->eye = eyeChanged;
    }
}
