  // Copyright 2020 JeLLek
#pragma once
#include <chrono>
#include <ctime>
#include "EggSystem.h"
#include "Settings.h"
#include "Egg.h"
#include "RotationDirection.h"
#include "Camera.h"
#include "Vector3.h"
#include "CirculatingLight.h"
#include "MovingLight.h"

// główna klasa aplikacji (singleton)
class App {
 private:
    // rozdzielczość głównego jajka
    size_t resolution_main = 0;
    // instancja aplikacji singletonu
    static App* instance;
    // czas ostatniego wykonania idleFunction
    std::chrono::high_resolution_clock::time_point lastTime;
    // główny system jajek aplikacji
    EggSystem* mainSystem;
    // czy aplikacja jest w foolscreenie
    bool isFoolScreen = false;
    // obecna rotacja całego systemu
    Vector3<GLfloat> currentRotation;
    // kamera
    Camera* camera;
    // przechowywanie ostatniej wychwyconei pozycji myszy
    int mouseX = 0, mouseY = 0, mouseDeltaX = 0,
        mouseDeltaY = 0, mouseStatus = 0;
    // instancja światłą kierunkowego "okrążającego obiekt"
    CirculatingLight* circulatingLight;
    MovingLight* movingLight;

    App();

 public:
    // usuwanie funkcjonalności niepotrzebnych dla singletounu
    App(const App& other) = delete;
    void operator=(const App&) = delete;

    // typ wyświetlania wszystkich jajek
    // (chmura punktów, linie, pełne trójkąty)
    DrawType displayType = DEF_DISPLAY;
    // obecny typ obrotu głównego systemu
    RotationDirection rotationDirection = DEF_ROTATION_DIRECTION;
    // pdstęp czasowy między klatkami
    GLfloat dt;

    // pobranie instancji aplikacji - singletonu
    static App* getInstance();
    // metoda rysowania sceny
    static void renderScene();
    // metoda obsługi klawiszy klawiatury
    static void handelInputKey(unsigned char key, int x, int y);
    // metoda obsługi specjalnych klawiszy klawiatury jak f11
    static void handleInputSpecialKey(int key, int x, int y);
    // obsługa zmiany wielkości okna
    static void handleInputChangeSize(GLsizei horizontal, GLsizei vertical);
    // obsługa poruszania myszy, gdy przycisk jest trzymany
    static void handleMouseMotion(int x, int y);
    // obsługa przycisków myszy
    static void handleMouse(int button, int status, int x, int y);
    // funckja wywoływana gdy nie ma w kolejnce żadnych eventów
    static void idleFunction();
    // aktualizacja pozycji i statusów wszystkich elementów
    void update();
    // metoda inicjująca elementy wyświetlane
    void init();
    // destruktor
    ~App();
};
