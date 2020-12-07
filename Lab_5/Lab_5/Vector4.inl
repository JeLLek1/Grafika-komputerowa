  // Copyright 2020 JeLLek
#pragma once
#include "Vector4.h"

// konstruktor pusty (przypisanie 0)
template <typename T>
inline Vector4<T>::Vector4() {
    this->cords[0] = this->cords[1] = this->cords[2] = this->cords[3] = 0;
}
// konstruktor z podanymi elementami
template <typename T>
inline Vector4<T>::Vector4(T x, T y, T z, T a) {
    this->cords[0] = x;
    this->cords[1] = y;
    this->cords[2] = z;
    this->cords[3] = a;
}
// kontstuktor z Vector3
template <typename T>
inline Vector4<T>::Vector4(Vector3<T> vector, T a) {
    this->cords[0] = vector.cords[0];
    this->cords[1] = vector.cords[1];
    this->cords[2] = vector.cords[2];
    this->cords[3] = a;
}

// przeciążenie operatora przypisania
template<typename T>
inline Vector4<T>& Vector4<T>::operator=(const Vector4<T>& right) {
    this->cords[0] = right.cords[0];
    this->cords[1] = right.cords[1];
    this->cords[2] = right.cords[2];
    this->cords[3] = right.cords[3];
    return *this;
}
