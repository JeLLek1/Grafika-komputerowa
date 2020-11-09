#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include "App.h"
#include "Egg.h"

//instancja singletonu
App* App::instance = nullptr;

//konstruktor
App::App() {
    //pobranie rozdzielczo�ci z okna
    printf("Podaj rozdzielczosc jajka glownego (drugie jajko zostanie wygenerowanie z %1.1f razy mniejsza iloscia punktow): ", 1/SMALL_EGG_MULTIPLIER);
    scanf_s("%u", &this->resolution_main);
    //pobieranie dop�ki warto�c nie b�dzie poprawna
    while (this->resolution_main < MIN_EGG_POINT_COUNT) {
        //czyszczenie buforu
        char c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        //pobranie informacji ponowanie
        printf("Uwaga! Glowne jajko musi miec przynajmniej rodzielczosc %u. Podaj rozdzielczosc ponownie: ", MIN_EGG_POINT_COUNT);
        scanf_s("%u", &this->resolution_main);
    }

    std::srand(std::time(NULL));
    //GLUT_DOUBLE - tryb podw�jnie buforowanego okna
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //ustawienie warto�ci pocz�tkowych okna
    glutInitWindowSize(WINDOW_SIZE, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    // Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna
    glutCreateWindow(APP_NAME);;

    // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
    glutDisplayFunc(App::renderScene);

    //zmiany rozmiaru okna
    glutReshapeFunc(App::handleInputChangeSize);

    //obs�uga klawiszy specjalnych
    glutSpecialFunc(App::handleInputSpecialKey);
    //obs�uga zwyk�ych klawiszy
    glutKeyboardFunc(App::handelInputKey);
    //obs�uga poruszania si� myszy, gdy przycisk jest trzymany
    glutMotionFunc(App::handleMouseMotion);
    //obs�uga przycisk�w myszy
    glutMouseFunc(App::handleMouse);
    //funckja wywo�ywana gdy nie ma �adnych event�w
    glutIdleFunc(App::idleFunction);
    //kolor czyszcz�cy ekran
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // W��czenie mechanizmu usuwania powierzchni niewidocznych
    glEnable(GL_DEPTH_TEST);

    this->init();
}
//pobranie instancji singletonu
App* App::getInstance()
{
	if (App::instance == nullptr) {
        App::instance = new App();
	}
	return App::instance;
}
//rysowanie sceny
void App::renderScene()
{
    App* app = App::getInstance();
    // Czyszczenie okna aktualnym kolorem czyszcz�cym
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie macierzy bie��cej
    glLoadIdentity();

    //ustawienie kamery
    app->camera->setView();

    //rotacja ca�ego systemu wed�ug podanego inputu
    glRotatef(app->currentRotation.cords[0], 1.0f, 0.0f, 0.0f);
    glRotatef(app->currentRotation.cords[1], 0.0f, 1.0f, 0.0f);
    glRotatef(app->currentRotation.cords[2], 0.0f, 0.0f, 1.0f);
    //rysowanie systemu jajeczenego
    app->mainSystem->draw();

    // Przekazanie polece� rysuj�cych do wykonania
    glFlush();

    //zmiana bufor�w wy�wieltanego i przetwarzanego
    glutSwapBuffers();
}

//metoda obs�ugi klawiszy klawiatury
void App::handelInputKey(unsigned char key, int x, int y)
{
    //pobranie instancji singletonu
    App* app = App::getInstance();
    switch (key) {
    case 'p':
        //wy�wietlanie jajek jako punkty
        app->displayType = DrawType::Point;
        break;
    case 'l':
        //wy�wietlanie jajek jako linie
        app->displayType = DrawType::Line;
        break;
    case 't':
        //wy�wietlanie wype�nionych jajek
        app->displayType = DrawType::Triangle;
        break;
    case ' ':
        //zatrzymanie g��wnego obrotu
        app->rotationDirection = RotationDirection::PAUSE;
        break;
    case 'r':
        //reset pozycji kamery
        app->camera->reset();
        break;
    case '+':
        //przybli�enie
        app->camera->zoom(-CAMERA_MOOV);
        break;
    case '-':
        //przybli�enie
        app->camera->zoom(+CAMERA_MOOV);
        break;
    case 27:
        //wyj�cie z programu esc
        exit(0);
        break;
    }
}
//metoda obs�ugi specjalnych klawiszy klawiatury jak f11
void App::handleInputSpecialKey(int key, int x, int y)
{
    App* app = App::getInstance();
    //je�eli wci�ni�to f11
    switch (key) {
    case GLUT_KEY_F11:
        if (app->isFoolScreen) {
            //powr�t okna
            glutReshapeWindow(WINDOW_SIZE, WINDOW_HEIGHT);
        }
        else {
            //pe�ne okno
            glutFullScreen();
        }
        //zmiana informacji o aktualnym stanie okna
        app->isFoolScreen = !app->isFoolScreen;
        break;
    case GLUT_KEY_DOWN:
        //obr�t jajka pionowo w d�
        app->rotationDirection = RotationDirection::DOWN;
        break;
    case GLUT_KEY_UP:
        //obr�t jajka pionowo w g�r�
        app->rotationDirection = RotationDirection::UP;
        break;
    case GLUT_KEY_LEFT:
        //obr�t jajka poziomo w lewo
        app->rotationDirection = RotationDirection::LEFT;
        break;
    case GLUT_KEY_RIGHT:
        //obr�t jajka poziomo w prawo
        app->rotationDirection = RotationDirection::RIGHT;
        break;
    }
}

//obs�uga zmiany wielko�ci okna
void App::handleInputChangeSize(GLsizei horizontal, GLsizei vertical)
{
    glMatrixMode(GL_PROJECTION);
    // Prze��czenie macierzy bie��cej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bie��cej

    if (vertical == 0) vertical = 1;
    //rzut perspektywiczny
    gluPerspective(70, static_cast<GLdouble>(horizontal)/vertical, 1.0, 100.0);


    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielko�ci okna okna widoku (viewport) w zale�no�ci
    // relacji pomi�dzy wysoko�ci� i szeroko�ci� okna

    glMatrixMode(GL_MODELVIEW);
    // Prze��czenie macierzy bie��cej na macierz widoku modelu  

    glLoadIdentity();
    // Czyszczenie macierzy bie��cej

}
//obs�uga poruszania myszy, gdy przycisk jest trzymany
void App::handleMouseMotion(int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    //ustawienie przesuni�cia obecnego myszy
    app->mouseDeltaX += x - app->mouseX;
    app->mouseDeltaY += y - app->mouseY;
    //ustawienie starej pozycji myszy jako ta aktualna
    app->mouseX = x;
    app->mouseY = y;
}
//obs�uga przycisk�w myszy
void App::handleMouse(int button, int status, int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    switch (button) {
    //je�eli event dotyczy lewogo przycisku
    case GLUT_LEFT:
        //je�eli przycisk jest wciskany
        if (status == GLUT_DOWN) {
            //status wci�ni�cia myszy
            app->mouseStatus = 1;
            //zapisanie obecnej pozycji myszy
            app->mouseX = x;
            app->mouseY = y;
            //ustawienie przesuni�cia myszy na 0
            app->mouseDeltaX = 0;
            app->mouseDeltaY = 0;
        //je�eli lewy przycisk jest puszczany
        }else {
            //ustawienie statu wci�ni�ta myszy
            app->mouseStatus = 0;
        }
        break;
    }
}

//"p�tla g��wna" funckja wywo�ywana gdy nie ma innych ewent�w
void App::idleFunction()
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    //obecny czas
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    //r�nica czasu
    app->dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - app->lastTime).count() / 1000000000.f;
    //przyspianie nowego czasu do starego czasu
    app->lastTime = now;
    //funckja zajmuj�ca si� zmian� stan�w element�w
    app->update();
    //wywo�anie przerysowania
    glutPostRedisplay();
}
//warto�� pseudo losowa <0, 1> je�eli negativ false lub <-1, 1> je�eli negative true
GLfloat App::randGLfloat(bool negative)
{
    if (negative)
        //liczba pseudolosowa z przedzia�u <-1;1>
        return static_cast <GLfloat> (rand() * 2) / static_cast <GLfloat> (RAND_MAX) - 1.f;
    else
        //liczba pseudolosowa z przedzia�u <0;1>
        return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

//obs�uga zmiany stan�w element�w
void App::update()
{
    //o�wierzenie statn�w pozycji systemu g��wnego
    this->mainSystem->update();

    //aktualizacja pozycji kamery
    if (this->mouseStatus == 1) {
        //ziana pozycji kamery
        this->camera->changeViewer(CAM_MULTIPLIER * this->mouseDeltaX, CAM_MULTIPLIER * this->mouseDeltaY);
        //zerowanie przesuni�cia myszy
        this->mouseDeltaX = this->mouseDeltaY = 0;
    }

    //zmiana pozycji osi obrotu g��wnego systemu
    switch (this->rotationDirection) {
    case RotationDirection::DOWN:
        //obr�t pionowo w d�
        this->currentRotation += Vector3<GLfloat>(DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::UP:
        //o� obrotu pionowo w g�r�
        this->currentRotation += Vector3<GLfloat>(-DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::LEFT:
        //o� obrotu poziomo w lewo
        this->currentRotation += Vector3<GLfloat>(0.f, -DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    case RotationDirection::RIGHT:
        //o� obrotu poziomo w prawo
        this->currentRotation += Vector3<GLfloat>(0.f, DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    }
}
void App::init()
{
    //ustawienie warto�ci pocz�tkowej odst�pu czasu
    App::dt = 0.f;
    //ustawienie warto�ci czasu ostatniej klatki
    this->lastTime = std::chrono::high_resolution_clock::now();
    //tworzenie instancji kamery
    this->camera = new Camera();
    //stworzenie nowego jajka (ilo�� szeg��, pozycja, wielko��)
    Egg* egg = new Egg(this->resolution_main, Vector3<GLfloat>(0.f, -3.f, 0.f), Vector3<GLfloat>(0.8f, 0.8f, 0.8f));
    //ustawienie koloru jaka
    egg->setColor(Egg::ColorType::Random);
    //stwoenie "systemu" z centrum jako podane jajko 
    this->mainSystem = new EggSystem(egg, 0.f, 0.f, 0.f);
    //stworzenie jajka obracaj�cego si� w ok� g��wnego jajka 
    egg = new Egg(static_cast<size_t>(this->resolution_main * SMALL_EGG_MULTIPLIER), Vector3<GLfloat>(0.f, -1.f, 0.f), Vector3<GLfloat>(0.3f, 0.3f, 0.3f));
    //ustawienie koloru
    egg->setColor(Egg::ColorType::Green);
    //stworzenie systemu w kt�rym jajko si� znajduje (jajko, promie�, obr�t wok� w�asnej osi na sekund�, obr�t w ok� promienia na sekund�) i dodanie go do listy system�w g��wnego systemu
    this->mainSystem->push(new EggSystem(egg, 7.f, -40.f, 15.f));

    //w zwi�zku z sposobem, w jaki s� tworzone systemy jajek i jaka, mo�liwe jest dodanie wielu system�w w wielu systemach, kt�re kr��� w ok� siebie
}
//desturktor
App::~App()
{
    delete this->mainSystem;
    delete this->camera;
}
