#pragma once
//szablon klasy o trzech punktach z operatorami
template <typename T>
class Vector3
{
public:
	//koordynaty
	T cords[3];
	//konstruktor pusty
	Vector3();
	//konstruktor z podanymi elementami
	Vector3(T x, T y, T z);

	//normalizuje wektor
	void normalize();
	//oblicza dystans miêdzy wektorami
	T distance(const Vector3<T>& rigth);

	//przeci¹¿enie operatora przypisania
	Vector3<T>& operator =(const Vector3<T>& rigth);
	//przeci¹¿enie operatora dodawania z przypisaniem (obie strony s¹ wektorami)
	Vector3<T>& operator +=(const Vector3<T>& rigth);
	//przeci¹¿enie operatora mno¿enia z przypisaniem (obie strony s¹ wektorami)
	Vector3<T>& operator *=(const Vector3<T>& rigth);
	//przeci¹¿enie operatora dzielenia z przypisaniem (obie strony s¹ wektorami)
	Vector3<T>& operator /=(const T& rigth);
};
//przeci¹¿enie operatora odejmowania (obie strony s¹ wektorami)
template <typename T>
Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);
//przeci¹¿enie operatora dodawania (obie strony s¹ wektorami)
template <typename T>
Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);
//przeci¹¿enie operatora mno¿enia (jedna strona jest wektorem)
template <typename T>
Vector3<T> operator *(const Vector3<T>& left, const T& right);

#include "Vector3.inl"