  // Copyright 2020 JeLLek
#pragma once
#include "Vector3.h"

// szablon klasy o czterech punktach
template <typename T>
class Vector4 {
 public:
    // koordynaty
    T cords[4];
    // konstruktor pusty
    Vector4();
    // konstruktor z podanymi elementami
    Vector4(T x, T y, T z, T a);
    // kontstuktor z Vector3
    Vector4(Vector3<T> vector, T a);

    // przeciążenie operatora przypisania
    Vector4<T>& operator =(const Vector4<T>& right);
};

#include "Vector4.inl"
