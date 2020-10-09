/*
settings.h - wszystkie opcje domyślnie programu
Obsługa programu:
[+/-] - zmienianie przybliżenia
[strzałki] - przesuwanie pozycji fraktalu
[a/d] - zmiana poziomu perturbacji
[w/s] - zmiana poziomu rystowania fraktalu
*/

#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <stdarg.h> 
#include <list> 
#include <iterator> 
#include "settings.h"
#include "SierpinskiCarpet.h"

//stan okna
static bool is_fullscrean = false;
//pozycja względna fraktalu
static GLfloat pos_x = 0.f;
static GLfloat pos_y = 0.f;
//poziom perturbacji
static GLfloat noise = DEF_NOISE;
//poziom fraktalu
static size_t last_level = DEF_LEVEL;
//wskaźnik klasy dywanu Sierpińskiego
static SierpinskiCarpet* carpet = nullptr;
//przybliżenie fraktalu
static GLfloat size = CARPET_SIZE;

//inicjalizacja/reinicjalizacja dywanu Sierpińskiego
//reinicjalizacja następuje gdy następuje zmiana parametrów (poziom,perturbacje)
void carpetInit() {
    if (carpet != nullptr) {
        delete carpet;
    }
    //tworzenie dywanu Sierpińskiego według danych defaultowych
    carpet = new SierpinskiCarpet(CARPET_X, CARPET_Y, CARPET_SIZE, last_level,noise);
    //przybliżenie według aktualnych ustawień
    carpet->zoom(size - CARPET_SIZE);
    carpet->moov(pos_x, pos_y);
}

//generowanie pseudolosowej liczby zmiennoprzecinkowej <0;1> lub <-1;1>
float randGLfloat(bool negative = false) {
    if(negative)
        //liczba pseudolosowa z przedziału <-1;1>
        return static_cast <GLfloat> (rand() * 2) / static_cast <GLfloat> (RAND_MAX) - 1.f;
    else
        //liczba pseudolosowa z przedziału <0;1>
        return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

//Rysowanie poligonu z podanych punktów o podanej ilości punktów
void drawSierpinskiCarpet() {

    //Dla wszystkich kwadratów
    std::list <Square*> ::iterator it;
    for (it = carpet->squares->begin(); it != carpet->squares->end(); ++it) {
        //rozpoczęcie rysowania poligonu
        glBegin(GL_POLYGON);
        //dla każdego punktu z tablicy pt
        for (size_t j = 0; j < 4; j++) {
            //Ustawianie koloru wierzchołka
            glColor3f((*it)->points[j]->r, (*it)->points[j]->g, (*it)->points[j]->b);
            //Wyświetlanie wierzchołka i perturbacje według aktualnych ustawień programu
            glVertex2f((*it)->points[j]->x, (*it)->points[j]->y);
        }
        //zakończenie rysowania poligonu
        glEnd();
    }
}

//Funkcja rywująca tekst na ekranie wraz ze zmiennymi
void display_setting_text(GLfloat x, GLfloat y, const char *string, ...) {
    //ustawienie koloru czcionki na biały
    glColor3f(1.f, 1.f, 1.f);
    //ustawienie pozycji tesktu
    glRasterPos2f(x, y);
    //lista argumentów, wstrzykiwanie do ciągu znaków
    va_list st;
    va_start(st, string);
    char bofor[126];
    vsprintf_s(bofor, string, st);
    va_end(st);
    //wyświetlanie znak po znaku tekstu na ektranie
    for (size_t i = 0; i < strlen(bofor); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bofor[i]);
    }
}

//rysowanie gui
void drawGui() {
    //informacja o perturbacjach
    display_setting_text(-100.f, 90.f, "Poziom zniekształcenia: %1.1f", noise);
    //ifnrmacja o ilości poziomów
    display_setting_text(-100.f, 85.f, "Poziomy fraktalu: %u", last_level);
    //Iformacja o przyciskach
    display_setting_text(-100.f, -90.f, "Dostepne klawisze: [w,a,s,d,+,-,(arrows)]");
}

// Funkcaja określająca, co ma być rysowane
void RenderScene(void) {

    // Czyszczenie okna aktualnym kolorem czyszczącym
    glClear(GL_COLOR_BUFFER_BIT);

    //wywołanie metody rysującej dywan
    drawSierpinskiCarpet();
    //rysowanie gui
    drawGui();

    // Przekazanie poleceń rysujących do wykonania
    glFlush();

}

