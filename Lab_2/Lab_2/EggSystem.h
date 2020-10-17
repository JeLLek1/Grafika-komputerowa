#pragma once
#include "Egg.h"
#include <Windows.h>
#include <gl/GL.h>
#include <list>
#include "Vector3f.h"

//System sk³adaj¹cy siê z podsystemów i centralnego jajka
class EggSystem
{
private:
	//lista podsystemów
	std::list<EggSystem*> systems;
	//jajko centralne systemu
	Egg *center;
public:
	//promieñ obrotu systemu
	GLfloat radius;
	//iloœæ stopni wykonywanych przejœæ po orbicie na sekundê
	GLfloat circlePerSec;
	//obecna iloœc stopni obrotu po orbicie
	GLfloat curentCircleAngle;
	//obecna iloœæ stopni obrotu w okó³ w³asnej osi
	GLfloat currentRotateAngle;
	//iloœæ stopni obrotów na sekundê w okó³ w³asnej osi
	GLfloat rotatePerSec;
	//konstruktor (jajko centralne, promieñ obrotu, iloœæ stopni w okó³ w³asnej osi, iloœc stopni obtoru po orbicie na sekundê, iloœæ stopni pocz¹tkowej pozycji orbity)
	EggSystem(Egg* center, GLfloat radius = 0.f, GLfloat rotatePerSec = 0.f, GLfloat circlePerSec = 0.f, GLfloat initialCircle = 0.f);
	//Wyrysowanie systemu
	void draw();
	//aktualizacja pozycji w systemie
	void update();
	//dodanie podsystemu
	void push(EggSystem* system);
	//destruktor
	~EggSystem();
};

