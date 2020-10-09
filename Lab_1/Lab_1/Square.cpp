#include "Square.h"

Square::Square(Point* lt, Point* rt, Point* rb, Point* lb)
{
	this->points = new Point * [4];
	this->points[0] = lt;
	this->points[1] = rt;
	this->points[2] = rb;
	this->points[3] = lb;
}

void Square::zoom(GLfloat step)
{
	//wywo�anie metody zoom dla wszystkich wierzcho�k�w kwadratu
	for (size_t i = 0; i < 4; i++) {
		this->points[i]->zoom(step);
	}
}

void Square::moov(GLfloat x, GLfloat y)
{
	//wywo�anie metody moov dla wszystkich wierzcho�k�w kwadratu
	for (size_t i = 0; i < 4; i++) {
		this->points[i]->moov(x, y);
	}
}

Square::~Square()
{
	//zwalnianie 4 kolejnych wierzcho�k�w
	for (size_t i = 0; i < 4; i++) {
		delete this->points[i];
	}
	//zwolnienie tablicy wierzcho�k�w
	delete[] this->points;
}