// Funkcja ustalająca stan renderowania
void MyInit()
{
    // Kolor okna wnętrza okna - ustawiono na czarny
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    //inicjalizacja dywanu sierpińskiego
    carpetInit();
}

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
    // ustawienie aspect ration do odwołania dla testu czy element jest widoczny
    if (horizontal <= vertical) {
        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
    }
    else {
        glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);
    }

    // Określenie układu współrzędnych    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//funckja wywoływana podczas użycia specjalnych klawiszy
void keySpecialFunction(int key, int x, int y) {
    //jeżeli wciśnięto f11
    switch(key){
    case GLUT_KEY_F11:
        if (is_fullscrean) {
            //powrót okna
            glutReshapeWindow(WINDOW_SIZE, WINDOW_HEIGHT);
        }
        else {
            //pełne okno
            glutFullScreen();
        }
        //zmiana informacji o aktualnym stanie okna
        is_fullscrean = !is_fullscrean;
        break;
    case GLUT_KEY_DOWN:
        //przesunięcie fraktalu w górę
        carpet->moov(0, DEF_STEP_MOOV);
        pos_y += DEF_STEP_MOOV;
        break;
    case GLUT_KEY_UP:
        //przesunięcie fraktalu w dół
        carpet->moov(0, -DEF_STEP_MOOV);
        pos_y -= DEF_STEP_MOOV;
        break;
    case GLUT_KEY_LEFT:
        //przesunięcie fraktalu w prawo
        carpet->moov(DEF_STEP_MOOV, 0);
        pos_x += DEF_STEP_MOOV;
        break;
    case GLUT_KEY_RIGHT:
        //przesunięcie fraktalu w lewo
        carpet->moov(-DEF_STEP_MOOV, 0);
        pos_x -= DEF_STEP_MOOV;
        break;
    }
    //przerysowanie
    glutPostRedisplay();
}

//funkcja wywoływana podczas użycia normalnych klawiszy
void keyNormalFunction(unsigned char key, int x, int y) {
    switch (key) {
        case 43:
            //powiększenie [+]
            carpet->zoom(DEF_STEP_ZOOM);
            //w zmiennych pomocniczyć należy przetworzyć proporcje nowego zoomu dla pozycji, żeby po ewentualnej reinicjalizacji dało się odczytać starą pozycję
            size += size/100.f * DEF_STEP_ZOOM;
            pos_x += pos_x / 100.f * DEF_STEP_ZOOM;
            pos_y += pos_y / 100.f * DEF_STEP_ZOOM;
            break;
        case 45:
            //pomniejszenie [-]
            carpet->zoom(-DEF_STEP_ZOOM);
            //w zmiennych pomocniczyć należy przetworzyć proporcje nowego zoomu dla pozycji, żeby po ewentualnej reinicjalizacji dało się odczytać starą pozycję
            size -= size / 100.f * DEF_STEP_ZOOM;
            pos_x -= pos_x / 100.f * DEF_STEP_ZOOM;
            pos_y -= pos_y / 100.f * DEF_STEP_ZOOM;
            break;
        case 97:
            //zwiększenie poziomu parturbacji [d]
            if (noise > 0.f) {
                noise -= DEF_NOISE_STEP;
                if (noise < 0.f) noise = 0.f;
                carpetInit();
            }
            break;
        case 100:
            //zmniejszenie poziomu parturbacji [a]
            noise += DEF_NOISE_STEP;
            carpetInit();
            break;
        case 119:
            //zwiększenie poziomu fraktalu [w]
            last_level++;
            carpetInit();
            break;
        case 115:
            //zmniejszenie poziomu fraktalu [s]
            if (last_level > 1) {
                last_level--;
                carpetInit();
            }
            break;
        case 27:
            //wyjście z programu esc
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main() {

    // Ustawienie trybu wyświetlania
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(WINDOW_SIZE, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    // Utworzenie okna i określenie treści napisu w nagłówku okna
    glutCreateWindow(APP_NAME);;

    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    glutDisplayFunc(RenderScene);

    //zmiany rozmiaru okna
    glutReshapeFunc(ChangeSize);

    //obsługa klawiszy specjalnych
    glutSpecialFunc(keySpecialFunction);
    //obsługa zwykłych klawiszy
    glutKeyboardFunc(keyNormalFunction);

    //inicjalizacja
    MyInit();

    // Funkcja uruchamia szkielet biblioteki GLUT
    glutMainLoop();

    return 0;
}