  // Copyright 2020 JeLLek

#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <string>

class Texture {
    // szerokość tekstury
    GLint imWidth;
    // wysokość tekstury
    GLint imHeight;
    // ilość skłądowych koloru
    GLint imComponents;
    // format tekstury
    GLenum imFormat;

    // id tekstury
    GLuint textureID;

    // dane na temat elementów tekstury
    unsigned trianglesCount;  // ilość kolorów
    unsigned framesCount;  // ilość stanów animacji
    unsigned currentState;  // obecny stan animacji
    GLfloat frameTime;  // czas trwania jednej klatki
    GLfloat currentTime;  // czas trwania obecnej klatki


    // wczytanie tekstury z pliku
    void load(std::string fileName);

 public:
    Texture(std::string fileName, unsigned trianglesCount,
        unsigned framesCount, GLfloat frameTime);
    // aktualizacja animacji tekstury
    void update();
    // ustawienie wierzchołka tekstury
    void setTexture(size_t index, unsigned int edge, bool type);
    // ustawienie aktywnej tekstury
    void bindTexture();

    ~Texture();
};
