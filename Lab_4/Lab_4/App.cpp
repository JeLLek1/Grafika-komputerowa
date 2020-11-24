  // Copyright 2020 JeLLek
#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include "App.h"
#include "Egg.h"
#include "Material.h"

// instancja singletonu
App* App::instance = nullptr;

// konstruktor
App::App() {
    // pobranie rozdzielczości z okna
    printf("Podaj rozdzielczosc jajka glownego (drugie jajko zostanie ");
    printf(
        "wygenerowanie z % 1.1f razy mniejsza iloscia punktow): ",
        1/SMALL_EGG_MULTIPLIER);
    scanf_s("%zu", &this->resolution_main);
    // pobieranie dopóki wartośc nie będzie poprawna
    while (this->resolution_main < MIN_EGG_POINT_COUNT) {
        // czyszczenie buforu
        char c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        // pobranie informacji ponowanie
        printf("Uwaga! Glowne jajko musi miec przynajmniej rodzielczosc ");
        printf("% zu.Podaj rozdzielczosc ponownie : ", MIN_EGG_POINT_COUNT);
        scanf_s("%zu", &this->resolution_main);
    }

    std::srand(std::time(NULL));
    // GLUT_DOUBLE - tryb podwójnie buforowanego okna
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // ustawienie wartości początkowych okna
    glutInitWindowSize(WINDOW_SIZE, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    // Utworzenie okna i określenie treści napisu w nagłówku okna
    glutCreateWindow(APP_NAME);;

    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    glutDisplayFunc(App::renderScene);

    // zmiany rozmiaru okna
    glutReshapeFunc(App::handleInputChangeSize);

    // obsługa klawiszy specjalnych
    glutSpecialFunc(App::handleInputSpecialKey);
    // obsługa zwykłych klawiszy
    glutKeyboardFunc(App::handelInputKey);
    // obsługa poruszania się myszy, gdy przycisk jest trzymany
    glutMotionFunc(App::handleMouseMotion);
    // obsługa przycisków myszy
    glutMouseFunc(App::handleMouse);
    // funckja wywoływana gdy nie ma żadnych eventów
    glutIdleFunc(App::idleFunction);
    // kolor czyszczący ekran
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    glShadeModel(GL_SMOOTH);  // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);  // właczenie systemu oświetlenia sceny
    // Włączenie mechanizmu usuwania powierzchni niewidocznych
    glEnable(GL_DEPTH_TEST);

    this->init();
}
// pobranie instancji singletonu
App* App::getInstance() {
    if (App::instance == nullptr) {
        App::instance = new App();
    }
    return App::instance;
}
// rysowanie sceny
void App::renderScene() {
    App* app = App::getInstance();
    // Czyszczenie okna aktualnym kolorem czyszczącym
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie macierzy bieżącej
    glLoadIdentity();

    // ustawienie kamery
    app->camera->setView();

    // uswawienie światła
    app->circulatingLight->setLight();
    app->movingLight->setLight();

    // rotacja całego systemu według podanego inputu
    glRotatef(app->currentRotation.cords[0], 1.0f, 0.0f, 0.0f);
    glRotatef(app->currentRotation.cords[1], 0.0f, 1.0f, 0.0f);
    glRotatef(app->currentRotation.cords[2], 0.0f, 0.0f, 1.0f);
    // rysowanie systemu jajeczenego
    app->mainSystem->draw();

    // Przekazanie poleceń rysujących do wykonania
    glFlush();

    // zmiana buforów wyświeltanego i przetwarzanego
    glutSwapBuffers();
}

// metoda obsługi klawiszy klawiatury
void App::handelInputKey(unsigned char key, int x, int y) {
    // pobranie instancji singletonu
    App* app = App::getInstance();
    switch (key) {
    case 'p':
        // wyświetlanie jajek jako punkty
        app->displayType = DrawType::Point;
        break;
    case 'l':
        // wyświetlanie jajek jako linie
        app->displayType = DrawType::Line;
        break;
    case 't':
        // wyświetlanie wypełnionych jajek
        app->displayType = DrawType::Triangle;
        break;
    case ' ':
        // zatrzymanie głównego obrotu
        app->rotationDirection = RotationDirection::PAUSE;
        break;
    case 8:
        // reset pozycji kamery
        app->camera->reset();
        // reset pozycji światła
        app->movingLight->reset();
        break;
    case 'r':
        // kolor czerwony światła poruszangeo
        app->movingLight->setColor(0);
        break;
    case 'g':
        // kolor zielony światła poruszangeo
        app->movingLight->setColor(1);
        break;
    case 'b':
        // kolor niebieski światła poruszangeo
        app->movingLight->setColor(2);
        break;
    case '+':
        // przybliżenie
        app->camera->zoom(-CAMERA_MOOV);
        break;
    case '-':
        // przybliżenie
        app->camera->zoom(+CAMERA_MOOV);
        break;
    case 27:
        // wyjście z programu esc
        exit(0);
        break;
    }
}
// metoda obsługi specjalnych klawiszy klawiatury jak f11
void App::handleInputSpecialKey(int key, int x, int y) {
    App* app = App::getInstance();
    // jeżeli wciśnięto f11
    switch (key) {
    case GLUT_KEY_F11:
        if (app->isFoolScreen) {
            // powrót okna
            glutReshapeWindow(WINDOW_SIZE, WINDOW_HEIGHT);
        } else {
            // pełne okno
            glutFullScreen();
        }
        // zmiana informacji o aktualnym stanie okna
        app->isFoolScreen = !app->isFoolScreen;
        break;
    case GLUT_KEY_DOWN:
        // obrót jajka pionowo w dół
        app->rotationDirection = RotationDirection::DOWN;
        break;
    case GLUT_KEY_UP:
        // obrót jajka pionowo w górę
        app->rotationDirection = RotationDirection::UP;
        break;
    case GLUT_KEY_LEFT:
        // obrót jajka poziomo w lewo
        app->rotationDirection = RotationDirection::LEFT;
        break;
    case GLUT_KEY_RIGHT:
        // obrót jajka poziomo w prawo
        app->rotationDirection = RotationDirection::RIGHT;
        break;
    }
}

// obsługa zmiany wielkości okna
void App::handleInputChangeSize(GLsizei horizontal, GLsizei vertical) {
    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej

    if (vertical == 0) vertical = 1;
    // rzut perspektywiczny
    gluPerspective(70, static_cast<GLdouble>(horizontal)/vertical, 1.0, 100.0);


    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkości okna okna widoku (viewport) w zależności
    // relacji pomiędzy wysokością i szerokością okna

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    // Czyszczenie macierzy bieżącej
    glLoadIdentity();
}
// obsługa poruszania myszy, gdy przycisk jest trzymany
void App::handleMouseMotion(int x, int y) {
    // pobranie instancji aplikacji
    App* app = App::getInstance();
    // ustawienie przesunięcia obecnego myszy
    app->mouseDeltaX += x - app->mouseX;
    app->mouseDeltaY += y - app->mouseY;
    // ustawienie starej pozycji myszy jako ta aktualna
    app->mouseX = x;
    app->mouseY = y;
}
// obsługa przycisków myszy
void App::handleMouse(int button, int status, int x, int y) {
    // pobranie instancji aplikacji
    App* app = App::getInstance();
    switch (button) {
    // jeżeli event dotyczy lewogo przycisku
    case GLUT_LEFT:
        // jeżeli przycisk jest wciskany
        if (status == GLUT_DOWN) {
            // status wciśnięcia myszy
            app->mouseStatus = 1;
            // zapisanie obecnej pozycji myszy
            app->mouseX = x;
            app->mouseY = y;
            // ustawienie przesunięcia myszy na 0
            app->mouseDeltaX = 0;
            app->mouseDeltaY = 0;
        // jeżeli lewy przycisk jest puszczany
        } else {
            // ustawienie statu wcićnięta myszy
            app->mouseStatus = 0;
        }
        break;
    }
}

// "pętla główna" funckja wywoływana gdy nie ma innych ewentów
void App::idleFunction() {
    // pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    // obecny czas
    std::chrono::high_resolution_clock::time_point now
        = std::chrono::high_resolution_clock::now();
    // różnica czasu
    app->dt = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now - app->lastTime).count() / 1000000000.f;
    // przyspianie nowego czasu do starego czasu
    app->lastTime = now;
    // funckja zajmująca się zmianą stanów elementów
    app->update();
    // wywołanie przerysowania
    glutPostRedisplay();
}

