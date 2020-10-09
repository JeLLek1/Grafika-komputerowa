#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <list> 
#include <iterator> 
#include "Square.h"

class SierpinskiCarpet
{
private:
	//generowanie kolejnych poziomów dywanu Sierpiñskiego
	void generateSierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise);
public:
	//Lista przechowuj¹ca informacjê o obliczonych kwadratach
	std::list <Square*> *squares;
	//przybli¿anie
	void zoom(GLfloat step);
	//przesuwanie
	void moov(GLfloat x, GLfloat y);
	//konstruktor - x,y poziocja, size - wielkoœæ, depth- g³ebokoœæ, noise - poziom perturbacji
	SierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth, GLfloat noise);
	~SierpinskiCarpet();
};

