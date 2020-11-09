#pragma once
#include "RotationDirection.h"
#include "DrawType.h"

//domyœlne ustawienia ekrany
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const int WINDOW_SIZE = 1900;
const int WINDOW_HEIGHT = 1000;

//domyœlny obrót na sekundê trwania aplikacji
const GLfloat ROTATE_STEP = 1.5f;

//nazwa aplikacji
const char* const APP_NAME = "LAB 2";

//domyœlny typ wyœwietlania elementów
const DrawType DEF_DISPLAY = DrawType::Triangle;

//domyœlne dane dotycz¹ce obrotu wszystkich elementów
//-status obrotu (lewo,prawo,góra,dó³,brak)
const RotationDirection DEF_ROTATION_DIRECTION = RotationDirection::PAUSE;
//-prêdkoœæ obrotu
const GLfloat DEF_ROTATION_STEP = 25.f;

//minimalna iloœæ punktów g³ównego jajka
const size_t MIN_EGG_POINT_COUNT = 30;
//mno¿nik iloœci punktow drugiejgo jajka
const float SMALL_EGG_MULTIPLIER = 0.2f;

//mno¿nik przesuniêcia kamery
const GLdouble CAM_MULTIPLIER = 0.1;
//pozycja pocz¹tkowa kamery
const GLdouble EYE_X = 0.0, EYE_Y = 0.0, EYE_Z = 30.0;
const GLdouble CENTER_X = 0.0, CENTER_Y = 0.0, CENTER_Z = 0.0;
//jednostkowe przesuniêcie kamery
const GLdouble CAMERA_MOOV = 1.0;
//stopa b³êdu obliczania wektorów
const GLdouble EPSILON = 0.000001;