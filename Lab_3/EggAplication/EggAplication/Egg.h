#pragma once
#include <vector>
#include "Vector3.h"
#include "Point3f.h"

//jajko
class Egg
{
public:
	//typy kolor�w jajka
	enum class ColorType {
		Random = 0,	//wszystkie sk�adowe koloru losowe
		Red = 1,	//losowy tylko kolor czerwony
		Green = 2,	//losowy tylko kolor zielony
		Blue = 3	//losowy tylko kolor niebieski
	};
private:
	//wektor przechowuj�cy wszystkie punkty jajka
	std::vector<std::vector<Point3f>> points;
	//rozdzielczo�� (ilo�� punkt�w)
	size_t resolution;
	//typ rysowania chmury punkt�w
	void drawPoints();
	//typ rysowania linii
	void drawLines();
	//typ rysowania wype�nionych tr�jk�t�w
	void drawTriangles();
public:
	//konstruktor (rozdzielczo��, pozycja w przestrzeni 3d, skala)
	Egg(size_t resolution, Vector3<GLfloat> pos = Vector3<GLfloat>(), Vector3<GLfloat> scale = Vector3<GLfloat>(1.f, 1.f, 1.f));
	//wype�nienie punkt�w kolorem
	void setColor(ColorType colorType);
	//rysowanie
	void draw();
};
