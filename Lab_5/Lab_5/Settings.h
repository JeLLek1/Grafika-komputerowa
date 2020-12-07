  // Copyright 2020 JeLLek
#pragma once
#include <string>
#include "RotationDirection.h"
#include "DrawType.h"

// domyślne ustawienia ekrany
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const int WINDOW_SIZE = 1900;
const int WINDOW_HEIGHT = 1000;

// domyślny obrót na sekundę trwania aplikacji
const GLfloat ROTATE_STEP = 1.5f;

// nazwa aplikacji
const char* const APP_NAME = "LAB 5";

// domyślny typ wyświetlania elementów
const DrawType DEF_DISPLAY = DrawType::Triangle;

// domyślne dane dotyczące obrotu wszystkich elementów
// -status obrotu (lewo,prawo,góra,dół,brak)
const RotationDirection DEF_ROTATION_DIRECTION = RotationDirection::PAUSE;
// -prędkość obrotu
const GLfloat DEF_ROTATION_STEP = 25.f;

// minimalna ilość punktów głównego jajka
const size_t MIN_EGG_POINT_COUNT = 30;
// mnożnik ilości punktow drugiejgo jajka
const float SMALL_EGG_MULTIPLIER = 0.2f;

// mnożnik przesunięcia światła
const GLdouble LIGHT_MULTIPLIER = 0.1;
// pozycja początkowa kamery
const GLdouble EYE_X = 0.0, EYE_Y = 0.0, EYE_Z = 30.0;
const GLdouble CENTER_X = 0.0, CENTER_Y = 0.0, CENTER_Z = 0.0;
// pozycja początkowa światła punktowego
const GLfloat LIGHT_X = 0.0, LIGHT_Y = 0.0, LIGHT_Z = 30.0;
// prędkość obrotu światła kierunkowego
const GLfloat LIGHT_ROTATE = 10.f;
// jednostkowe przesunięcie kamery (przybliżanie)
const GLdouble CAMERA_MOOV = 1.0;
// stopa błędu obliczania wektorów
const GLdouble EPSILON = 0.000001;
// rozdzielczość jajka
const size_t EGG_RESSOLUTION = 50;

// nazwa tekstury jajka
const char* const TEX_FILE = "textures/tex.tga";
const unsigned TRIANGLES_COUNT = 4;
const unsigned FRAMES_COUNT = 4;
const GLfloat FRAME_TIME = 0.5;