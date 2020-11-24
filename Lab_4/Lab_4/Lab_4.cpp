  // Copyright 2020 JeLLek
  // Opis progamu:
  // settings.h - wszyskite ustawienia, jak
  //   domyśłny typ wyświetlania, wielkości okien i ilości punktów.
  // Obsługiwane klawisze:
  // (mysz lewy przycisk) - zmiana pozycji światła punktowego
  // (+/-) - przybliżanie/oddalanie obserwatora od punktu obserwowanego
  //   (niestety nie działa u mnie scroll dlatego użyłem +/-)
  // backspace - reset widoku i światła punktowego
  // p - tryb wyświetlania chmura punktów
  // l - tryb wyświetlania linie
  // t - tryb wyświetlania wypełnione trójkąty
  // r - czerwone światło punktowe
  // g - zieolone światło punktowe
  // b - niebieskie światło punktowe
  // esc - wyjście z programu
  // f11 - pełny eknran
  // (arrows) - zmiana osi obrotu całego systemu
  //   (lewo, prawo poziomo, góra, dół pionowo)
  // space - zatrzymanie obrotu całego systemu.

#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include "App.h"

int main(int argc, char** argv) {
    // inicjalizacja struktury danych biblioteki glut
    glutInit(&argc, argv);
    // Pobranie pierwszej instancji obiektu aplikacji
    // (uruchomienie konstruktora)
    App::getInstance();
    // Funkcja uruchamia szkielet biblioteki GLUT
    glutMainLoop();
    return 0;
}
