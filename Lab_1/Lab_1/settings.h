#pragma once
#include <string>
#include <windows.h>
#include <gl/GL.h>

//domyślne ustawienia ekrany
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const int WINDOW_SIZE = 1900;
const int WINDOW_HEIGHT = 1000;

//domyślne przybliżenie i krok podczas zmiany
const GLfloat DEF_ZOOM = 50.f;
const GLfloat DEF_STEP_ZOOM = 3.f;

//domyślny poziom kroku poruszania strzałkami i początkowe ustawienia pozycji
const GLfloat DEF_STEP_MOOV = 3.f;
const GLfloat CARPET_X = -50.f;
const GLfloat CARPET_Y = -50.f;
const GLfloat CARPET_SIZE = 100.f;

//domyślna parturbacja, krok podczas zmiany
const GLfloat DEF_NOISE = 0.0f;
const GLfloat DEF_NOISE_STEP = 2.5f;

//domyślny poziom fraktalu
const size_t DEF_LEVEL = 4;

//pomijanie wyświetlania nieaktywnych lelementów
const bool DEF_SHOW_VISIBLE = false;

//nazwa aplikacji
const char* const APP_NAME = "LAB 1";
