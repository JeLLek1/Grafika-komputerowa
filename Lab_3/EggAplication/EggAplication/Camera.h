#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Vector3.h"

//obs�uga obserwatora
class Camera
{
private:
	//pozycja obserwatora
	Vector3<GLdouble> eye;
	//pozycja punktu obserwowanego
	Vector3<GLdouble> center;
public:
	//konstruktor
	Camera();
	//obs�uga gluLookAt z odpowiednimi przypisaniami
	void setView();
	//zmiana pozycji kamery
	void changeViewer(GLdouble x, GLdouble y);
	//przywracanie ustawie� pocz�tkowych kamery
	void reset();
	//obs�uga zmiany odleg�o�ci do punktu obserwowanego
	void zoom(GLdouble distance);
};

