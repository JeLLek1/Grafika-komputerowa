  // Copyright 2020 JeLLek
#include "Vector3.h"
#include <cmath>
#pragma once
// konstruktor pusty (przypisanie 0)
template <typename T>
inline Vector3<T>::Vector3() {
    this->cords[0] = this->cords[1] = this->cords[2] = 0;
}
// konstruktor z podanymi elementami
template <typename T>
inline Vector3<T>::Vector3(T x, T y, T z) {
    this->cords[0] = x;
    this->cords[1] = y;
    this->cords[2] = z;
}
// normalizuje wektor (wektor/sqrt(x*x + y+y + z+z)
template<typename T>
inline void Vector3<T>::normalize() {
    (*this) /= std::sqrt(this->cords[0] * this->cords[0]
        + this->cords[1] * this->cords[1] + this->cords[2] * this->cords[2]);
}
// oblicza dystans między wektorami (sqrt((x1-x2)^2 * (y1-y2)^2 * (z1-z2)^2)
template<typename T>
inline T Vector3<T>::distance(const Vector3<T>& right) {
    return std::sqrt((this->cords[0] - right.cords[0])
        * (this->cords[0] - right.cords[0])
        + (this->cords[1] - right.cords[1])
        * (this->cords[1] - right.cords[1])
        + (this->cords[2] - right.cords[2])
        * (this->cords[2] - right.cords[2]));
}
// przeciążenie operatora przypisania
template<typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& right) {
    this->cords[0] = right.cords[0];
    this->cords[1] = right.cords[1];
    this->cords[2] = right.cords[2];
    return *this;
}
// przeciążenie operatora dodawania z przypisaniem (obie strony są wektorami)
template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& right) {
    this->cords[0] += right.cords[0];
    this->cords[1] += right.cords[1];
    this->cords[2] += right.cords[2];

    return *this;
}
// przeciążenie operatora mnożenia z przypisaniem (obie strony są wektorami)
template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& right) {
    this->cords[0] *= right.cords[0];
    this->cords[1] *= right.cords[1];
    this->cords[2] *= right.cords[2];

    return *this;
}
// przeciążenie operatora dzielenia z przypisaniem (jedna strona jest wektorem)
template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const T& right) {
    this->cords[0] /= right;
    this->cords[1] /= right;
    this->cords[2] /= right;

    return *this;
}
// przeciążenie operatora mnożenia z przypisaniem (jedna strona jest wektorem)
template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const T& right) {
    this->cords[0] *= right;
    this->cords[1] *= right;
    this->cords[2] *= right;

    return *this;
}
// przeciążenie operatora odejmowania (obie strony są wektorami)
template<typename T>
inline Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) {
    return Vector3<T>(left.cords[0] - right.cords[0],
        left.cords[1] - right.cords[1],
        left.cords[2] - right.cords[2]);
}
// przeciążenie operatora dodawania (obie strony są wektorami)
template<typename T>
inline Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) {
    return Vector3<T>(left.cords[0] + right.cords[0],
        left.cords[1] + right.cords[1],
        left.cords[2] + right.cords[2]);
}
// przeciążenie operatora mnożenia (jedna strona jest wektorem)
template<typename T>
inline Vector3<T> operator*(const Vector3<T>& left, const T& right) {
    return Vector3<T>(left.cords[0] * right,
        left.cords[1] * right,
        left.cords[2] * right);
}
// przeciążenie operatora porównania (obie strony są wektorami)
template <typename T>
inline bool operator ==(const Vector3<T>& left,
    const Vector3<T>& right) {
    if (left.cords[0] == right.cords[0]
        && left.cords[1] == right.cords[1]
        && left.cords[2] == right.cords[2]) {
        return true;
    }
    return false;
}
