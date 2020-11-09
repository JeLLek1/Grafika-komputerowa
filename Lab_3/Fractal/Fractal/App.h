#pragma once
#include <chrono>
#include "settings.h"
#include "Mandelbrot.h"
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
	//czy aplikacja jest w foolscreenie
	bool isFoolScreen = false;
	//instancja przechowuj�ca fraktal
	Mandelbrot* fractal;
	//aktualna pozycja myszy
	int mouseX=0, mouseY=0;
	//przechowuje informacj� o tym, kt�ry klawisz myszy jest wci�ni�ty
	//(0 - brak, -1 - lewy, 1 - prawy) - je�eli s� oba na raz, brany pod uwag� jest ten pierwszy
	int mouseStatus=0;
	//konstruktor prywatny bo singleton
	App();
public:
	//usuwanie funkcjonalno�ci niepotrzebnych dla singletounu
	App(App& other) = delete;
	void operator=(const App&) = delete;

	//pdst�p czasowy mi�dzy klatkami
	double dt;

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
	//funckcja obs�ugi zdarze� myszy
	static void handleMouse(int button, int state, int x, int y);
	//obs�uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wci�ni�ty
	static void hangleMouseMotion(int x, int y);
	//funckja wywo�ywana gdy nie ma w kolejnce �adnych event�w
	static void idleFunction();
	//aktualizacja pozycji i status�w wszystkich element�w
	void update();
	//metoda inicjuj�ca elementy wy�wietlane
	void init();
	//destruktor
	~App();
};

