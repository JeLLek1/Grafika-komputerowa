#pragma once
#include "RotationDirection.h"
#include "DrawType.h"

//domy�lne ustawienia ekrany
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const int WINDOW_SIZE = 1900;
const int WINDOW_HEIGHT = 1000;

//domy�lny obr�t na sekund� trwania aplikacji
const GLfloat ROTATE_STEP = 1.5f;

//nazwa aplikacji
const char* const APP_NAME = "LAB 2";

//domy�lny typ wy�wietlania element�w
const DrawType DEF_DISPLAY = DrawType::Triangle;

//domy�lne dane dotycz�ce obrotu wszystkich element�w
//-status obrotu (lewo,prawo,g�ra,d�,brak)
const RotationDirection DEF_ROTATION_DIRECTION = RotationDirection::PAUSE;
//-pr�dko�� obrotu
const GLfloat DEF_ROTATION_STEP = 25.f;

//minimalna ilo�� punkt�w g��wnego jajka
const size_t MIN_EGG_POINT_COUNT = 30;
//mno�nik ilo�ci punktow drugiejgo jajka
const float SMALL_EGG_MULTIPLIER = 0.1;