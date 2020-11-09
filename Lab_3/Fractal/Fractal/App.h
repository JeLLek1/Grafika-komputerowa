#pragma once
#include <chrono>
#include "settings.h"
#include "Mandelbrot.h"
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
	//czy aplikacja jest w foolscreenie
	bool isFoolScreen = false;
	//instancja przechowuj¹ca fraktal
	Mandelbrot* fractal;
	//aktualna pozycja myszy
	int mouseX=0, mouseY=0;
	//przechowuje informacjê o tym, który klawisz myszy jest wciœniêty
	//(0 - brak, -1 - lewy, 1 - prawy) - je¿eli s¹ oba na raz, brany pod uwagê jest ten pierwszy
	int mouseStatus=0;
	//konstruktor prywatny bo singleton
	App();
public:
	//usuwanie funkcjonalnoœci niepotrzebnych dla singletounu
	App(App& other) = delete;
	void operator=(const App&) = delete;

	//pdstêp czasowy miêdzy klatkami
	double dt;

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
	//funckcja obs³ugi zdarzeñ myszy
	static void handleMouse(int button, int state, int x, int y);
	//obs³uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wciœniêty
	static void hangleMouseMotion(int x, int y);
	//funckja wywo³ywana gdy nie ma w kolejnce ¿adnych eventów
	static void idleFunction();
	//aktualizacja pozycji i statusów wszystkich elementów
	void update();
	//metoda inicjuj¹ca elementy wyœwietlane
	void init();
	//destruktor
	~App();
};

