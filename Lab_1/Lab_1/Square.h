#pragma once
#include "Point.h"
#include <windows.h>
#include <gl/GL.h>
class Square
{
private:
public:
	//informacje o punktach kwadratu
	Point** points;
	//konstruktor wywo³any jest z u¿yciem 4 ju¿ stworzonych punktów
	Square(Point* lt, Point* rt, Point* rb, Point* lb);
	//przybli¿anie kwadratu
	void zoom(GLfloat step);
	//przesuwanie kwadratu
	void moov(GLfloat x, GLfloat y);
	~Square();
};