// obsługa zmiany stanów elementów
void App::update() {
    // oświerzenie statnów pozycji systemu głównego
    this->mainSystem->update();

    // zmiana pozycji światła okrążającego orbitę
    this->circulatingLight->update();

    // aktualizacja pozycji światła
    if (this->mouseStatus == 1) {
        // ziana pozycji światła
        this->movingLight->changePos(LIGHT_MULTIPLIER * this->mouseDeltaX,
            LIGHT_MULTIPLIER * this->mouseDeltaY);
        // zerowanie przesunięcia myszy
        this->mouseDeltaX = this->mouseDeltaY = 0;
    }

    // zmiana pozycji osi obrotu głównego systemu
    switch (this->rotationDirection) {
    case RotationDirection::DOWN:
        // obrót pionowo w dół
        this->currentRotation += Vector3<GLfloat>(
            DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::UP:
        // oś obrotu pionowo w górę
        this->currentRotation += Vector3<GLfloat>(
            -DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::LEFT:
        // oś obrotu poziomo w lewo
        this->currentRotation += Vector3<GLfloat>(
            0.f, -DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    case RotationDirection::RIGHT:
        // oś obrotu poziomo w prawo
        this->currentRotation += Vector3<GLfloat>(
            0.f, DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    }
}
void App::init() {
    // ustawienie wartości początkowej odstępu czasu
    App::dt = 0.f;
    // ustawienie wartości czasu ostatniej klatki
    this->lastTime = std::chrono::high_resolution_clock::now();
    // tworzenie instancji kamery
    this->camera = new Camera();
    // Materiał pierwszego jajka
    Material* material = new Material(Vector4<GLfloat>(0.4f, 0.4f, 0.0f, 1.f),
        Vector4<GLfloat>(0.2f, 0.2f, 0.f, 1.f),
        Vector4<GLfloat>(1.f, 1.f, 0.3f, 1.f), 20.0f);
    // stworzenie nowego jajka (ilość szegółó, pozycja, wielkość)
    Egg* egg = new Egg(this->resolution_main, material,
        Vector3<GLfloat>(0.f, -3.f, 0.f),
        Vector3<GLfloat>(0.8f, 0.8f, 0.8f));
    // stwoenie "systemu" z centrum jako podane jajko
    this->mainSystem = new EggSystem(egg, 0.f, 0.f, 0.f);
    // Materiał drugiego jajka
    material = new Material(Vector4<GLfloat>(0.0f, 0.2f, 0.2f, 1.f),
        Vector4<GLfloat>(0.f, 0.2f, 0.2f, 1.f),
        Vector4<GLfloat>(0.3f, 1.f, 1.f, 1.f), 100.0f);
    // stworzenie jajka obracającego się w okół głównego jajka
    egg = new Egg(static_cast<size_t>(
        SMALL_EGG_MULTIPLIER * this->resolution_main),
        material,
        Vector3<GLfloat>(0.f, -1.f, 0.f),
        Vector3<GLfloat>(0.3f, 0.3f, 0.3f));
    // stworzenie systemu w którym jajko się znajduje
    // (jajko, promień, obrót wokół własnej osi na sekundę,
    // obrót w okół promienia na sekundę) i dodanie go do
    // listy systemów głównego systemu
    this->mainSystem->push(new EggSystem(egg, 7.f, -40.f, 15.f));

    // światło krążące w okół orbity (kierunkowe)
    this->circulatingLight = new CirculatingLight(0, LIGHT_ROTATE,
        Vector4<GLfloat>(0.1f, 0.1f, 0.1f, 1.f),
        Vector4<GLfloat>(1.f, 1.f, 1.f, 1.f),
        Vector4<GLfloat>(1.f, 1.f, 1.f, 1.f));
    this->movingLight = new MovingLight(1,
        Vector3<GLfloat>(LIGHT_X, LIGHT_Y, LIGHT_Z));
}
// desturktor
App::~App() {
    delete this->mainSystem;
    delete this->camera;
    delete this->circulatingLight;
    delete this->movingLight;
}
