#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <list> 
#include <iterator> 
#include "Square.h"

class SierpinskiCarpet
{
private:
	//generowanie kolejnych poziomów dywanu Sierpińskiego
	void generateSierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise);
public:
	//Lista przechowująca informację o obliczonych kwadratach
	std::list <Square*> *squares;
	//przybliżanie
	void zoom(GLfloat step);
	//przesuwanie
	void moov(GLfloat x, GLfloat y);
	//konstruktor - x,y poziocja, size - wielkość, depth- głebokość, noise - poziom perturbacji
	SierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise);
	~SierpinskiCarpet();
};

