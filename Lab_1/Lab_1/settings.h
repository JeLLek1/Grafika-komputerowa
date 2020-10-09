#pragma once
#include <string>
#include <windows.h>
#include <gl/GL.h>

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
const GLfloat DEF_NOISE_STEP = 0.1f;

//domy�lny poziom fraktalu
const size_t DEF_LEVEL = 4;

//nazwa aplikacji
const char* const APP_NAME = "LAB 1";
