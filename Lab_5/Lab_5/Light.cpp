  // Copyright 2020 JeLLek

#include "Light.h"

GLfloat Light::att_constant = 1.f;  // stała odległości
GLfloat Light::att_linear = 0.001f;  // parametr liniowy odległości
GLfloat Light::att_quadratic = 0.001f;  // parametr kwadratowy odległości

// konstruktor
// indeks światłą, typ światła, pozycja/wektor,
// światło otoczenia, odbicie kierunkowe, odbicie dyfuzyjne
Light::Light(GLenum lightNumber, LigtType lightType, Vector3<GLfloat> position,
    Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
    Vector4<GLfloat> diffuse) {

    this->lightNumber = lightNumber;
    this->lightType = lightType;
    this->setPosition(position);
    this->changeParams(ambien, diffuse, specular);
    glEnable(GL_LIGHT0 + this->lightNumber);
}

// konstruktor
// indeks światłą, typ światła, pozycja/wektor
Light::Light(GLenum lightNumber, LigtType lightType,
    Vector3<GLfloat> position) {

    this->lightNumber = lightNumber;
    this->lightType = lightType;
    this->setPosition(position);
    glEnable(GL_LIGHT0 + this->lightNumber);
}

// zmiana wetkora/pozycji światła
void Light::setPosition(Vector3<GLfloat> position) {
    this->position = position;
}
// zmiana ustawień parametrów
// ambien, specular, diffuse
void Light::changeParams(Vector4<GLfloat> ambien, Vector4<GLfloat> specular,
    Vector4<GLfloat> diffuse) {

    this->ambien = ambien;
    this->specular = specular;
    this->diffuse = diffuse;
}

// ustawienie parametrów światła
void Light::setLight() {
    glLightfv(GL_LIGHT0 + this->lightNumber, GL_AMBIENT, this->ambien.cords);
    glLightfv(GL_LIGHT0 + this->lightNumber, GL_SPECULAR, this->specular.cords);
    glLightfv(GL_LIGHT0 + this->lightNumber, GL_DIFFUSE, this->diffuse.cords);

    // definiowanie położenia i zmiany jasności światła punktowego
    if (this->lightType == Light::LigtType::POINT) {
        glLightf(GL_LIGHT0 + this->lightNumber,
            GL_CONSTANT_ATTENUATION, Light::att_constant);
        glLightf(GL_LIGHT0 + this->lightNumber,
            GL_LINEAR_ATTENUATION, Light::att_linear);
        glLightf(GL_LIGHT0 + this->lightNumber,
            GL_QUADRATIC_ATTENUATION, Light::att_quadratic);

        glLightfv(GL_LIGHT0 + this->lightNumber,
            GL_POSITION, Vector4<GLfloat>(this->position, 1.f).cords);
        // definiowanie wektora światła kierunkowego
    } else {
        glLightfv(GL_LIGHT0 + this->lightNumber, GL_POSITION,
            Vector4<GLfloat>(this->position, 0.f).cords);
    }
}
