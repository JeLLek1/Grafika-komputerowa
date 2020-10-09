#include "Point.h"
#include "globFunc.h"
#include <gl/GL.h>

Point::Point(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
	//kolor jest zawsze losowy
	this->r = randGLfloat();
	this->g = randGLfloat();
	this->b = randGLfloat();
}

void Point::zoom(GLfloat step)
{
	//podczas przybli¿ania/oddalania nale¿y uwzglêdniæ proporcje odleg³oœci punktu od œrodka	
	this->x += this->x/100.f * step;
	this->y += this->y/100.f * step;
}

void Point::moov(GLfloat x, GLfloat y)
{
	this->x += x;
	this->y += y;
}