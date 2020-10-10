#pragma once
#include <string>
#include <windows.h>
#include <gl/GL.h>

/*	Opcja pozwala na w��czenie rysowania tylko widocznych element�w. Pozwala to na rysowanie du�ych fraktali, je�eli s� przybli�one
	jednak z powodu tego, �e kolory i zniekszta�cenia s� losowe i rysowanie niekt�rych element�w jest pomijane, to powoduje to 
	zmian� koloru lub kszta�tu podczas przybli�ania. */
#define CHECK_IF_VISIBLE false

//domy�lne ustawienia ekrany
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const int WINDOW_SIZE = 1900;
const int WINDOW_HEIGHT = 1000;

//domy�lne przybli�enie i krok podczas zmiany
const GLfloat DEF_ZOOM = 50.f;
const GLfloat DEF_STEP_ZOOM = 3.f;

//domy�lny poziom kroku poruszania strza�kami i pocz�tkowe ustawienia pozycji
const GLfloat DEF_STEP_MOOV = 3.f;
const GLfloat CARPET_X = -50.f;
const GLfloat CARPET_Y = -50.f;
const GLfloat CARPET_SIZE = 100.f;

//domy�lna parturbacja, krok podczas zmiany
const GLfloat DEF_NOISE = 0.0f;
const GLfloat DEF_NOISE_STEP = 2.5f;

//domy�lny poziom fraktalu
const size_t DEF_LEVEL = 4;

//nazwa aplikacji
const char* const APP_NAME = "LAB 1";
