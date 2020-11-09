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
    //pobranie rozdzielczoœci z okna
    printf("Podaj rozdzielczosc jajka glownego (drugie jajko zostanie wygenerowanie z %1.1f razy mniejsza iloscia punktow): ", 1/SMALL_EGG_MULTIPLIER);
    scanf_s("%u", &this->resolution_main);
    //pobieranie dopóki wartoœc nie bêdzie poprawna
    while (this->resolution_main < MIN_EGG_POINT_COUNT) {
        //czyszczenie buforu
        char c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        //pobranie informacji ponowanie
        printf("Uwaga! Glowne jajko musi miec przynajmniej rodzielczosc %u. Podaj rozdzielczosc ponownie: ", MIN_EGG_POINT_COUNT);
        scanf_s("%u", &this->resolution_main);
    }

    std::srand(std::time(NULL));
    //GLUT_DOUBLE - tryb podwójnie buforowanego okna
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //ustawienie wartoœci pocz¹tkowych okna
    glutInitWindowSize(WINDOW_SIZE, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    // Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna
    glutCreateWindow(APP_NAME);;

    // Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
    glutDisplayFunc(App::renderScene);

    //zmiany rozmiaru okna
    glutReshapeFunc(App::handleInputChangeSize);

    //obs³uga klawiszy specjalnych
    glutSpecialFunc(App::handleInputSpecialKey);
    //obs³uga zwyk³ych klawiszy
    glutKeyboardFunc(App::handelInputKey);
    //obs³uga poruszania siê myszy, gdy przycisk jest trzymany
    glutMotionFunc(App::handleMouseMotion);
    //obs³uga przycisków myszy
    glutMouseFunc(App::handleMouse);
    //funckja wywo³ywana gdy nie ma ¿adnych eventów
    glutIdleFunc(App::idleFunction);
    //kolor czyszcz¹cy ekran
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // W³¹czenie mechanizmu usuwania powierzchni niewidocznych
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
    // Czyszczenie okna aktualnym kolorem czyszcz¹cym
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie macierzy bie¿¹cej
    glLoadIdentity();

    //ustawienie kamery
    app->camera->setView();

    //rotacja ca³ego systemu wed³ug podanego inputu
    glRotatef(app->currentRotation.cords[0], 1.0f, 0.0f, 0.0f);
    glRotatef(app->currentRotation.cords[1], 0.0f, 1.0f, 0.0f);
    glRotatef(app->currentRotation.cords[2], 0.0f, 0.0f, 1.0f);
    //rysowanie systemu jajeczenego
    app->mainSystem->draw();

    // Przekazanie poleceñ rysuj¹cych do wykonania
    glFlush();

    //zmiana buforów wyœwieltanego i przetwarzanego
    glutSwapBuffers();
}

//metoda obs³ugi klawiszy klawiatury
void App::handelInputKey(unsigned char key, int x, int y)
{
    //pobranie instancji singletonu
    App* app = App::getInstance();
    switch (key) {
    case 'p':
        //wyœwietlanie jajek jako punkty
        app->displayType = DrawType::Point;
        break;
    case 'l':
        //wyœwietlanie jajek jako linie
        app->displayType = DrawType::Line;
        break;
    case 't':
        //wyœwietlanie wype³nionych jajek
        app->displayType = DrawType::Triangle;
        break;
    case ' ':
        //zatrzymanie g³ównego obrotu
        app->rotationDirection = RotationDirection::PAUSE;
        break;
    case 'r':
        //reset pozycji kamery
        app->camera->reset();
        break;
    case '+':
        //przybli¿enie
        app->camera->zoom(-CAMERA_MOOV);
        break;
    case '-':
        //przybli¿enie
        app->camera->zoom(+CAMERA_MOOV);
        break;
    case 27:
        //wyjœcie z programu esc
        exit(0);
        break;
    }
}
//metoda obs³ugi specjalnych klawiszy klawiatury jak f11
void App::handleInputSpecialKey(int key, int x, int y)
{
    App* app = App::getInstance();
    //je¿eli wciœniêto f11
    switch (key) {
    case GLUT_KEY_F11:
        if (app->isFoolScreen) {
            //powrót okna
            glutReshapeWindow(WINDOW_SIZE, WINDOW_HEIGHT);
        }
        else {
            //pe³ne okno
            glutFullScreen();
        }
        //zmiana informacji o aktualnym stanie okna
        app->isFoolScreen = !app->isFoolScreen;
        break;
    case GLUT_KEY_DOWN:
        //obrót jajka pionowo w dó³
        app->rotationDirection = RotationDirection::DOWN;
        break;
    case GLUT_KEY_UP:
        //obrót jajka pionowo w górê
        app->rotationDirection = RotationDirection::UP;
        break;
    case GLUT_KEY_LEFT:
        //obrót jajka poziomo w lewo
        app->rotationDirection = RotationDirection::LEFT;
        break;
    case GLUT_KEY_RIGHT:
        //obrót jajka poziomo w prawo
        app->rotationDirection = RotationDirection::RIGHT;
        break;
    }
}

