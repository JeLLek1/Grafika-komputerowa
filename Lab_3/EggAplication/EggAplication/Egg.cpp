#define _USE_MATH_DEFINES

#include <cmath>
#include "Egg.h"
#include "App.h"
//rysowanie punktów
void Egg::drawPoints()
{
	//rozpoczêcie rysowania punktów
	glBegin(GL_POINTS);
	//dla ka¿dej pozycji w wektorze systarczy wyrysowaæ punkt
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			this->points[i][j].setGlVertex();
		}
	}
	//koniec rysowania punktków
	glEnd();
}
//rysowanie lini
//zale¿noœci w rysowaniu linii i trójk¹tów s¹ bardzo podobne,
//j - ka¿de punktu w poziomie sk³adaj¹ siê z dwóch pó³okrêgów, dlatego, aby po³¹czyæ ostatni punkt, nale¿y go po³¹czyæ z pierszym drugiej po³ówki
//i - ka¿dy pionowy pó³okr¹g idzie w górê, po¿nie od góry w dó³
void Egg::drawLines()
{
	//rozpoczêcie rysowania linii
	glBegin(GL_LINES);
	//dla ka¿dego punktu
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//pion
			this->points[i][j].setGlVertex();
			this->points[(i + 1) % this->resolution][j].setGlVertex();
			
			//poziome ani ukoœne linie nigdy nie bêd¹ rysowane dla z³¹czonych punktów na dole
			if (i > 0) {
				//poziom
				//pomijanie rysowania wokó³ najni¿szego punku i najwy¿szego je¿eli parzysta liczba punktów (bo 1 punkt)
				if (this->resolution % 2 == 1 || i != this->resolution / 2) {
					//je¿eli ostatni punkt w pó³okrêgu, trzeba po³¹czyæ go z pierwszym drugiego pó³okrêgu
					if (j + 1 == this->resolution) {
						this->points[i][j].setGlVertex();
						this->points[this->resolution - i][0].setGlVertex();
					}
					else {
						this->points[i][j].setGlVertex();
						this->points[i][j + 1].setGlVertex();
					}
				}
				//ukoœne
				//pomijanie rysowania wokó³ najni¿szego punku i najwy¿szego je¿eli parzysta liczba punktów (bo punkty ³¹cz¹ siê w jeden)
				if (i + 1 != this->resolution && i != this->resolution / 2 && (this->resolution % 2 == 1 || i + 1 != this->resolution / 2)) {
					if (j + 1 == this->resolution) {
						// je¿eli ostatni punkt w pó³okrêgu, trzeba po³¹czyæ go z pierwszym drugiego pó³okrêgu
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
//rysowanie wype³nionych trójk¹tów
void Egg::drawTriangles()
{
	//rozpoczêcie rysowania trójk¹tów
	glBegin(GL_TRIANGLES);

	//dla ka¿dej pozycji w wektorze
	for (size_t i = 1; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//po³ówka góna i przeciwleg³a dolna (pocz¹tek tablicy)
			if (i == 1 || i==this->resolution/2+1) {
				this->points[i][j].setGlVertex();
				this->points[(i - 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - i][0].setGlVertex();
				else
					this->points[i][j + 1].setGlVertex();
			}
			//po³ówka góna i przeciwleg³a dolna (koniec tablicy)
			if (i + 1 == this->resolution || i == this->resolution / 2 - 1 + this->resolution%2) {
				this->points[i][j].setGlVertex();
				this->points[(i + 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - i][0].setGlVertex();
				else
					this->points[i][j + 1].setGlVertex();
			}
			//je¿eli istniej¹ linie ukoœne (jak przy rysowaniu linii)
			if (i + 1 != this->resolution && i != this->resolution / 2 && (this->resolution % 2 == 1 || i + 1 != this->resolution / 2)) {
				//pierwszy z dwóch trójk¹tów
				this->points[i][j].setGlVertex();
				this->points[(i + 1) % this->resolution][j].setGlVertex();
				if (j + 1 == this->resolution)
					this->points[this->resolution - (i + 1) % this->resolution][0].setGlVertex();
				else
					this->points[(i + 1) % this->resolution][j + 1].setGlVertex();

				//drugi z dwóch trójk¹tów
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
//konstruktor (rozdzielczoœæ (iloœæ punktów), pozycja vector3f, skala)
Egg::Egg(size_t resolution, Vector3<GLfloat> pos, Vector3<GLfloat> scale)
{
	this->resolution = resolution;
	//dla ka¿dego wiersza
	for (size_t i = 0; i < resolution; i++) {
		//tworzenie kolumny
		this->points.push_back(std::vector<Point3f>());
		//dla ka¿dej kolumny
		for (size_t j = 0; j < resolution; j++) {
			//wyznaczanie pozycji równego odsêpu <0, 1>
			GLfloat u = static_cast<GLfloat>(i) / resolution;
			GLfloat v = static_cast<GLfloat>(j) / resolution;
			//wyliczanie pozycji punktu w przestrzeni 3d
			Point3f point = Point3f(
				(-90.f * std::pow(u, 5) + 225.f * std::pow(u, 4) - 270.f * std::pow(u, 3) + 180.f * std::pow(u, 2) - 45.f * u) * std::cosf(v * (GLfloat)M_PI),
				160.f * std::pow(u, 4) - 320.f * std::pow(u, 3) + 160.f * std::pow(u, 2),
				(-90.f * std::pow(u, 5) + 225.f * std::pow(u, 4) - 270.f * std::pow(u, 3) + 180.f * std::pow(u, 2) - 45.f * u) * std::sinf(v * (GLfloat)M_PI)
			);
			//dodanie przesuniêcia w pozycji
			point.cords += pos;
			//uwzglêdnienie skali jajka
			point.cords *= scale;
			//dodanie punktu do wektora punktów
			this->points.back().push_back(point);
		}
	}
}
//ustalanie kolorów
void Egg::setColor(ColorType colorType)
{
	//dla ka¿dego punktu
	for (size_t i = 0; i < this->resolution; i++) {
		for (size_t j = 0; j < this->resolution; j++) {
			//3 typy koloró
			switch (colorType)
			{
			case Egg::ColorType::Random:
				//ka¿dy rodzaj koloru jest losowy
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
	//rysowanie wed³ug podanego typu rysowania w App
	switch (App::getInstance()->displayType)
	{
	case DrawType::Point:
		//chmura punktów
		this->drawPoints();
		break;
	case DrawType::Line:
		//linie
		this->drawLines();
		break;
	case DrawType::Triangle:
		//wype³nienie (trój¹ky)
		this->drawTriangles();
		break;
	}
}
