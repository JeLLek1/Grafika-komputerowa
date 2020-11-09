#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "Vector3.h"
//punkt u³atwiaj¹cy operacjie na punktach openGl
class Point3f
{
public:
	//pozycjia punktu
	Vector3<GLfloat> cords;
	//kolor punktu
	Vector3<GLfloat> color;

	//konstruktor
	Point3f(GLfloat x=0, GLfloat y = 0, GLfloat z = 0);

	//ustawienie koloru
	void setColor(GLfloat r = 0.f, GLfloat g = 0.f, GLfloat b = 0.f);
	//Ustawienie punktu dla elementów rysowania openGL
	void setGlVertex();
	//pobiranie tablicy 3-elementowej kolorów
	GLfloat* getColor();
};

