#include "Mandelbrot.h"
#include <algorithm>
#include "settings.h"
#include "RgbTable.h"

//rozpocz�cie generowania tekstury (wyliczanie danych)
void Mandelbrot::generate()
{
	//wyliczenie danych na temat pozycji lewego g�rnego wierzcho�ka, wed�ug pozucji �rodka i wielko�ci
	//oraz wyliczanie mno�nika pikseli wed�ug wielko�ci fraktalu
	//dodatkowo brane jest pod uwag� to czy szeroko�� czy wysoko�� ekranu jest mniejsza i wielko�� fraktalu jest ustawiana wed�ug tego
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
	//ustawienie ilo�ci wydenerowanych wierszy na 0
	this->countRows = 0;
	//wype�nienie tablicy tekstury kolorem czarnym
	std::fill(this->textureData, this->textureData + this->texWidth * this->texHeight * 3, 0);
}

//generowanie wiersza struktury wed�ug podanego numeru kolumny
void Mandelbrot::generateRow(size_t y)
{
	//przeskalowana pozycja piksela na osi Im
	double c_im = ratio * y + minY;
	for (size_t x = 0; x < this->fractalW; x++) {
		//przeskalowana pozycja punktu na ozi Re
		double c_re = this->ratio * x + this->minX;

		size_t level = 0;
		double z_re = 0, z_im = 0, tmp_re;
		//algorytm wyliczania poziomu punktu w zbiorze, wed�ug podanej pozycji
		do {
			tmp_re = z_re * z_re - z_im * z_im + c_re;
			z_im = c_im + 2 * z_re * z_im;
			z_re = tmp_re;

			level++;
		} while (z_re * z_re + z_im * z_im < 4 && level < MAX_LEVELS);

		//wyliczenie pozycji koloru w tablicy kolor�w tekstury
		size_t pos = (y * this->texWidth + x) * 3;
		//je�eli poziom jest maksymalny to kolorem b�dzie czarny
		if (level == MAX_LEVELS) {
			this->textureData[pos] = this->textureData[pos + 1] = this->textureData[pos + 2] = 0;
		//w przeciwnym wypadku kolor jest brany z tablicy kolor�w z p�ynnym przej�ciem
		}else {
			//pobranie instancji tablicy kolor�w
			RgbTable* rgbtable = RgbTable::getInstance();
			//kolorkowanie
			this->textureData[pos] = rgbtable->getR(level);
			this->textureData[pos + 1] = rgbtable->getG(level);
			this->textureData[pos + 2] = rgbtable->getB(level);
		}
	}
}
//wyliczanie najmniejszej wi�kszej od n pot�gi 2
size_t Mandelbrot::get_pow_2(size_t n)
{
	size_t pow = 1;
	size_t tmp = n;
	//przesuni�cie bitowe podanej liczby a� do momentu kiedy b�dzie r�wna 1
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
	//generowanie tekstury (ilo��, miejsce przechowywania id wygenerowanych tekstur)
	glGenTextures(1, &this->texture);
	//wybieranie kt�rej tekstury ustawienia si� tycz�
	glBindTexture(GL_TEXTURE_2D, this->texture);
	//spos�b zmniejszania tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//spos�b zwi�kszania tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//uzupe�nianie tekstury po przekroczeniu zakresu [0, 1] wsp�rz�dnej S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//uzupe�nianie tekstury po przekroczeniu zakresu [0, 1] wsp�rz�dnej T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//wywo�anie metody zmieniaj�cej rozmiar fraktalu
	this->resize(width, height);
	//generowanie tekstury (fraktalu)
	this->generate();
}
//metoda aktualizuj�ca struktrur� fraktalu
void Mandelbrot::update()
{
	size_t i = 0;
	//wyrysowanie co LINES_SPACE wiersz fraktalu, kt�ry nie by� jeszcze wyrysowany a� do ko�ca wysoko�ci okna
	while (i <= this->fractalH / LINES_SPACE && this->countRows <= this->fractalH) {
		this->generateRow((this->countRows*LINES_SPACE)%this->fractalH);
		this->countRows++;
		i++;
	}
}
//metoda rysuj�ca fraktal na ekranie
void Mandelbrot::draw()
{
	//wybieranie kt�rej tekstury ustawienia si� tycz�
	glBindTexture(GL_TEXTURE_2D, this->texture);
	//�adowanie wygenerowanego obrazu do pami�ci (typ struktury, poziom szczeg��w, format kolor�w np rgb rgba, szeroko��, wysoko��, szeroko�� ramki teskstury, format kolor�w danych r�wnie�
	//np rgb rgba, typ danych np byte short float, dane tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->texWidth, this->texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textureData);
	//rysowanie prostok�tu wielko�ci ekranu i nak�adanie cz�ci tekstury kt�ra jest generowana
	glBegin(GL_QUADS);
		glTexCoord2f(this->texCutX, 0); glVertex2f(1, -1);
		glTexCoord2f(this->texCutX, this->texCutY); glVertex2f(1, 1);
		glTexCoord2f(0, this->texCutY); glVertex2f(-1, 1);
		glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glEnd();
}
//metoda zajmuj�ca si� obliczaniem danych wed�ug wielko�ci okna
void Mandelbrot::resize(size_t width, size_t height)
{
	//zwolnienie obecnie zaalokowanej tablicy przez tekstur�
	if (this->textureData != nullptr) {
		delete[] this->textureData;
	}
	//obliczenie wielko�ci tekstury (pot�ga 2)
	this->texWidth = Mandelbrot::get_pow_2(width);
	this->texHeight = Mandelbrot::get_pow_2(height);
	//wielko�� generowanego fraktalu
	this->fractalW = width;
	this->fractalH = height;
	//wyliczenie wsp�czynnika, w jakim miejscu b�dzie wycinana tekstura
	this->texCutX = static_cast<GLfloat>(this->fractalW) / this->texWidth;
	this->texCutY = static_cast<GLfloat>(this->fractalH) / this->texHeight;
	//stworzenie tablicy danych tekstury
	this->textureData = new GLubyte[this->texWidth * this->texHeight * 3];
	//rozpocz�cie algorytmu generowania fraktalu
	this->generate();
}
//metoda zajmuj�ca si� obliczaniem danych podczas przybli�ania/oddalania
void Mandelbrot::zoom(double size, int x, int y)
{
	//zmiana rozmiaru osi wsp�rz�dnych
	double sizeChange = size * this->size;
	this->size += sizeChange;

	//zmiana pozycji �rodka wed�ug pozycji myszy
	//dodatkowo nale�y wzi�� pod uwag� to, �e wielko�� jest ustawiana wed�ug tego czy szeroko�� czy wysoko�� jest mniejsza
	if (this->fractalH > this->fractalW) {
		this->posX += (0.5 - (static_cast<double>(x) / this->fractalW)) * sizeChange * this->fractalH / this->fractalW;
		this->posY -= (0.5 - (static_cast<double>(y) / this->fractalH)) * sizeChange;
	}
	else {
		this->posX += (0.5 - (static_cast<double>(x) / this->fractalW)) * sizeChange * this->fractalW / this->fractalH;
		this->posY -= (0.5 - (static_cast<double>(y) / this->fractalH)) * sizeChange;
	}


	
	//rozpocz�cie algorytmu generowanie tekstury (fraktalu)
	this->generate();
}
//destruktor
Mandelbrot::~Mandelbrot()
{
	delete[] this->textureData;
}
