#include "RgbTable.h"
#include <cmath>

//instancja singletonu pocz¹tkowo nullptr
RgbTable* RgbTable::instance = nullptr;

//prywatny konstruktor
RgbTable::RgbTable() {
	this->colors = new GLubyte[this->size * 3];
	//wed³ug iloœci kolorów generuje kolory z p³ynnym przejœciem
	for (size_t i = 0; i < this->size; i++) {
		this->hsvToRgb(i, i*360.f/this->size, 1.f, 1.f);
	}
}
//zamiana modelu barw hsv do rgb
void RgbTable::hsvToRgb(size_t index, float H, float S, float V)
{
	//konwersja wed³ug wzoru http://4.bp.blogspot.com/-BIcNZkeJHn0/T94CP7e0F3I/AAAAAAAAAP8/ZX7vnhdklV8/s1600/hsvtorgb.png
	float c, m, x, cm, xm, r, g, b;
	c = V * S;
	m = V - c;
	x = c*(1-std::fabs(std::fmod((H / 60.f), 2.f) - 1));
	cm = c + m;
	xm = x + m;
	int part = static_cast<int>(H / 60);
	switch (part) {
	case 0:
		r = cm, g = xm, b = m;
		break;
	case 1:
		r = xm, g = cm, b = m;
		break;
	case 2:
		r = m, g = cm, b = xm;
		break;
	case 3:
		r = m, g = xm, b = cm;
		break;
	case 4:
		r = xm, g = m, b = cm;
		break;
	case 5:
		r = cm, g = m, b = xm;
		break;
	default:
		r = m, g = m, b = m;
		break;
	}
	//zamiana z typu float na typ GLubyte (sk³adowe rgb by³y w przedzia³ach [0-1]
	this->colors[index * 3] = static_cast<GLubyte>(r*255);
	this->colors[index * 3 + 1] = static_cast<GLubyte>(g * 255);
	this->colors[index * 3 + 2] = static_cast<GLubyte>(b * 255);
}

//generowanie instancji singletonu je¿eli nie istnieje i zwracanie jej
RgbTable* RgbTable::getInstance()
{
	if (RgbTable::instance == nullptr) {
		RgbTable::instance = new RgbTable();
	}
	return RgbTable::instance;
}
//zwrócenie sk³adowej red z tablicy wed³ug podanego indeksu
GLubyte RgbTable::getR(size_t index)
{
	//zabezpieczenie przed podaniem zbyt du¿ego indeksu
	return this->colors[(index%this->size)*3];
}
//zwrócenie sk³adowej green z tablicy wed³ug podanego indeksu
GLubyte RgbTable::getG(size_t index)
{
	//zabezpieczenie przed podaniem zbyt du¿ego indeksu
	return this->colors[(index % this->size) * 3+1];
}
//zwrócenie sk³adowej blue z tablicy wed³ug podanego indeksu
GLubyte RgbTable::getB(size_t index)
{
	//zabezpieczenie przed podaniem zbyt du¿ego indeksu
	return this->colors[(index % this->size) * 3+2];
}
//destruktor
RgbTable::~RgbTable()
{
	delete this->colors;
	this->instance = nullptr;
}
