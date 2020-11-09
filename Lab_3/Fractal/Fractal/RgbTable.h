#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "settings.h"

//przechowuje tablicê kolorów z p³ynnym przejœciem(iloœæ kolorów ustawiana w settings.h)
struct RgbTable
{
private:
	//instancja singletona
	static RgbTable* instance;
	//tablica kolorów
	GLubyte* colors;
	//iloœæ koloró
	size_t size = COLORS_COUNT;
	//prywatny konstruktor singletonu
	RgbTable();
	//zamiana modelu barw hsv do rgb
	void hsvToRgb(size_t index, float H, float S, float V);
public:
	//pobranie instancji singletonu
	static RgbTable* getInstance();
	//zwrócenie sk³adowej red z tablicy wed³ug podanego indeksu
	GLubyte getR(size_t index);
	//zwrócenie sk³adowej green z tablicy wed³ug podanego indeksu
	GLubyte getG(size_t index);
	//zwrócenie sk³adowej blue z tablicy wed³ug podanego indeksu
	GLubyte getB(size_t index);
	//destruktor
	~RgbTable();
};

