#pragma once
#include <vector>
#include "Vector3f.h"

//jajko
class Egg
{
public:
	//typy kolorów jajka
	enum class ColorType {
		Random = 0,	//wszystkie sk³adowe koloru losowe
		Red = 1,	//losowy tylko kolor czerwony
		Green = 2,	//losowy tylko kolor zielony
		Blue = 3	//losowy tylko kolor niebieski
	};
private:
	//wektor przechowuj¹cy wszystkie punkty jajka
	std::vector<std::vector<Vector3f>> points;
	//rozdzielczoœæ (iloœæ punktów)
	size_t resolution;
	//typ rysowania chmury punktów
	void drawPoints();
	//typ rysowania linii
	void drawLines();
	//typ rysowania wype³nionych trójk¹tów
	void drawTriangles();
public:
	//konstruktor (rozdzielczoœæ, pozycja w przestrzeni 3d, skala)
	Egg(size_t resolution, Vector3f pos = Vector3f(), Vector3f scale = Vector3f(1.f, 1.f, 1.f));
	//wype³nienie punktów kolorem
	void setColor(ColorType colorType);
	//rysowanie
	void draw();
};
