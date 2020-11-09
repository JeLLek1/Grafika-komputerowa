#include "Camera.h"
#include <gl/GLU.h>
#include "settings.h"

//konstruktor
Camera::Camera()
{
	this->reset();
}
//obs�uga gluLookAt z odpowiednimi przypisaniami
void Camera::setView()
{
	gluLookAt(eye.cords[0], eye.cords[1], eye.cords[2], center.cords[0], center.cords[1], center.cords[2], 0.0, 1.0, 0.0);
}
//zmiana pozycji kamery
void Camera::changeViewer(GLdouble x, GLdouble y)
{
	//zmiana pozycji obserwatora
	eye += Vector3<GLdouble>(x, -y, 0.0);
	//zmiana pozycji punktu obserwowanego
	center += Vector3<GLdouble>(x, -y, 0.0);
}
//przywracanie ustawie� pocz�tkowych kamery
void Camera::reset()
{
	//przywracanie ustawienia pocz�tkowego obserwatora
	eye = Vector3<GLdouble>(EYE_X, EYE_Y, EYE_Z);
	//przywracanie ustawienia pocz�tkowego punktu obserwowanego
	center = Vector3<GLdouble>(CENTER_X, CENTER_Y, CENTER_Z);
}
//obs�uga zmiany odleg�o�ci do punktu obserwowanego
void Camera::zoom(GLdouble distance)
{
	//znormalizowany wektor od �rodka do obserwatora
	Vector3<GLdouble> vector = this->eye - this->center;
	vector.normalize();

	//obliczenie pozycji obserwatora po zmianie dystansu
	Vector3<GLdouble> eyeChanged = this->eye + vector * distance;

	//znormalizowany wektor od �rodka do obserwatora po zmianie dystansu
	Vector3<GLdouble> newEyeVector = eyeChanged - this->center;
	newEyeVector.normalize();

	//test, czy nie zmieni� si� wektor (aby unikn�� sytuacji "wyjechania" poza jajko podczas przybli�ania)
	if (vector.distance(newEyeVector)< EPSILON) {
		//operator przypisania jest przeci��ony i powoduje przypisanie kolejnych koordynat�w
		this->eye = eyeChanged;
	}
	
}
