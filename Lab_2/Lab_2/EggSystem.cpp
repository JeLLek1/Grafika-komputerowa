#include "EggSystem.h"
#include "App.h"
//konstruktor, ustawienie jajka centralnego, promienia obrotu, kont rotacji na sekund�, ilo�� k� otaczania na sekund�, i startowej pozycji otaczania
EggSystem::EggSystem(Egg* center, GLfloat radius, GLfloat rotatePerSec, GLfloat circlePerSec, GLfloat initialCircle) {
	this->radius = radius;
	this->rotatePerSec = rotatePerSec;
	this->circlePerSec = circlePerSec;
	this->center = center;
	this->curentCircleAngle = initialCircle;
	this->currentRotateAngle = 0.f;
}
//rysowanie
void EggSystem::draw()
{
	//ustawienie pozycji systemu (obecy obr�t w ok� osio i w og� rodzica)
	glRotatef(this->curentCircleAngle, 0.f, 1.f, 0.f);
	glTranslatef(this->radius, 0.f, 0.f);
	glRotatef(this->currentRotateAngle, 0.f, 1.f, 0.f);
	//je�eli center jest ustawiony to wyrysowanie go
	if (this->center != nullptr) {
		this->center->draw();
	}

	//dla ka�dego podsystemu wywo�anie metody draw
	std::list<EggSystem*>::iterator it;
	for (it = this->systems.begin(); it != this->systems.end(); it++)
	{
		(*it)->draw();
	}
	//zmiana transformacji do poprzedniego stanu
	glRotatef(-this->currentRotateAngle, 0.f, 1.f, 0.f);
	glTranslatef(-this->radius, 0.f, 0.f);
	glRotatef(-this->curentCircleAngle, 0.f, 1.f, 0.f);
}

//altualizacjia pozycji systemu
void EggSystem::update()
{
	//aktualna pozycja okr��e� w ok� promienia
	GLfloat dt = App::getInstance()->dt;
	this->curentCircleAngle += dt * this->circlePerSec;
	if (this->circlePerSec>0 && this->curentCircleAngle >= 360.f) {
		this->curentCircleAngle -= 360.f;
	}
	else if (this->circlePerSec < 0 && this->curentCircleAngle <= 0.f) {
		this->curentCircleAngle += 360.f;
	}
	//aktualna pozycja obrotu w ok� w�asnej osi
	this->currentRotateAngle += dt * this->rotatePerSec;
	if (this->rotatePerSec > 0 && this->currentRotateAngle >= 360.f) {
		this->currentRotateAngle -= 360.f;
	}
	else if (this->rotatePerSec < 0 && this->currentRotateAngle <= 0.f) {
		this->currentRotateAngle += 360.f;
	}
	//dla ka�dego podsystemu wywo�anie metody draw
	std::list<EggSystem*>::iterator it;
	for (it = this->systems.begin(); it != this->systems.end(); it++)
	{
		(*it)->update();
	}
}
//dodanie podsystemu
void EggSystem::push(EggSystem* system)
{
	this->systems.push_back(system);
}
//destruktor
EggSystem::~EggSystem()
{
	//zwalnianie pami�ci �rodka systemu
	if (this->center != nullptr) {
		delete center;
	}
	//zwalnianie pami�ci zajmowanej przez podsystemy
	std::list<EggSystem*>::iterator it;
	for (it = this->systems.begin(); it != this->systems.end(); it++)
	{
		delete (*it);
	}
}
