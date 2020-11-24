  // Copyright 2020 JeLLek
#define _USE_MATH_DEFINES

#include <cmath>
#include "Egg.h"
#include "App.h"
// rysowanie punktów
void Egg::drawPoints() {
    // rozpoczęcie rysowania punktów
    glBegin(GL_POINTS);
    // dla każdej pozycji w wektorze systarczy wyrysować punkt
    for (size_t i = 0; i < this->resolution; i++) {
        for (size_t j = 0; j < this->resolution; j++) {
            this->points[i][j].setGlVertex();
        }
    }
    // koniec rysowania punktków
    glEnd();
}
// rysowanie lini
// zależności w rysowaniu linii i trójkątów są bardzo podobne,
// j - każde punktu w poziomie składają się z dwóch półokręgów, dlatego,
// aby połączyć ostatni punkt, należy go połączyć z pierszym drugiej połówki
// i - każdy pionowy półokrąg idzie w górę, pożnie od góry w dół
void Egg::drawLines() {
    // rozpoczęcie rysowania linii
    glBegin(GL_LINES);
    // dla każdego punktu
    for (size_t i = 0; i < this->resolution; i++) {
        for (size_t j = 0; j < this->resolution; j++) {
            // pion
            this->points[i][j].setGlVertex();
            this->points[(i + 1) % this->resolution][j].setGlVertex();

            // poziome ani ukośne linie nigdy nie będą
            // rysowane dla złączonych punktów na dole
            if (i > 0) {
                // poziom
                // pomijanie rysowania wokół najniższego punku i najwyższego
                // jeżeli parzysta liczba punktów (bo 1 punkt)
                if (this->resolution % 2 == 1 || i != this->resolution / 2) {
                    // jeżeli ostatni punkt w półokręgu, trzeba połączyć go z
                    // pierwszym drugiego półokręgu
                    if (j + 1 == this->resolution) {
                        this->points[i][j].setGlVertex();
                        this->points[this->resolution - i][0].setGlVertex();
                    } else {
                        this->points[i][j].setGlVertex();
                        this->points[i][j + 1].setGlVertex();
                    }
                }
                // ukośne
                // pomijanie rysowania wokół najniższego punku i najwyższego
                // jeżeli parzysta liczba punktów (bo punkty łączą się w jeden)
                if (i + 1 != this->resolution && i != this->resolution / 2
                    && (this->resolution % 2 == 1
                        || i + 1 != this->resolution / 2)) {
                    if (j + 1 == this->resolution) {
                        // jeżeli ostatni punkt w półokręgu, trzeba połączyć go
                        // z pierwszym drugiego półokręgu
                        this->points[i][j].setGlVertex();
                        this->points[this->resolution
                            - (i + 1) % this->resolution][0].setGlVertex();
                    } else {
                        this->points[i][j].setGlVertex();
                        this->points[(i + 1) % this->resolution][j + 1]
                            .setGlVertex();
                    }
                }
            }
        }
    }
    // koniec rysowania linii
    glEnd();
}
// rysowanie wypełnionych trójkątów
void Egg::drawTriangles() {
    // rozpoczęcie rysowania trójkątów
    glBegin(GL_TRIANGLES);

    // dla każdej pozycji w wektorze
    for (size_t i = 1; i < this->resolution; i++) {
        for (size_t j = 0; j < this->resolution; j++) {
            // połówka góna i przeciwległa dolna (początek tablicy)
            if (i == 1 || i == this->resolution / 2 + 1) {
                this->points[i][j].setGlVertex();
                this->points[(i - 1) % this->resolution][j].setGlVertex();
                if (j + 1 == this->resolution)
                    this->points[this->resolution - i][0].setGlVertex();
                else
                    this->points[i][j + 1].setGlVertex();
            }
            // połówka góna i przeciwległa dolna (koniec tablicy)
            if (i + 1 == this->resolution
                || i == this->resolution / 2 - 1 + this->resolution % 2) {
                this->points[i][j].setGlVertex();
                this->points[(i + 1) % this->resolution][j].setGlVertex();
                if (j + 1 == this->resolution)
                    this->points[this->resolution - i][0].setGlVertex();
                else
                    this->points[i][j + 1].setGlVertex();
            }
            // jeżeli istnieją linie ukośne (jak przy rysowaniu linii)
            if (i + 1 != this->resolution && i != this->resolution / 2
                && (this->resolution % 2 == 1
                    || i + 1 != this->resolution / 2)) {
                // pierwszy z dwóch trójkątów
                this->points[i][j].setGlVertex();
                this->points[(i + 1) % this->resolution][j].setGlVertex();
                if (j + 1 == this->resolution)
                    this->points[
                        this->resolution - (i + 1) % this->resolution
                    ][0].setGlVertex();
                else
                    this->points[
                        (i + 1) % this->resolution
                    ][j + 1].setGlVertex();

                        // drugi z dwóch trójkątów
                        this->points[i][j].setGlVertex();
                        if (j + 1 == this->resolution) {
                            this->points[
                                this->resolution - (i + 1) % this->resolution
                            ][0].setGlVertex();
                            this->points[
                                this->resolution - i
                            ][0].setGlVertex();
                        } else {
                            this->points[
                                (i + 1) % this->resolution
                            ][j + 1].setGlVertex();
                                this->points[i][j + 1].setGlVertex();
                        }
            }
        }
    }

    glEnd();
}
// konstruktor (rozdzielczość (ilość punktów), pozycja vector3f, skala)
Egg::Egg(size_t resolution, Material* material, Vector3<GLfloat> pos,
    Vector3<GLfloat> scale) {
    this->resolution = resolution;
    this->material = material;
    // dla każdego wiersza
    for (size_t i = 0; i < resolution; i++) {
        // tworzenie kolumny
        this->points.push_back(std::vector<Point3f>());
        // dla każdej kolumny
        for (size_t j = 0; j < resolution; j++) {
            // wyznaczanie pozycji równego odsępu <0, 1>
            GLfloat u = static_cast<GLfloat>(i) / resolution;
            GLfloat v = static_cast<GLfloat>(j) / resolution;
            // wyliczanie pozycji punktu w przestrzeni 3d
            Point3f point = Point3f(
                (-90.f * std::powf(u, 5) + 225.f * std::powf(u, 4)
                    - 270.f * std::powf(u, 3) + 180.f * std::powf(u, 2)
                    - 45.f * u) * std::cosf(v * (GLfloat)M_PI),
                160.f * std::powf(u, 4) - 320.f * std::powf(u, 3)
                + 160.f * std::powf(u, 2),
                (-90.f * std::powf(u, 5) + 225.f * std::powf(u, 4)
                    - 270.f * std::powf(u, 3) + 180.f * std::powf(u, 2)
                    - 45.f * u) * std::sinf(v * (GLfloat)M_PI));
            // obliczanie wektora normalnego
            GLfloat xu = (-450.f * std::powf(u, 4) + 900.f * std::powf(u, 3)
                - 810.f * std::powf(u, 2) + 360.f * u - 45.f)
                * std::cosf(v * (GLfloat)M_PI);
            GLfloat xv = (GLfloat)M_PI * (90.f * std::powf(u, 5)
                - 225.f * std::powf(u, 4) + 270.f * std::powf(u, 3)
                - 180.f * std::powf(u, 2) + 45.f * u)
                * std::sinf(v * (GLfloat)M_PI);
            GLfloat yu = 640.f * std::powf(u, 3) - 960.f
                * std::powf(u, 2) + 320.f * u;
            GLfloat yv = 0.f;
            GLfloat zu = (-450.f * std::powf(u, 4) + 900.f * std::powf(u, 3)
                - 810.f * std::powf(u, 2) + 360.f * u - 45.f)
                * std::sinf(v * (GLfloat)M_PI);
            GLfloat zv = -(GLfloat)M_PI * (90.f * std::powf(u, 5)
                - 225.f * std::powf(u, 4) + 270.f * std::powf(u, 3)
                - 180.f * std::powf(u, 2) + 45.f * u)
                * std::cosf(v * (GLfloat)M_PI);

            Vector3<GLfloat> normalizedVector((yu * zv) - (zu * yv),
                (zu * xv) - (xu * zv), (xu * yv) - (yu * xv));
            // druga połowa jajka ma przeciwny wektor
            if (i >= resolution / 2) {
                normalizedVector *= (GLfloat)-1;
            }
            // wektor jest zerowy (góra / dół jajka)
            if (normalizedVector == Vector3<GLfloat>(0, 0, 0)) {
                // góra
                if (i == 0) {
                    normalizedVector.cords[1] = -1.f;
                    // dół
                } else {
                    normalizedVector.cords[1] = 1.f;
                }
            }

            normalizedVector.normalize();
            point.normalVector = normalizedVector;

            // dodanie przesunięcia w pozycji
            point.cords += pos;
            // uwzględnienie skali jajka
            point.cords *= scale;
            // dodanie punktu do wektora punktów
            this->points.back().push_back(point);
        }
    }
}

// rysowanie obiektu
void Egg::draw() {
    // ustawienie materiału z którego jest wykonany obiekt
    this->material->setMaterial();

    // rysowanie według podanego typu rysowania w App
    switch (App::getInstance()->displayType) {
    case DrawType::Point:
        // chmura punktów
        this->drawPoints();
        break;
    case DrawType::Line:
        // linie
        this->drawLines();
        break;
    case DrawType::Triangle:
        // wypełnienie (trójąky)
        this->drawTriangles();
        break;
    }
}

// destruktor
Egg::~Egg() {
    delete this->material;
}
