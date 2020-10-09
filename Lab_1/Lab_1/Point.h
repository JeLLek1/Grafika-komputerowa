#pragma once
#include <windows.h>
#include <gl/GL.h>

class Point
{
public:
	GLfloat x, y;
	GLfloat r, g, b;
	Point(GLfloat x, GLfloat y);
	//przybli�anie wierzcho�ka
	void zoom(GLfloat step);
	//przesuwanie wierzcho�ka
	void moov(GLfloat x, GLfloat y);
};

