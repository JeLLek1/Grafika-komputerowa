#pragma once
#include <windows.h>
#include <gl/GL.h>

class Point
{
public:
	GLfloat x, y;
	GLfloat r, g, b;
	Point(GLfloat x, GLfloat y);
	//przybli¿anie wierzcho³ka
	void zoom(GLfloat step);
	//przesuwanie wierzcho³ka
	void moov(GLfloat x, GLfloat y);
};

