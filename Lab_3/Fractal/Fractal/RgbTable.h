#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "settings.h"

//przechowuje tablic� kolor�w z p�ynnym przej�ciem(ilo�� kolor�w ustawiana w settings.h)
struct RgbTable
{
private:
	//instancja singletona
	static RgbTable* instance;
	//tablica kolor�w
	GLubyte* colors;
	//ilo�� kolor�
	size_t size = COLORS_COUNT;
	//prywatny konstruktor singletonu
	RgbTable();
	//zamiana modelu barw hsv do rgb
	void hsvToRgb(size_t index, float H, float S, float V);
public:
	//pobranie instancji singletonu
	static RgbTable* getInstance();
	//zwr�cenie sk�adowej red z tablicy wed�ug podanego indeksu
	GLubyte getR(size_t index);
	//zwr�cenie sk�adowej green z tablicy wed�ug podanego indeksu
	GLubyte getG(size_t index);
	//zwr�cenie sk�adowej blue z tablicy wed�ug podanego indeksu
	GLubyte getB(size_t index);
	//destruktor
	~RgbTable();
};

