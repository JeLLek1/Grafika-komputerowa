#include "Point3f.h"
//konstruktor pozycje x,y,z punktu
Point3f::Point3f(GLfloat x, GLfloat y, GLfloat z)
{
	this->cords = Vector3<GLfloat>(x, y, z);
	this->setColor();
}
//ustawianie kolorów punktu r,g,b
void Point3f::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = Vector3<GLfloat>(r, g, b);
}
//ustawienie koloru i pozycji punktu do wyrysowania
void Point3f::setGlVertex()
{
	glColor3fv(this->color.cords);
	glVertex3fv(this->cords.cords);
}
//pobranie tablicy koloru punktu
GLfloat* Point3f::getColor()
{
	return this->color.cords;
}