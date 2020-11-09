#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Vector3.h"

//obs³uga obserwatora
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
	//obs³uga gluLookAt z odpowiednimi przypisaniami
	void setView();
	//zmiana pozycji kamery
	void changeViewer(GLdouble x, GLdouble y);
	//przywracanie ustawieñ pocz¹tkowych kamery
	void reset();
	//obs³uga zmiany odleg³oœci do punktu obserwowanego
	void zoom(GLdouble distance);
};

