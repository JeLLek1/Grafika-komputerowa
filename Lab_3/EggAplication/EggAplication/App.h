#pragma once
#include <chrono>
#include <ctime>
#include "EggSystem.h"
#include "settings.h"
#include "Egg.h"
#include "RotationDirection.h"
#include "Camera.h"
#include "Vector3.h"

//g³ówna klasa aplikacji (singleton)
class App
{
private:
	//rozdzielczoœæ g³ównego jajka
	size_t resolution_main = 0;
	//instancja aplikacji singletonu
	static App* instance;
	//czas ostatniego wykonania idleFunction
	std::chrono::high_resolution_clock::time_point lastTime;
	//g³ówny system jajek aplikacji
	EggSystem *mainSystem;
	//czy aplikacja jest w foolscreenie
	bool isFoolScreen = false;
	//obecna rotacja ca³ego systemu
	Vector3<GLfloat> currentRotation;
	//kamera
	Camera* camera;
	//przechowywanie ostatniej wychwyconei pozycji myszy
	int mouseX = 0, mouseY = 0, mouseDeltaX = 0, mouseDeltaY = 0, mouseStatus = 0;
	//wspó³czynnik szerokoœæ/wysokoœæ okna
	App();
public:
	//typ wyœwietlania wszystkich jajek (chmura punktów, linie, pe³ne trójk¹ty) 
	DrawType displayType = DEF_DISPLAY;
	//obecny typ obrotu g³ównego systemu
	RotationDirection rotationDirection = DEF_ROTATION_DIRECTION;
	//pdstêp czasowy miêdzy klatkami
	GLfloat dt;

	//pobranie instancji aplikacji - singletonu
	static App* getInstance();
	//metoda rysowania sceny
	static void renderScene();
	//metoda obs³ugi klawiszy klawiatury
	static void handelInputKey(unsigned char key, int x, int y);
	//metoda obs³ugi specjalnych klawiszy klawiatury jak f11
	static void handleInputSpecialKey(int key, int x, int y);
	//obs³uga zmiany wielkoœci okna
	static void handleInputChangeSize(GLsizei horizontal, GLsizei vertical);
	//obs³uga poruszania myszy, gdy przycisk jest trzymany
	static void handleMouseMotion(int x, int y);
	//obs³uga przycisków myszy
	static void handleMouse(int button, int status, int x, int y);
	//funckja wywo³ywana gdy nie ma w kolejnce ¿adnych eventów
	static void idleFunction();
	//losowanie wartoœc <0;1> gdy false i <-1;1> gdy true
	static GLfloat randGLfloat(bool negative = false);
	//aktualizacja pozycji i statusów wszystkich elementów
	void update();
	//metoda inicjuj¹ca elementy wyœwietlane
	void init();
	//destruktor
	~App();
};

