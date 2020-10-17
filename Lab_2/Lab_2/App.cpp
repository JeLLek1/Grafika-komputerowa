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
    //funckja wywo�ywana gdy nie ma �adnych event�w
    glutIdleFunc(App::idleFunction);
    //czyszczenie ekranu
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // W��czenie mechanizmu usuwania powierzchni niewidocznych
    glEnable(GL_DEPTH_TEST);

    //ustawienie warto�ci pocz�tkowej odst�pu czasu
    App::dt = 0.f;
    //ustawienie warto�ci czasu ostatniej klatki
    this->lastTime = std::chrono::high_resolution_clock::now();
    //stworzenie nowego jajka (ilo�� szeg��, pozycja, wielko��)
    Egg* egg = new Egg(this->resolution_main, Vector3f(0.f, -3.f, 0.f), Vector3f(0.8f, 0.8f, 0.8f));
    //ustawienie koloru jaka
    egg->setColor(Egg::ColorType::Random);
    //stwoenie "systemu" z centrum jako podane jajko 
    this->mainSystem = new EggSystem(egg, 0.f, 0.f, 0.f);
    //stworzenie jajka obracaj�cego si� w ok� g��wnego jajka 
    egg = new Egg(static_cast<size_t>(this->resolution_main*SMALL_EGG_MULTIPLIER), Vector3f(0.f, -1.f, 0.f), Vector3f(0.3f, 0.3f, 0.3f));
    //ustawienie koloru
    egg->setColor(Egg::ColorType::Green);
    //stworzenie systemu w kt�rym jajko si� znajduje (jajko, promie�, obr�t wok� w�asnej osi na sekund�, obr�t w ok� promienia na sekund�) i dodanie go do listy system�w g��wnego systemu
    this->mainSystem->push(new EggSystem(egg, 7.f, -40.f, 10.f));

    //w zwi�zku z sposobem, w jaki s� tworzone systemy jajek i jaka, mo�liwe jest dodanie wielu system�w w wielu systemach, kt�re kr��� w ok� siebie
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

//obs�uga przycisk�
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
    case 27:
        //wyj�cie z programu esc
        exit(0);
        break;
    }
}

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
    // Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna
    GLfloat AspectRatio;

    // Zabezpieczenie pzred dzieleniem przez 0
    if (vertical == 0)
        vertical = 1;

    // Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)
    glViewport(0, 0, horizontal, vertical);

    // Okre�lenie uk�adu wsp�rz�dnych obserwatora
    glMatrixMode(GL_PROJECTION);

    // Okre�lenie przestrzeni ograniczaj�cej
    glLoadIdentity();

    // Wyznaczenie wsp�czynnika proporcji okna
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // okre�lenie okna obserwatora.
    // Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
    // Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)
    // ustawienie aspect ration do odwo�ania dla testu czy element jest widoczny
    if (horizontal <= vertical) {
        //zapisywanie wsp�czynnik�w ekranu
        glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 30.0, -30.0);
    }
    else {
        //zapisywanie wsp�czynnik�w ekranu
        glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 30.0, -30.0);
    }

    // Okre�lenie uk�adu wsp�rz�dnych    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    //pobranie instancji obiektu aplikacji
    App* app = App::getInstance();
    //o�wierzenie statn�w pozycji systemu g��wnego
    this->mainSystem->update();

    //zmiana pozycji osi obrotu g��wnego systemu
    switch (this->rotationDirection) {
    case RotationDirection::DOWN:
        //obr�t pionowo w d�
        app->currentRotation += Vector3f(-DEF_ROTATION_STEP * app->dt);
        break;
    case RotationDirection::UP:
        //o� obrotu pionowo w g�r�
        app->currentRotation += Vector3f(DEF_ROTATION_STEP * app->dt);
        break;
    case RotationDirection::LEFT:
        //o� obrotu poziomo w lewo
        app->currentRotation += Vector3f(0.f, -DEF_ROTATION_STEP * app->dt);
        break;
    case RotationDirection::RIGHT:
        //o� obrotu poziomo w prawo
        app->currentRotation += Vector3f(0.f, DEF_ROTATION_STEP * app->dt);
        break;
    }
}
//desturktor
App::~App()
{
    delete this->mainSystem;
}
