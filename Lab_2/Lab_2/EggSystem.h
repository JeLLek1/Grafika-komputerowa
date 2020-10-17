#pragma once
#include "Egg.h"
#include <Windows.h>
#include <gl/GL.h>
#include <list>
#include "Vector3f.h"

//System sk�adaj�cy si� z podsystem�w i centralnego jajka
class EggSystem
{
private:
	//lista podsystem�w
	std::list<EggSystem*> systems;
	//jajko centralne systemu
	Egg *center;
public:
	//promie� obrotu systemu
	GLfloat radius;
	//ilo�� stopni wykonywanych przej�� po orbicie na sekund�
	GLfloat circlePerSec;
	//obecna ilo�c stopni obrotu po orbicie
	GLfloat curentCircleAngle;
	//obecna ilo�� stopni obrotu w ok� w�asnej osi
	GLfloat currentRotateAngle;
	//ilo�� stopni obrot�w na sekund� w ok� w�asnej osi
	GLfloat rotatePerSec;
	//konstruktor (jajko centralne, promie� obrotu, ilo�� stopni w ok� w�asnej osi, ilo�c stopni obtoru po orbicie na sekund�, ilo�� stopni pocz�tkowej pozycji orbity)
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

