#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include "App.h"

//instancja singletonu
App* App::instance = nullptr;

//konstruktor
App::App() {
    //GLUT_DOUBLE - tryb podw�jnie buforowanego okna
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //ustawienie warto�ci pocz�tkowych okna
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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
    //obs�uga klawiszy myszy
    glutMouseFunc(App::handleMouse);
    //obs�uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wci�ni�ty
    glutMotionFunc(App::hangleMouseMotion);
    //funckja wywo�ywana gdy nie ma �adnych event�w
    glutIdleFunc(App::idleFunction);
    //kolor czyszcz�cy ekran
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    
    //zmiana macierzy obserwatora
    glOrtho(-1.f, 1.f, -1.f, 1.f, 0.f, 1.f);

    //w��czenie mechanizmu teksturowania
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
    // Czyszczenie okna aktualnym kolorem czyszcz�cym
    glClear(GL_COLOR_BUFFER_BIT);
    // Czyszczenie macierzy bie��cej
    glLoadIdentity();

    //rysowanie fraktalu
    app->fractal->draw();

    // Przekazanie polece� rysuj�cych do wykonania
    glFlush();

    //zmiana bufor�w wy�wieltanego i przetwarzanego
    glutSwapBuffers();
}

//obs�uga przycisk�
void App::handelInputKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        //wyj�cie z programu esc
        exit(0);
        break;
    }
}

void App::handleInputSpecialKey(int key, int x, int y)
{
    //pobranie instancji aplikacji
    App* app = App::getInstance();
    switch (key) {
    //je�eli wci�ni�to f11
    case GLUT_KEY_F11:
        if (app->isFoolScreen) {
            //powr�t okna
            glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        else {
            //pe�ne okno
            glutFullScreen();
        }
        //zmiana informacji o aktualnym stanie okna
        app->isFoolScreen = !app->isFoolScreen;
        break;
    }
}

//obs�uga zmiany wielko�ci okna
void App::handleInputChangeSize(GLsizei horizontal, GLsizei vertical)
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    // Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna
    GLfloat AspectRatio;

    // Zabezpieczenie pzred dzieleniem przez 0
    if (vertical == 0)
        vertical = 1;

    // Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)
    glViewport(0, 0, horizontal, vertical);

    //zmiana rozmiaru fraktalu
    app->fractal->resize(static_cast<size_t>(horizontal), static_cast<size_t>(vertical));
}
//obs�uga przycisk�w myszy
void App::handleMouse(int button, int state, int x, int y)
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    switch (button)
    {
    //lewy przycisk myszy
    case GLUT_LEFT_BUTTON:
        //je�eli wcze�niej nie by� wci�ni�ty �aden klawisz, a lewy przycisk zosta� wci�ni�ty
        if (state == GLUT_DOWN && app->mouseStatus==0) {
            //tryb przybli�ania
            app->mouseStatus = -1;
        //je�eli wci�ni�ty by� lewy przycisk myszy
        }else if(app->mouseStatus==-1){
            //brak przybli�ania
            app->mouseStatus = 0;
        }
        break;
    //prawy przycisk myszy
    case GLUT_RIGHT_BUTTON:
        //je�eli wcze�niej nie by� wci�ni�ty �aden klawisz, a prawy przycisk zosta� wci�ni�ty
        if (state == GLUT_DOWN && app->mouseStatus == 0) {
            //tryb oddalania
            app->mouseStatus = 1;
        //je�eli wci�ni�ty by� prawy przycisk myszy
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

//obs�uga przesuwania myszy, kiedy przynajmniej jeden przycisk jest wci�ni�ty
void App::hangleMouseMotion(int x, int y)
{
    //pobrani instancji aplikacji
    App* app = App::getInstance();
    //pobranie aktualnej pozycji myszy
    app->mouseX = x;
    app->mouseY = y;
}

//"p�tla g��wna" funckja wywo�ywana gdy nie ma innych ewent�w
void App::idleFunction()
{
    //pobranie instancji obiektu aplikcaji
    App* app = App::getInstance();
    //obecny czas
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    //r�nica czasu
    app->dt = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - app->lastTime).count()) / 1000000000;
    //przyspianie nowego czasu do starego czasu
    app->lastTime = now;
    //funckja zajmuj�ca si� zmian� stan�w element�w
    app->update();
    //wywo�anie przerysowania
    glutPostRedisplay();
}
//obs�uga zmiany stan�w element�w
void App::update()
{
    if (this->mouseStatus) {
        this->fractal->zoom(this->dt * this->mouseStatus, this->mouseX, this->mouseY);
    }
    this->fractal->update();
}
void App::init()
{
    //ustawienie warto�ci pocz�tkowej odst�pu czasu
    App::dt = 0.f;
    //ustawienie warto�ci czasu ostatniej klatki
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
