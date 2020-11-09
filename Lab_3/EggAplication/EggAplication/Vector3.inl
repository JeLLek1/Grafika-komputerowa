#include "Vector3.h"
#include <cmath>
#pragma once
//konstruktor pusty (przypisanie 0)
template <typename T>
inline Vector3<T>::Vector3() {
	this->cords[0] = this->cords[1] = this->cords[2] = 0;
}
//konstruktor z podanymi elementami
template <typename T>
inline Vector3<T>::Vector3(T x, T y, T z) {
	this->cords[0] = x;
	this->cords[1] = y;
	this->cords[2] = z;
}
//normalizuje wektor (wektor/sqrt(x*x + y+y + z+z)
template<typename T>
inline void Vector3<T>::normalize()
{
	(*this) /= std::sqrt(this->cords[0] * this->cords[0] + this->cords[1] * this->cords[1] + this->cords[2] * this->cords[2]);
}
//oblicza dystans miêdzy wektorami (sqrt((x1-x2)^2 * (y1-y2)^2 * (z1-z2)^2)
template<typename T>
inline T Vector3<T>::distance(const Vector3<T>& rigth)
{
	return std::sqrt((this->cords[0] - rigth.cords[0]) * (this->cords[0] - rigth.cords[0])
					+ (this->cords[1] - rigth.cords[1]) * (this->cords[1] - rigth.cords[1])
					+ (this->cords[2] - rigth.cords[2]) * (this->cords[2] - rigth.cords[2]));
}
//przeci¹¿enie operatora przypisania
template<typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& rigth)
{
	this->cords[0] = rigth.cords[0];
	this->cords[1] = rigth.cords[1];
	this->cords[2] = rigth.cords[2];
	return *this;
}
//przeci¹¿enie operatora dodawania z przypisaniem (obie strony s¹ wektorami)
template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rigth)
{
	this->cords[0] += rigth.cords[0];
	this->cords[1] += rigth.cords[1];
	this->cords[2] += rigth.cords[2];

	return *this;
}
//przeci¹¿enie operatora mno¿enia z przypisaniem (obie strony s¹ wektorami)
template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& rigth)
{
	this->cords[0] *= rigth.cords[0];
	this->cords[1] *= rigth.cords[1];
	this->cords[2] *= rigth.cords[2];

	return *this;
}
//przeci¹¿enie operatora dzielenia z przypisaniem (obie strony s¹ wektorami)
template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const T& rigth)
{
	this->cords[0] /= rigth;
	this->cords[1] /= rigth;
	this->cords[2] /= rigth;

	return *this;
}
//przeci¹¿enie operatora odejmowania (obie strony s¹ wektorami)
template<typename T>
inline Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(left.cords[0] - right.cords[0], left.cords[1] - right.cords[1], left.cords[2] - right.cords[2]);
}
//przeci¹¿enie operatora dodawania (obie strony s¹ wektorami)
template<typename T>
inline Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(left.cords[0] + right.cords[0], left.cords[1] + right.cords[1], left.cords[2] + right.cords[2]);
}
//przeci¹¿enie operatora mno¿enia (jedna strona jest wektorem)
template<typename T>
inline Vector3<T> operator*(const Vector3<T>& left, const T& right)
{
	return Vector3<T>(left.cords[0] * right, left.cords[1] * right, left.cords[2] * right);
}