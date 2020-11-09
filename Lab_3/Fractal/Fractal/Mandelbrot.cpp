#include "Mandelbrot.h"
#include <algorithm>
#include "settings.h"
#include "RgbTable.h"

//rozpoczêcie generowania tekstury (wyliczanie danych)
void Mandelbrot::generate()
{
	//wyliczenie danych na temat pozycji lewego górnego wierzcho³ka, wed³ug pozucji œrodka i wielkoœci
	//oraz wyliczanie mnoŸnika pikseli wed³ug wielkoœci fraktalu
	//dodatkowo brane jest pod uwagê to czy szerokoœæ czy wysokoœæ ekranu jest mniejsza i wielkoœæ fraktalu jest ustawiana wed³ug tego
	if (this->fractalH > this->fractalW) {
		this->ratio = this->size / this->fractalW;
		this->minX = this->posX - this->size * 0.5;
		this->minY = this->posY - (this->size * this->fractalH / this->fractalW) * 0.5;
	}
	else {
		this->ratio = this->size / this->fractalH;
		this->minY = this->posY - this->size * 0.5;
		this->minX = this->posX - (this->size * this->fractalW / this->fractalH) * 0.5;
	}
	//ustawienie iloœci wydenerowanych wierszy na 0
	this->countRows = 0;
	//wype³nienie tablicy tekstury kolorem czarnym
	std::fill(this->textureData, this->textureData + this->texWidth * this->texHeight * 3, 0);
}

