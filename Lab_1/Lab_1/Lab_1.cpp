/*
settings.h - wszystkie opcje domyślnie programu
Obsługa programu:
[+/-] - zmienianie przybliżenia
[strzałki] - przesuwanie pozycji fraktalu
[a/d] - zmiana poziomu perturbacji
[w/s] - zmiana poziomu rystowania fraktalu
[p] -   czy wyświetlać tylko widoczne elementy na ekranie
        pozwala na generowanie dużych struktur po odpowiednim przybliżeniu
        jednak z powodu tego że perturbacje i kolor są losowe na podstawie ziarna
        pomijanie wyświetlania elementów może powodować zmianę tych wartości podczas przybliżania/przesuwania
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
#include <new>
#include "settings.h"

//stan okna
static bool is_fullscrean = false;
//pozycja względna fraktalu
static GLfloat pos_x = CARPET_X;
static GLfloat pos_y = CARPET_Y;
//poziom perturbacji
static GLfloat noise = DEF_NOISE;
//poziom fraktalu
static size_t last_level = DEF_LEVEL;
//przybliżenie fraktalu
static GLfloat size = CARPET_SIZE;

//seed zapamiętany, aby nie zmieniały się elementy podczas przerysowania
static time_t seed = 0;

//współczynnik perturbacji zależny od odległośi i wielkości fraktalu
static GLfloat noise_factor = 0;

//aktualne wpspółczynniki ekranu
static GLfloat screenWidth = 0.f;
static GLfloat screenHeight = 0.f;

//czy pomijanie wyświetlania elementów niewidocznych jest aktywne
static bool show_visible = DEF_SHOW_VISIBLE;

//generowanie pseudolosowej liczby zmiennoprzecinkowej <0;1> lub <-1;1>
GLfloat randGLfloat(bool negative = false) {
    if(negative)
        //liczba pseudolosowa z przedziału <-1;1>
        return static_cast <GLfloat> (rand() * 2) / static_cast <GLfloat> (RAND_MAX) - 1.f;
    else
        //liczba pseudolosowa z przedziału <0;1>
        return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

//zwaraca współczynnik perturbacji zależny od wielkości i poziomu fraktalu
GLfloat calculateNoiseFactor() {
    //obliczanie ilości elementów w linii
    GLfloat count = 3;
    for (size_t i = 0; i < last_level; i++) {
        count *= 3.f;
    }
    //wyliczanie współczynnika
    return (size / (CARPET_SIZE * count)) * noise;
}

//obliczenie perturbacji punktu z uwzględnieniem głebokości fraktalu
GLfloat calculateNoise(GLfloat cord) {

    //losowanie przesunięcia w uwzględnieniem ustawień i wielkosci fraktalu
    cord += randGLfloat(true) * noise_factor;
    return cord;
}

void drawPerturbatedPolygon(GLfloat x, GLfloat y, GLfloat size) {
    //rozpoczęcie rysowania poligonu
    glBegin(GL_POLYGON);
        //ustawienie koloru losowego
        glColor3f(randGLfloat(), randGLfloat(), randGLfloat());
        //ustawianie punktu 1 z uwzględnieniem noise i wielkością kwadratu
        glVertex2f(calculateNoise(x), calculateNoise(y));
        //ustawienie koloru losowego
        glColor3f(randGLfloat(), randGLfloat(), randGLfloat());
        //ustawianie punktu 2 z uwzględnieniem noise i wielkością kwadratu
        glVertex2f(calculateNoise(x + size),  calculateNoise(y));
        //ustawienie koloru losowego
        glColor3f(randGLfloat(), randGLfloat(), randGLfloat());
        //ustawianie punktu 3 z uwzględnieniem noise i wielkością kwadratu
        glVertex2f(calculateNoise(x + size),calculateNoise(y + size));
        //ustawienie koloru losowego
        glColor3f(randGLfloat(), randGLfloat(), randGLfloat());
        //ustawianie punktu 4 z uwzględnieniem noise i wielkością kwadratu
        glVertex2f(calculateNoise(x), calculateNoise(y + size));
    //zakończenie rysowania poligonu
    glEnd();
}

//test czy dany element ma możliwość bycia widocznym na ekranie
bool testIfNotVisible(GLfloat x, GLfloat y, GLfloat size) {
    if ((x + size) + noise_factor < -screenWidth || x - noise_factor > screenWidth
        || (y + size) + noise_factor < -screenHeight || y - noise_factor > screenHeight) {
        return true;
    }
    return false;
}

//Rysowanie poligonu z podanych punktów o podanej ilości punktów
void drawSierpinskiCarpet(GLfloat x, GLfloat y, GLfloat size, size_t depth) {
    //nowa wielkość kwadratu
    GLfloat sizeNew = size / 3.f;
    //dla 3 pozycji poziomo
    for (size_t horizontal = 0; horizontal < 3; horizontal++) {
        //dla 3 pozycji pionowo
        for (size_t vertical = 0; vertical < 3; vertical++) {
            //jeżeli środek to pomija rysowanie
            if (horizontal == 1 && vertical == 1) continue;

            //wyznaczanie pozycji lewego górnego wierzchołku na podstawie danych o pozycji rysowania i długości
            GLfloat xNew = x + sizeNew * horizontal;
            GLfloat yNew = y + sizeNew * vertical;

            //jeżeli element nie ma moliwości wyświetlenia na ekranie to jego rysowanie jest pomijane
            //tylko jeżeli taka opcja jest włączona
            if (show_visible && testIfNotVisible(xNew, yNew, sizeNew)) continue;

            if (depth > 1) {
                //jeżeli nie jest to ostatni poziom wchodzi w rekurencje z danymi o pozycji i zmniejszonej wielkości
                drawSierpinskiCarpet(xNew, yNew, sizeNew, depth - 1);
            }
            else {
                //Ostatni poziom - rysowanie poligonu
                drawPerturbatedPolygon(xNew, yNew, sizeNew);
            }
        }
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
    display_setting_text(-screenWidth + 10.f, screenHeight - 10.f, "Poziom zniekształcenia: %1.1f", noise);
    //ifnrmacja o ilości poziomów
    display_setting_text(-screenWidth + 10.f, screenHeight - 15.f, "Poziomy fraktalu: %u", last_level);
    //Iformacja o tym, czy pomijać niewidoczne elementy
    display_setting_text(-screenWidth + 10.f, - screenHeight + 15.f, "Pomijac niewidoczne: %s", (show_visible) ? "T": "N");
    //Iformacja o przyciskach
    display_setting_text(-screenWidth + 10.f, -screenHeight + 10.f, "Dostepne klawisze: [w,a,s,d,p,+,-,(arrows)]");
}

// Funkcaja określająca, co ma być rysowane
void RenderScene(void) {
    //ustawenie seedu aby podczas przerysowania nie zmieniać wyglądu fraktalu
    srand(seed);
    //obliczanie wspołczynnika zaszumienia na podstawie aktyalnych ustawień
    noise_factor = calculateNoiseFactor();

    // Czyszczenie okna aktualnym kolorem czyszczącym
    glClear(GL_COLOR_BUFFER_BIT);

    //wywołanie metody rysującej dywan
    drawSierpinskiCarpet(pos_x, pos_y, size, last_level);

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
    //zapamiętanie seedu podczas inizjalizacji programu
    seed = time(NULL);
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
        //zapisywanie współczynników ekranu
        screenWidth = 100.0;
        screenHeight = 100.0 / AspectRatio;
        glOrtho(-screenWidth, screenWidth, -screenHeight, screenHeight, 1.0, -1.0);
    }
    else {
        //zapisywanie współczynników ekranu
        screenWidth = 100.0 * AspectRatio;
        screenHeight = 100.0;
        glOrtho(-screenWidth, screenWidth, -screenHeight, screenHeight, 1.0, -1.0);
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
        pos_y += DEF_STEP_MOOV;
        break;
    case GLUT_KEY_UP:
        //przesunięcie fraktalu w dół
        pos_y -= DEF_STEP_MOOV;
        break;
    case GLUT_KEY_LEFT:
        //przesunięcie fraktalu w prawo
        pos_x += DEF_STEP_MOOV;
        break;
    case GLUT_KEY_RIGHT:
        //przesunięcie fraktalu w lewo
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
            size += DEF_STEP_ZOOM * (size/DEF_ZOOM);
            break;
        case 45:
            //pomniejszenie [-]
            size -= DEF_STEP_ZOOM * (size / DEF_ZOOM);
            break;
        case 97:
            //zwiększenie poziomu parturbacji [d]
            if (noise > 0.f) {
                noise -= DEF_NOISE_STEP;
                if (noise < 0.f) noise = 0.f;
            }
            break;
        case 100:
            //zmniejszenie poziomu parturbacji [a]
            noise += DEF_NOISE_STEP;
            break;
        case 119:
            //zwiększenie poziomu fraktalu [w]
            last_level++;
            break;
        case 115:
            //zmniejszenie poziomu fraktalu [s]
            if (last_level > 1) {
                last_level--;
            }
            break;
        case 112:
            //zmiana trybu wyświetlania elementów
            show_visible = !show_visible;
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