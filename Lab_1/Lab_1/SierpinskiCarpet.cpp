#include "SierpinskiCarpet.h"
#include "globFunc.h"

void SierpinskiCarpet::zoom(GLfloat step)
{
    //wywo³ywanie metody zoom dla kolejnych kwadratów
    std::list <Square*> ::iterator it;
    for (it = this->squares->begin(); it != this->squares->end(); ++it)
        (*it)->zoom(step);
}

void SierpinskiCarpet::moov(GLfloat x, GLfloat y)
{
    //wywo³ywanie metody moov dla kolejnych kwadratów
    std::list <Square*> ::iterator it;
    for (it = this->squares->begin(); it != this->squares->end(); ++it)
        (*it)->moov(x, y);
}

SierpinskiCarpet::SierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise)
{
    //inicjalizacja listy kwadratów
	this->squares = new std::list<Square*>();
    //generowanie rekurencjyjnie kolejnych poziomów
	this->generateSierpinskiCarpet(x, y, size, depth, noise);
}

void SierpinskiCarpet::generateSierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise)
{
	//nowa wielkoœæ kwadratu
	GLfloat sizeNew = size / 3.f;
    //dla 3 pozycji poziomo
    for (size_t horizontal = 0; horizontal < 3; horizontal++) {
        //dla 3 pozycji pionowo
        for (size_t vertical = 0; vertical < 3; vertical++) {
            //je¿eli œrodek to pomija rysowanie
            if (horizontal == 1 && vertical == 1) continue;

            //wyznaczanie pozycji lewego górnego wierzcho³ku na podstawie danych o pozycji rysowania i d³ugoœci
            GLfloat xNew = x + sizeNew * horizontal;
            GLfloat yNew = y + sizeNew * vertical;

            if (depth > 1) {
                //je¿eli nie jest to ostatni poziom wchodzi w rekurencje z danymi o pozycji i zmniejszonej wielkoœci
                this->generateSierpinskiCarpet(xNew,yNew, sizeNew, depth - 1, noise);
            }else{
                //Wyznaczanie pozycji 4 wierzcho³ków wed³ug wielkoœci i perturbacji
                this->squares->push_back(new Square(
                    new Point(xNew + randGLfloat(true) * noise, yNew + randGLfloat(true) * noise),
                    new Point(xNew + sizeNew + randGLfloat(true) * noise, yNew + randGLfloat(true) * noise),
                    new Point(xNew + sizeNew + randGLfloat(true) * noise, yNew + sizeNew + randGLfloat(true) * noise),
                    new Point(xNew + randGLfloat(true) * noise, yNew + sizeNew + randGLfloat(true) * noise)
                ));
            }
        }
    }
}

SierpinskiCarpet::~SierpinskiCarpet()
{
    //kolejne zwalnianie pamiêci kwadratów
    std::list <Square*> ::iterator it;
    for (it = this->squares->begin(); it != this->squares->end(); ++it)
        delete (*it);

    //zwalnianie pamiêci listy
    delete this->squares;
}
