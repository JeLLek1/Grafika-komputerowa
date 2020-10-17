#include "Vector3f.h"
//konstruktor pozycje x,y,z punktu
Vector3f::Vector3f(GLfloat x, GLfloat y, GLfloat z)
{
	this->cords[0] = x;
	this->cords[1] = y;
	this->cords[2] = z;
}
//ustawianie kolorów punktu r,g,b
void Vector3f::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}
//ustawienie koloru i pozycji punktu do wyrysowania
void Vector3f::setGlVertex()
{
	glColor3fv(this->color);
	glVertex3fv(this->cords);
}
//pobranie tablicy pozycji punktu
GLfloat* Vector3f::getPosition()
{
	return this->cords;
}
//pobranie tablicy koloru punktu
GLfloat* Vector3f::getColor()
{
	return this->color;
}
//dodawanie wektorów do siebie
Vector3f Vector3f::operator+=(const Vector3f& Vector3f)
{
	this->cords[0] += Vector3f.cords[0];
	this->cords[1] += Vector3f.cords[1];
	this->cords[2] += Vector3f.cords[2];
	return *this;
}
//mno¿enie wetkorów
Vector3f Vector3f::operator*=(const Vector3f& Vector3f)
{
	this->cords[0] *= Vector3f.cords[0];
	this->cords[1] *= Vector3f.cords[1];
	this->cords[2] *= Vector3f.cords[2];
	return *this;
}
