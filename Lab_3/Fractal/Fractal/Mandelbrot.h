#pragma once
#include <windows.h>
#include <gl/GL.h>
//generowanie i rysowanie fraktalu zbioru Mandelbrota
class Mandelbrot
{
private:
	//dane na temat kolorów w teksturze fraktalu
	GLubyte* textureData = nullptr;
	//wielkoœæ tekstury (inna ni¿ ekranu, potêga 2)
	size_t	texWidth = 0, 
			texHeight = 0, 
			//wielkoœæ tesktury na ekranie
			fractalW = 0, 
			fractalH = 0,
			//iloœæ wyrysowanych ju¿ wierszy
			countRows = 0;
	//identyfikator tekstruy
	GLuint	texture;
	//wyliczone miejsce odciêcia tekstury (tesktura wiêksza od wygenerowanego fraktalu)
	GLfloat texCutX, texCutY;
	//wielkoœæ osi generowanego fraktalu
	double	size = 4,
			//pozycja œrodka
			posX = 0,
			posY = 0,
			//dane wyliczane przez program (lewy górny róg fraktalu i wyliczony mno¿nik pikseli)
			ratio = 0,
			minX = 0,
			minY = 0;
	//rozpoczêcie generowania tekstury (wyliczanie danych)
	void generate();
	//generowanie wiersza struktury wed³ug podanego numeru kolumny
	void generateRow(size_t y);
	//wyliczanie najmniejszej wiêkszej od n potêgi 2
	static size_t get_pow_2(size_t n);
public:
	//konstruktor
	Mandelbrot(size_t width, size_t height);
	//metoda aktualizuj¹ca struktrurê fraktalu
	void update();
	//metoda rysuj¹ca fraktal na ekranie
	void draw();
	//metoda zajmuj¹ca siê obliczaniem danych wed³ug wielkoœci okna
	void resize(size_t width, size_t height);
	//metoda zajmuj¹ca siê obliczaniem danych podczas przybli¿ania/oddalania
	void zoom(double size, int x, int y);
	//destruktor
	~Mandelbrot();
};