//generowanie wiersza struktury wed³ug podanego numeru kolumny
void Mandelbrot::generateRow(size_t y)
{
	//przeskalowana pozycja piksela na osi Im
	double c_im = ratio * y + minY;
	for (size_t x = 0; x < this->fractalW; x++) {
		//przeskalowana pozycja punktu na ozi Re
		double c_re = this->ratio * x + this->minX;

		size_t level = 0;
		double z_re = 0, z_im = 0, tmp_re;
		//algorytm wyliczania poziomu punktu w zbiorze, wed³ug podanej pozycji
		do {
			tmp_re = z_re * z_re - z_im * z_im + c_re;
			z_im = c_im + 2 * z_re * z_im;
			z_re = tmp_re;

			level++;
		} while (z_re * z_re + z_im * z_im < 4 && level < MAX_LEVELS);

		//wyliczenie pozycji koloru w tablicy kolorów tekstury
		size_t pos = (y * this->texWidth + x) * 3;
		//je¿eli poziom jest maksymalny to kolorem bêdzie czarny
		if (level == MAX_LEVELS) {
			this->textureData[pos] = this->textureData[pos + 1] = this->textureData[pos + 2] = 0;
		//w przeciwnym wypadku kolor jest brany z tablicy kolorów z p³ynnym przejœciem
		}else {
			//pobranie instancji tablicy kolorów
			RgbTable* rgbtable = RgbTable::getInstance();
			//kolorkowanie
			this->textureData[pos] = rgbtable->getR(level);
			this->textureData[pos + 1] = rgbtable->getG(level);
			this->textureData[pos + 2] = rgbtable->getB(level);
		}
	}
}
//wyliczanie najmniejszej wiêkszej od n potêgi 2
size_t Mandelbrot::get_pow_2(size_t n)
{
	size_t pow = 1;
	size_t tmp = n;
	//przesuniêcie bitowe podanej liczby a¿ do momentu kiedy bêdzie równa 1
	while (tmp > 1) {
		tmp = tmp >> 1;
		pow = pow << 1;
	}
	if (pow != n) {
		pow = pow << 1;
	}
	return pow;
}
//konstruktor
Mandelbrot::Mandelbrot(size_t width, size_t height)
{
	//generowanie tekstury (iloœæ, miejsce przechowywania id wygenerowanych tekstur)
	glGenTextures(1, &this->texture);
	//wybieranie której tekstury ustawienia siê tycz¹
	glBindTexture(GL_TEXTURE_2D, this->texture);
	//sposób zmniejszania tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//sposób zwiêkszania tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//uzupe³nianie tekstury po przekroczeniu zakresu [0, 1] wspó³rzêdnej S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//uzupe³nianie tekstury po przekroczeniu zakresu [0, 1] wspó³rzêdnej T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//wywo³anie metody zmieniaj¹cej rozmiar fraktalu
	this->resize(width, height);
	//generowanie tekstury (fraktalu)
	this->generate();
}
//metoda aktualizuj¹ca struktrurê fraktalu
void Mandelbrot::update()
{
	size_t i = 0;
	//wyrysowanie co LINES_SPACE wiersz fraktalu, który nie by³ jeszcze wyrysowany a¿ do koñca wysokoœci okna
	while (i <= this->fractalH / LINES_SPACE && this->countRows <= this->fractalH) {
		this->generateRow((this->countRows*LINES_SPACE)%this->fractalH);
		this->countRows++;
		i++;
	}
}
//metoda rysuj¹ca fraktal na ekranie
void Mandelbrot::draw()
{
	//wybieranie której tekstury ustawienia siê tycz¹
	glBindTexture(GL_TEXTURE_2D, this->texture);
	//³adowanie wygenerowanego obrazu do pamiêci (typ struktury, poziom szczegó³ów, format kolorów np rgb rgba, szerokoœæ, wysokoœæ, szerokoœæ ramki teskstury, format kolorów danych równie¿
	//np rgb rgba, typ danych np byte short float, dane tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->texWidth, this->texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textureData);
	//rysowanie prostok¹tu wielkoœci ekranu i nak³adanie czêœci tekstury która jest generowana
	glBegin(GL_QUADS);
		glTexCoord2f(this->texCutX, 0); glVertex2f(1, -1);
		glTexCoord2f(this->texCutX, this->texCutY); glVertex2f(1, 1);
		glTexCoord2f(0, this->texCutY); glVertex2f(-1, 1);
		glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glEnd();
}
//metoda zajmuj¹ca siê obliczaniem danych wed³ug wielkoœci okna
void Mandelbrot::resize(size_t width, size_t height)
{
	//zwolnienie obecnie zaalokowanej tablicy przez teksturê
	if (this->textureData != nullptr) {
		delete[] this->textureData;
	}
	//obliczenie wielkoœci tekstury (potêga 2)
	this->texWidth = Mandelbrot::get_pow_2(width);
	this->texHeight = Mandelbrot::get_pow_2(height);
	//wielkoœæ generowanego fraktalu
	this->fractalW = width;
	this->fractalH = height;
	//wyliczenie wspó³czynnika, w jakim miejscu bêdzie wycinana tekstura
	this->texCutX = static_cast<GLfloat>(this->fractalW) / this->texWidth;
	this->texCutY = static_cast<GLfloat>(this->fractalH) / this->texHeight;
	//stworzenie tablicy danych tekstury
	this->textureData = new GLubyte[this->texWidth * this->texHeight * 3];
	//rozpoczêcie algorytmu generowania fraktalu
	this->generate();
}
//metoda zajmuj¹ca siê obliczaniem danych podczas przybli¿ania/oddalania
void Mandelbrot::zoom(double size, int x, int y)
{
	//zmiana rozmiaru osi wspó³rzêdnych
	double sizeChange = size * this->size;
	this->size += sizeChange;

	//zmiana pozycji œrodka wed³ug pozycji myszy
	//dodatkowo nale¿y wzi¹æ pod uwagê to, ¿e wielkoœæ jest ustawiana wed³ug tego czy szerokoœæ czy wysokoœæ jest mniejsza
	if (this->fractalH > this->fractalW) {
		this->posX += (0.5 - (static_cast<double>(x) / this->fractalW)) * sizeChange * this->fractalH / this->fractalW;
		this->posY -= (0.5 - (static_cast<double>(y) / this->fractalH)) * sizeChange;
	}
	else {
		this->posX += (0.5 - (static_cast<double>(x) / this->fractalW)) * sizeChange * this->fractalW / this->fractalH;
		this->posY -= (0.5 - (static_cast<double>(y) / this->fractalH)) * sizeChange;
	}


	
	//rozpoczêcie algorytmu generowanie tekstury (fraktalu)
	this->generate();
}
//destruktor
Mandelbrot::~Mandelbrot()
{
	delete[] this->textureData;
}
