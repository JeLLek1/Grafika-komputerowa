#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include "App.h"

//instancja singletonu
App* App::instance = nullptr;

//konstruktor
App::App() {
    //GLUT_DOUBLE - tryb podwójnie buforowanego okna
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //ustawienie wartoœci pocz¹tkowych okna
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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
    //obs³uga klawiszy myszy
    glutMouseFunc(App::handleMouse);
    //obs³uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wciœniêty
    glutMotionFunc(App::hangleMouseMotion);
    //funckja wywo³ywana gdy nie ma ¿adnych eventów
    glutIdleFunc(App::idleFunction);
    //kolor czyszcz¹cy ekran
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    
    //zmiana macierzy obserwatora
    glOrtho(-1.f, 1.f, -1.f, 1.f, 0.f, 1.f);

    //w³¹czenie mechanizmu teksturowania
    glEnable(GL_TEXTURE_2D);

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
    glClear(GL_COLOR_BUFFER_BIT);
    // Czyszczenie macierzy bie¿¹cej
    glLoadIdentity();

    //rysowanie fraktalu
    app->fractal->draw();

    // Przekazanie poleceñ rysuj¹cych do wykonania
    glFlush();

    //zmiana buforów wyœwieltanego i przetwarzanego
    glutSwapBuffers();
}

//obs³uga przyciskó
void App::handelInputKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        //wyjœcie z programu esc
        exit(0);
        break;
    }
}

void App::handleInputSpecialKey(int key, int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    switch (key) {
    //je¿eli wciœniêto f11
    case GLUT_KEY_F11:
        if (app->isFoolScreen) {
            //powrót okna
            glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        else {
            //pe³ne okno
            glutFullScreen();
        }
        //zmiana informacji o aktualnym stanie okna
        app->isFoolScreen = !app->isFoolScreen;
        break;
    }
}

//obs³uga zmiany wielkoœci okna
void App::handleInputChangeSize(GLsizei horizontal, GLsizei vertical)
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    // Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna
    GLfloat AspectRatio;

    // Zabezpieczenie pzred dzieleniem przez 0
    if (vertical == 0)
        vertical = 1;

    // Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)
    glViewport(0, 0, horizontal, vertical);

    //zmiana rozmiaru fraktalu
    app->fractal->resize(static_cast<size_t>(horizontal), static_cast<size_t>(vertical));
}
//obs³uga przycisków myszy
void App::handleMouse(int button, int state, int x, int y)
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    switch (button)
    {
    //lewy przycisk myszy
    case GLUT_LEFT_BUTTON:
        //je¿eli wczeœniej nie by³ wciœniêty ¿aden klawisz, a lewy przycisk zosta³ wciœniêty
        if (state == GLUT_DOWN && app->mouseStatus==0) {
            //tryb przybli¿ania
            app->mouseStatus = -1;
        //je¿eli wciœniêty by³ lewy przycisk myszy
        }else if(app->mouseStatus==-1){
            //brak przybli¿ania
            app->mouseStatus = 0;
        }
        break;
    //prawy przycisk myszy
    case GLUT_RIGHT_BUTTON:
        //je¿eli wczeœniej nie by³ wciœniêty ¿aden klawisz, a prawy przycisk zosta³ wciœniêty
        if (state == GLUT_DOWN && app->mouseStatus == 0) {
            //tryb oddalania
            app->mouseStatus = 1;
        //je¿eli wciœniêty by³ prawy przycisk myszy
        }else if(app->mouseStatus == 1){
            //brak oddalania
            app->mouseStatus = 0;
        }
        break;
    }
    //pobranie aktualnej pozycji myszy
    app->mouseX = x;
    app->mouseY = y;
}

//obs³uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wciœniêty
void App::hangleMouseMotion(int x, int y)
{
    //pobrani instancji aplikacji
    App* app = App::getInstance();
    //pobranie aktualnej pozycji myszy
    app->mouseX = x;
    app->mouseY = y;
}

//"pêtla g³ówna" funckja wywo³ywana gdy nie ma innych ewentów
void App::idleFunction()
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    //obecny czas
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    //ró¿nica czasu
    app->dt = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - app->lastTime).count()) / 1000000000;
    //przyspianie nowego czasu do starego czasu
    app->lastTime = now;
    //funckja zajmuj¹ca siê zmian¹ stanów elementów
    app->update();
    //wywo³anie przerysowania
    glutPostRedisplay();
}
//obs³uga zmiany stanów elementów
void App::update()
{
    if (this->mouseStatus) {
        this->fractal->zoom(this->dt * this->mouseStatus, this->mouseX, this->mouseY);
    }
    this->fractal->update();
}
void App::init()
{
    //ustawienie wartoœci pocz¹tkowej odstêpu czasu
    App::dt = 0.f;
    //ustawienie wartoœci czasu ostatniej klatki
    this->lastTime = std::chrono::high_resolution_clock::now();
    //inicjalizacja fraktalu
    this->fractal = new Mandelbrot(static_cast<size_t>(glutGet(GLUT_WINDOW_WIDTH)), static_cast<size_t>(glutGet(GLUT_WINDOW_HEIGHT)));
}
//desturktor
App::~App()
{
    delete this->fractal;
    App::instance = nullptr;
}
