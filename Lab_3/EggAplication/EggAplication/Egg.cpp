#define _USE_MATH_DEFINES

#include <cmath>
#include "Egg.h"
#include "App.h"
//rysowanie punkt�w
void Egg::drawPoints()
{
	//rozpocz�cie rysowania punkt�w
	glBegin(GL_POINTS);
	//dla ka�dej pozycji w wektorze systarczy wyrysowa� punkt
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			this->points[i][j].setGlVertex();
		}
	}
	//koniec rysowania punktk�w
	glEnd();
}
//rysowanie lini
//zale�no�ci w rysowaniu linii i tr�jk�t�w s� bardzo podobne,
//j - ka�de punktu w poziomie sk�adaj� si� z dw�ch p�okr�g�w, dlatego, aby po��czy� ostatni punkt, nale�y go po��czy� z pierszym drugiej po��wki
//i - ka�dy pionowy p�okr�g idzie w g�r�, po�nie od g�ry w d�
void Egg::drawLines()
{
	//rozpocz�cie rysowania linii
	glBegin(GL_LINES);
	//dla ka�dego punktu
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//pion
			this->points[i][j].setGlVertex();
			this->points[(i + 1) % this->resolution][j].setGlVertex();
			
			//poziome ani uko�ne linie nigdy nie b�d� rysowane dla z��czonych punkt�w na dole
			if (i > 0) {
				//poziom
				//pomijanie rysowania wok� najni�szego punku i najwy�szego je�eli parzysta liczba punkt�w (bo 1 punkt)
				if (this->resolution % 2 == 1 || i != this->resolution / 2) {
					//je�eli ostatni punkt w p�okr�gu, trzeba po��czy� go z pierwszym drugiego p�okr�gu
					if (j + 1 == this->resolution) {
						this->points[i][j].setGlVertex();
						this->points[this->resolution - i][0].setGlVertex();
					}
					else {
						this->points[i][j].setGlVertex();
						this->points[i][j + 1].setGlVertex();
					}
				}
				//uko�ne
				//pomijanie rysowania wok� najni�szego punku i najwy�szego je�eli parzysta liczba punkt�w (bo punkty ��cz� si� w jeden)
				if (i + 1 != this->resolution && i != this->resolution / 2 && (this->resolution % 2 == 1 || i + 1 != this->resolution / 2)) {
					if (j + 1 == this->resolution) {
						// je�eli ostatni punkt w p�okr�gu, trzeba po��czy� go z pierwszym drugiego p�okr�gu
						this->points[i][j].setGlVertex();
						this->points[this->resolution - (i + 1) % this->resolution][0].setGlVertex();
					}
					else {
						this->points[i][j].setGlVertex();
						this->points[(i + 1) % this->resolution][j + 1].setGlVertex();
					}
				}
			}
		}
	}
	//koniec rysowania linii
	glEnd();
}
//rysowanie wype�nionych tr�jk�t�w
void Egg::drawTriangles()
{
	//rozpocz�cie rysowania tr�jk�t�w
	glBegin(GL_TRIANGLES);

	//dla ka�dej pozycji w wektorze
	for (size_t i = 1; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//po��wka g�na i przeciwleg�a dolna (pocz�tek tablicy)
			if (i == 1 || i==this->resolution/2+1) {
				this->points[i][j].setGlVertex();
				this->points[(i - 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - i][0].setGlVertex();
				else
					this->points[i][j + 1].setGlVertex();
			}
			//po��wka g�na i przeciwleg�a dolna (koniec tablicy)
			if (i + 1 == this->resolution || i == this->resolution / 2 - 1 + this->resolution%2) {
				this->points[i][j].setGlVertex();
				this->points[(i + 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - i][0].setGlVertex();
				else
					this->points[i][j + 1].setGlVertex();
			}
			//je�eli istniej� linie uko�ne (jak przy rysowaniu linii)
			if (i + 1 != this->resolution && i != this->resolution / 2 && (this->resolution % 2 == 1 || i + 1 != this->resolution / 2)) {
				//pierwszy z dw�ch tr�jk�t�w
				this->points[i][j].setGlVertex();
				this->points[(i + 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - (i + 1) % this->resolution][0].setGlVertex();
				else
					this->points[(i + 1) % this->resolution][j + 1].setGlVertex();

				//drugi z dw�ch tr�jk�t�w
				this->points[i][j].setGlVertex();
				if (j + 1 == this->resolution) {
					this->points[this->resolution - (i + 1) % this->resolution][0].setGlVertex();
					this->points[this->resolution - i][0].setGlVertex();
				}
				else {
					this->points[(i + 1) % this->resolution][j + 1].setGlVertex();
					this->points[i][j + 1].setGlVertex();
				}
			}
		}
	}

	glEnd();
}
//konstruktor (rozdzielczo�� (ilo�� punkt�w), pozycja vector3f, skala)
Egg::Egg(size_t resolution, Vector3<GLfloat> pos, Vector3<GLfloat> scale)
{
	this->resolution = resolution;
	//dla ka�dego wiersza
	for (size_t i = 0; i < resolution; i++) {
		//tworzenie kolumny
		this->points.push_back(std::vector<Point3f>());
		//dla ka�dej kolumny
		for (size_t j = 0; j < resolution; j++) {
			//wyznaczanie pozycji r�wnego ods�pu <0, 1>
			GLfloat u = static_cast<GLfloat>(i) / resolution;
			GLfloat v = static_cast<GLfloat>(j) / resolution;
			//wyliczanie pozycji punktu w przestrzeni 3d
			Point3f point = Point3f(
				(-90.f * std::pow(u, 5) + 225.f * std::pow(u, 4) - 270.f * std::pow(u, 3) + 180.f * std::pow(u, 2) - 45.f * u) * std::cosf(v * (GLfloat)M_PI),
				160.f * std::pow(u, 4) - 320.f * std::pow(u, 3) + 160.f * std::pow(u, 2),
				(-90.f * std::pow(u, 5) + 225.f * std::pow(u, 4) - 270.f * std::pow(u, 3) + 180.f * std::pow(u, 2) - 45.f * u) * std::sinf(v * (GLfloat)M_PI)
			);
			//dodanie przesuni�cia w pozycji
			point.cords += pos;
			//uwzgl�dnienie skali jajka
			point.cords *= scale;
			//dodanie punktu do wektora punkt�w
			this->points.back().push_back(point);
		}
	}
}
//ustalanie kolor�w
void Egg::setColor(ColorType colorType)
{
	//dla ka�dego punktu
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//3 typy kolor�
			switch (colorType)
			{
			case Egg::ColorType::Random:
				//ka�dy rodzaj koloru jest losowy
				this->points[i][j].setColor(
					App::randGLfloat(),
					App::randGLfloat(),
					App::randGLfloat()
				);
				break;
			case Egg::ColorType::Red:
				//losowane jest tylko czerwony kolor
				this->points[i][j].setColor(
					App::randGLfloat(),
					0.f,
					0.f
				);
				break;
			case Egg::ColorType::Green:
				//losowany jest tylko zielony kolor
				this->points[i][j].setColor(
					0.f,
					App::randGLfloat(),
					0.f
				);
				break;
			case Egg::ColorType::Blue:
				//losowany jest tylko niebieski kolor
				this->points[i][j].setColor(
					0.f,
					0.f,
					App::randGLfloat()
				);
				break;
			}
		}
	}
}

//rysowanie obiektu
void Egg::draw()
{
	//rysowanie wed�ug podanego typu rysowania w App
	switch (App::getInstance()->displayType)
	{
	case DrawType::Point:
		//chmura punkt�w
		this->drawPoints();
		break;
	case DrawType::Line:
		//linie
		this->drawLines();
		break;
	case DrawType::Triangle:
		//wype�nienie (tr�j�ky)
		this->drawTriangles();
		break;
	}
}
