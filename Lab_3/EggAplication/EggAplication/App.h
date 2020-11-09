#pragma once
#include <chrono>
#include <ctime>
#include "EggSystem.h"
#include "settings.h"
#include "Egg.h"
#include "RotationDirection.h"
#include "Camera.h"
#include "Vector3.h"

//g��wna klasa aplikacji (singleton)
class App
{
private:
	//rozdzielczo�� g��wnego jajka
	size_t resolution_main = 0;
	//instancja aplikacji singletonu
	static App* instance;
	//czas ostatniego wykonania idleFunction
	std::chrono::high_resolution_clock::time_point lastTime;
	//g��wny system jajek aplikacji
	EggSystem *mainSystem;
	//czy aplikacja jest w foolscreenie
	bool isFoolScreen = false;
	//obecna rotacja ca�ego systemu
	Vector3<GLfloat> currentRotation;
	//kamera
	Camera* camera;
	//przechowywanie ostatniej wychwyconei pozycji myszy
	int mouseX = 0, mouseY = 0, mouseDeltaX = 0, mouseDeltaY = 0, mouseStatus = 0;
	//wsp�czynnik szeroko��/wysoko�� okna
	App();
public:
	//typ wy�wietlania wszystkich jajek (chmura punkt�w, linie, pe�ne tr�jk�ty) 
	DrawType displayType = DEF_DISPLAY;
	//obecny typ obrotu g��wnego systemu
	RotationDirection rotationDirection = DEF_ROTATION_DIRECTION;
	//pdst�p czasowy mi�dzy klatkami
	GLfloat dt;

	//pobranie instancji aplikacji - singletonu
	static App* getInstance();
	//metoda rysowania sceny
	static void renderScene();
	//metoda obs�ugi klawiszy klawiatury
	static void handelInputKey(unsigned char key, int x, int y);
	//metoda obs�ugi specjalnych klawiszy klawiatury jak f11
	static void handleInputSpecialKey(int key, int x, int y);
	//obs�uga zmiany wielko�ci okna
	static void handleInputChangeSize(GLsizei horizontal, GLsizei vertical);
	//obs�uga poruszania myszy, gdy przycisk jest trzymany
	static void handleMouseMotion(int x, int y);
	//obs�uga przycisk�w myszy
	static void handleMouse(int button, int status, int x, int y);
	//funckja wywo�ywana gdy nie ma w kolejnce �adnych event�w
	static void idleFunction();
	//losowanie warto�c <0;1> gdy false i <-1;1> gdy true
	static GLfloat randGLfloat(bool negative = false);
	//aktualizacja pozycji i status�w wszystkich element�w
	void update();
	//metoda inicjuj�ca elementy wy�wietlane
	void init();
	//destruktor
	~App();
};

