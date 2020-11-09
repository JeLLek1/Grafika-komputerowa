#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include "App.h"
/* Opis progamu: 
Program generuje fraktal zbioru Mandelbrota. Pozwala na przybliżanie, oddalanie fraktalu.
Dodatkowo z powodu, że generowanie jest wymagające szczególnie dla czarnego pola (program musi przejść przez maksymalną ilość iteracji, 
generowana jest tylko co N-ta linia na klatkę animacji. N można zmienić w settings.h
Obsługa programu:
lewy przycisk myszy:    przybliżanie fraktalu według pozycji myszy
prawy przycisk myszy:   oddalanie fraktalu według pozycji myszy
f11:                    włączanie/wyłączanie trybu pełnoekranowego
esc:                    wyjście z programu
*/
int main(int argc, char** argv) {
    //inicjalizacja struktury danych biblioteki glut
    glutInit(&argc, argv);
    //Pobranie pierwszej instancji obiektu aplikacji (uruchomienie konstruktora)
    App::getInstance();
    // Funkcja uruchamia szkielet biblioteki GLUT
    glutMainLoop();
    return 0;
}