#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <time.h> 
#include "settings.h"

//stan okna
static bool is_fullscrean = false;

//generowanie pseudolosowej liczby zmiennoprzecinkowej <0;1>
float randFloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

//Rysowanie poligonu
void drawPoligon() {

}

// Funkcaja określająca, co ma być rysowane
void RenderScene(void) {

    // Czyszczenie okna aktualnym kolorem czyszczącym
    glClear(GL_COLOR_BUFFER_BIT);
    // Ustawienie aktualnego koloru rysowania na zielony
    glColor3f(0.0f, 1.0f, 0.0f);

    // Narysowanie prostokąta
    glRectf(-50.0f, 50.0f, 50.0f, -50.0f);

    // Przekazanie poleceń rysujących do wykonania
    glFlush();

}

// Funkcja ustalająca stan renderowania
void MyInit(void)
{
    // Kolor okna wnętrza okna - ustawiono na szary
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

/*************************************************************************************/

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
void ChangeSize(GLsizei horizontal, GLsizei vertical) {

    // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna
    GLfloat AspectRatio;

    // Zabezpieczenie pzred dzieleniem przez 0
    if (vertical == 0)
        vertical = 1;

    // Ustawienie wielkościokna okna urządzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)
    glViewport(0, 0, horizontal, vertical);

    // Określenie układu współrzędnych obserwatora
    glMatrixMode(GL_PROJECTION);

    // Określenie przestrzeni ograniczającej
    glLoadIdentity();

    // Wyznaczenie współczynnika proporcji okna
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // określenie okna obserwatora.
    // Pozwala to zachować właściwe proporcje rysowanego obiektu
    // Do określenia okna obserwatora służy funkcja glOrtho(...)
    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);

    // Określenie układu współrzędnych    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//funckja wywoływana podczas użycia specjalnych klawiszy
void keySpecialFunction(int key, int x, int y) {
    if (key == GLUT_KEY_F11) {
        if (is_fullscrean) {
            //powrót okna
            glutReshapeWindow(WINDOW_SIZE, WINDOW_HEIGHT);
        }
        else {
            //pełne okno
            glutFullScreen();
        }
        is_fullscrean = !is_fullscrean;
    }
}

//funkcja wywoływana podczas użycia normalnych klawiszy
void keyNormalFunction(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

void main(void) {

    // Ustawienie trybu wyświetlania
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(WINDOW_SIZE, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    // Utworzenie okna i określenie treści napisu w nagłówku okna
    glutCreateWindow("Lab 1");;

    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    glutDisplayFunc(RenderScene);

    //zmiany rozmiaru okna
    glutReshapeFunc(ChangeSize);

    //obsługa klawiszy specjalnych
    glutSpecialFunc(keySpecialFunction);
    glutKeyboardFunc(keyNormalFunction);

    //inicjalizacja
    MyInit();

    // Funkcja uruchamia szkielet biblioteki GLUT
    glutMainLoop();
}