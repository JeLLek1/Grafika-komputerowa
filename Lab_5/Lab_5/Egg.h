  // Copyright 2020 JeLLek
#pragma once
#include <vector>
#include "Vector3.h"
#include "Point3f.h"
#include "Material.h"
#include "Texture.h"

// jajko
class Egg {
 private:
    // wektor przechowujący wszystkie punkty jajka
    std::vector<std::vector<Point3f>> points;
    // rozdzielczość (ilość punktów)
    size_t resolution;
    // Materiał z którego wykonane jest jajko
    Material* material;
    // Tekstura
    Texture* texture;
    // typ rysowania chmury punktów
    void drawPoints();
    // typ rysowania linii
    void drawLines();
    // typ rysowania wypełnionych trójkątów
    void drawTriangles();
    // rysowanie pojedyńczego trójkąta
    void drawSingleTriangle(size_t x0, size_t y0,
        size_t x1, size_t y1, size_t x2, size_t y2,
        bool typeTriangle, bool half, unsigned no);

 public:
    // konstruktor (rozdzielczość, materiał, pozycja w przestrzeni 3d, skala)
    Egg(size_t resolution, Material* material,
        Texture* texture,
        Vector3<GLfloat> pos = Vector3<GLfloat>(),
        Vector3<GLfloat> scale = Vector3<GLfloat>(1.f, 1.f, 1.f));
    // rysowanie
    void draw();
    // odświerzanie
    void update();
    // destruktor
    ~Egg();
};
