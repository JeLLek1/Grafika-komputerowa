#pragma once
#include <windows.h>
#include <gl/GL.h>
//punkt u³atwiaj¹cy operacjie na punktach openGl
class Vector3f
{
public:
	//pozycjia punktu
	GLfloat cords[3];
	//kolor punktu
	GLfloat color[3] = {1.f, 1.f, 1.f};

	//kontruktor (pozycja x,y,z)
	Vector3f(GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f);
	//ustawienie koloru (r,g,b)
	void setColor(GLfloat r = 0.f, GLfloat g = 0.f, GLfloat b = 0.f);
	//Ustawienie punktu dla elementów rysowania openGL
	void setGlVertex();
	//pobranie tablicy 3-elementowej pozycji
	GLfloat* getPosition();
	//pobiranie tablicy 3-elementowej kolorów
	GLfloat* getColor();
	//operator += dodawanie do wektora wektoru
	Vector3f operator += (const Vector3f& Vector3f);
	//operator *= mno¿enie wektorów
	Vector3f operator *= (const Vector3f& Vector3f);
};

