#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include "App.h"
/* Opis progamu: 
settings.h - wszyskite ustawienia, jak domyśłny typ wyświetlania, wielkości okien i ilości punktów.
Obsługiwane klawisze: 
p - tryb wyświetlania chmura punktów
l - tryb wyświetlania linie
t - tryb wyświetlania wypełnione trójkąty
esc - wyjście z programu
f11 - pełny eknran
(arrows) - zmiana osi obrotu całego systemu (lewo, prawo poziomo, góra, dół pionowo)
space - zatrzymanie obrotu całego systemu.

w konstruktorze App.cpp definiowane są struktury jajek i systemów jajek. Program jest napisany w taki sposób,
że można tworzyć wiele struktur z wieloma jajkami z wieloma poziomami. Dodanych zostały tylko dwa według treści zadania, Ale łatwie byłoby
przerobienie na wczytywanie przykładowo z pliku ustawień, gdzie możnaby byłoby w prosty sposób dodawać wiele struktur
w konstruktorze systemu można ustalać średnice obrotu, prędkość obrotu w orbicie i prędkośc obrotu w okół własnej osi.

Strzałkami można sterować obrotem całego systemu.
*/
int main() {
    //Pobranie pierwszej instancji obiektu aplikacji (uruchomienie konstruktora)
    App::getInstance();
    // Funkcja uruchamia szkielet biblioteki GLUT
    glutMainLoop();
    return 0;
}