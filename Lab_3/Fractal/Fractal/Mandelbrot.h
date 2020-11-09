#pragma once
#include <windows.h>
#include <gl/GL.h>
//generowanie i rysowanie fraktalu zbioru Mandelbrota
class Mandelbrot
{
private:
	//dane na temat kolor�w w teksturze fraktalu
	GLubyte* textureData = nullptr;
	//wielko�� tekstury (inna ni� ekranu, pot�ga 2)
	size_t	texWidth = 0, 
			texHeight = 0, 
			//wielko�� tesktury na ekranie
			fractalW = 0, 
			fractalH = 0,
			//ilo�� wyrysowanych ju� wierszy
			countRows = 0;
	//identyfikator tekstruy
	GLuint	texture;
	//wyliczone miejsce odci�cia tekstury (tesktura wi�ksza od wygenerowanego fraktalu)
	GLfloat texCutX, texCutY;
	//wielko�� osi generowanego fraktalu
	double	size = 4,
			//pozycja �rodka
			posX = 0,
			posY = 0,
			//dane wyliczane przez program (lewy g�rny r�g fraktalu i wyliczony mno�nik pikseli)
			ratio = 0,
			minX = 0,
			minY = 0;
	//rozpocz�cie generowania tekstury (wyliczanie danych)
	void generate();
	//generowanie wiersza struktury wed�ug podanego numeru kolumny
	void generateRow(size_t y);
	//wyliczanie najmniejszej wi�kszej od n pot�gi 2
	static size_t get_pow_2(size_t n);
public:
	//konstruktor
	Mandelbrot(size_t width, size_t height);
	//metoda aktualizuj�ca struktrur� fraktalu
	void update();
	//metoda rysuj�ca fraktal na ekranie
	void draw();
	//metoda zajmuj�ca si� obliczaniem danych wed�ug wielko�ci okna
	void resize(size_t width, size_t height);
	//metoda zajmuj�ca si� obliczaniem danych podczas przybli�ania/oddalania
	void zoom(double size, int x, int y);
	//destruktor
	~Mandelbrot();
};