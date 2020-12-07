  // Copyright 2020 JeLLek
#pragma once
// szablon klasy o trzech punktach z operatorami
template <typename T>
class Vector3 {
 public:
    // koordynaty
    T cords[3];
    // konstruktor pusty
    Vector3();
    // konstruktor z podanymi elementami
    Vector3(T x, T y, T z);

    // normalizuje wektor
    void normalize();
    // oblicza dystans między wektorami
    T distance(const Vector3<T>& rigth);

    // przeciążenie operatora przypisania
    Vector3<T>& operator =(const Vector3<T>& rigth);
    // przeciążenie operatora dodawania
    // z przypisaniem (obie strony są wektorami)
    Vector3<T>& operator +=(const Vector3<T>& rigth);
    // przeciążenie operatora mnożenia
    // z przypisaniem (obie strony są wektorami)
    Vector3<T>& operator *=(const Vector3<T>& rigth);
    // przeciążenie operatora dzielenia
    // z przypisaniem (jedna strona jest wektorem)
    Vector3<T>& operator /=(const T& rigth);
    // przeciążenie operatora mnożenia
    // z przypisaniem (jedna strona jest wektorem)
    Vector3<T>& operator *=(const T& rigth);
};
// przeciążenie operatora odejmowania (obie strony są wektorami)
template <typename T>
Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);
// przeciążenie operatora dodawania (obie strony są wektorami)
template <typename T>
Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);
// przeciążenie operatora mnożenia (jedna strona jest wektorem)
template <typename T>
Vector3<T> operator *(const Vector3<T>& left, const T& right);
// przeciążenie operatora porównania (obie strony są wektorami)
template <typename T>
bool operator ==(const Vector3<T>& left, const Vector3<T>& right);

#include "Vector3.inl"
