#pragma once
#include <windows.h>
#include <gl/GL.h>

class Point
{
public:
	GLfloat x, y;
	GLfloat r, g, b;
	Point(GLfloat x, GLfloat y);
	//przybliżanie wierzchołka
	void zoom(GLfloat step);
	//przesuwanie wierzchołka
	void moov(GLfloat x, GLfloat y);
};