//obs³uga zmiany wielkoœci okna
void App::handleInputChangeSize(GLsizei horizontal, GLsizei vertical)
{
    glMatrixMode(GL_PROJECTION);
    // Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bie¿¹cej

    if (vertical == 0) vertical = 1;
    //rzut perspektywiczny
    gluPerspective(70, static_cast<GLdouble>(horizontal)/vertical, 1.0, 100.0);


    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
    // relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

    glMatrixMode(GL_MODELVIEW);
    // Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

    glLoadIdentity();
    // Czyszczenie macierzy bie¿¹cej

}
//obs³uga poruszania myszy, gdy przycisk jest trzymany
void App::handleMouseMotion(int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    //ustawienie przesuniêcia obecnego myszy
    app->mouseDeltaX += x - app->mouseX;
    app->mouseDeltaY += y - app->mouseY;
    //ustawienie starej pozycji myszy jako ta aktualna
    app->mouseX = x;
    app->mouseY = y;
}
//obs³uga przycisków myszy
void App::handleMouse(int button, int status, int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    switch (button) {
    //je¿eli event dotyczy lewogo przycisku
    case GLUT_LEFT:
        //je¿eli przycisk jest wciskany
        if (status == GLUT_DOWN) {
            //status wciœniêcia myszy
            app->mouseStatus = 1;
            //zapisanie obecnej pozycji myszy
            app->mouseX = x;
            app->mouseY = y;
            //ustawienie przesuniêcia myszy na 0
            app->mouseDeltaX = 0;
            app->mouseDeltaY = 0;
        //je¿eli lewy przycisk jest puszczany
        }else {
            //ustawienie statu wciæniêta myszy
            app->mouseStatus = 0;
        }
        break;
    }
}

//"pêtla g³ówna" funckja wywo³ywana gdy nie ma innych ewentów
void App::idleFunction()
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    //obecny czas
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    //ró¿nica czasu
    app->dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - app->lastTime).count() / 1000000000.f;
    //przyspianie nowego czasu do starego czasu
    app->lastTime = now;
    //funckja zajmuj¹ca siê zmian¹ stanów elementów
    app->update();
    //wywo³anie przerysowania
    glutPostRedisplay();
}
//wartoœæ pseudo losowa <0, 1> je¿eli negativ false lub <-1, 1> je¿eli negative true
GLfloat App::randGLfloat(bool negative)
{
    if (negative)
        //liczba pseudolosowa z przedzia³u <-1;1>
        return static_cast <GLfloat> (rand() * 2) / static_cast <GLfloat> (RAND_MAX) - 1.f;
    else
        //liczba pseudolosowa z przedzia³u <0;1>
        return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

//obs³uga zmiany stanów elementów
void App::update()
{
    //oœwierzenie statnów pozycji systemu g³ównego
    this->mainSystem->update();

    //aktualizacja pozycji kamery
    if (this->mouseStatus == 1) {
        //ziana pozycji kamery
        this->camera->changeViewer(CAM_MULTIPLIER * this->mouseDeltaX, CAM_MULTIPLIER * this->mouseDeltaY);
        //zerowanie przesuniêcia myszy
        this->mouseDeltaX = this->mouseDeltaY = 0;
    }

    //zmiana pozycji osi obrotu g³ównego systemu
    switch (this->rotationDirection) {
    case RotationDirection::DOWN:
        //obrót pionowo w dó³
        this->currentRotation += Vector3<GLfloat>(DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::UP:
        //oœ obrotu pionowo w górê
        this->currentRotation += Vector3<GLfloat>(-DEF_ROTATION_STEP * this->dt, 0.f, 0.f);
        break;
    case RotationDirection::LEFT:
        //oœ obrotu poziomo w lewo
        this->currentRotation += Vector3<GLfloat>(0.f, -DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    case RotationDirection::RIGHT:
        //oœ obrotu poziomo w prawo
        this->currentRotation += Vector3<GLfloat>(0.f, DEF_ROTATION_STEP * this->dt, 0.f);
        break;
    }
}
void App::init()
{
    //ustawienie wartoœci pocz¹tkowej odstêpu czasu
    App::dt = 0.f;
    //ustawienie wartoœci czasu ostatniej klatki
    this->lastTime = std::chrono::high_resolution_clock::now();
    //tworzenie instancji kamery
    this->camera = new Camera();
    //stworzenie nowego jajka (iloœæ szegó³ó, pozycja, wielkoœæ)
    Egg* egg = new Egg(this->resolution_main, Vector3<GLfloat>(0.f, -3.f, 0.f), Vector3<GLfloat>(0.8f, 0.8f, 0.8f));
    //ustawienie koloru jaka
    egg->setColor(Egg::ColorType::Random);
    //stwoenie "systemu" z centrum jako podane jajko 
    this->mainSystem = new EggSystem(egg, 0.f, 0.f, 0.f);
    //stworzenie jajka obracaj¹cego siê w okó³ g³ównego jajka 
    egg = new Egg(static_cast<size_t>(this->resolution_main * SMALL_EGG_MULTIPLIER), Vector3<GLfloat>(0.f, -1.f, 0.f), Vector3<GLfloat>(0.3f, 0.3f, 0.3f));
    //ustawienie koloru
    egg->setColor(Egg::ColorType::Green);
    //stworzenie systemu w którym jajko siê znajduje (jajko, promieñ, obrót wokó³ w³asnej osi na sekundê, obrót w okó³ promienia na sekundê) i dodanie go do listy systemów g³ównego systemu
    this->mainSystem->push(new EggSystem(egg, 7.f, -40.f, 15.f));

    //w zwi¹zku z sposobem, w jaki s¹ tworzone systemy jajek i jaka, mo¿liwe jest dodanie wielu systemów w wielu systemach, które kr¹¿¹ w okó³ siebie
}
//desturktor
App::~App()
{
    delete this->mainSystem;
    delete this->camera;
}
