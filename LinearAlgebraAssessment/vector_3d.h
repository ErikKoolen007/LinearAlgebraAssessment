#pragma once
#include <complex>
#include <iostream>

template <typename T> class vector_3d
{
	T x_;
	T y_;
	T z_;
public:
	vector_3d(T x, T y, T z) : x_(x), y_(y), z_(z)
	{
	}
	vector_3d() : x_{}, y_{}, z_{}
	{
	}

	T x() const { return x_; }
	T y() const { return y_; }
	T z() const { return z_; }
	void x(T x) { x_ = x; }
	void y(T y) { y_ = y; }
	void z(T z) { z_ = z; }

	vector_3d<T> operator+(const vector_3d<T>& other);
	vector_3d<T>& operator+=(const vector_3d<T>& other);

	vector_3d<T> operator-(const vector_3d<T>& other);
	vector_3d<T>& operator-=(const vector_3d<T>& other);

	vector_3d<T> operator*(const T& scalar);
	vector_3d<T>& operator*=(const T& scalar);

	bool operator==(const vector_3d<T>& other);

	void print()
	{
		std::cout << "x: " << x_ << " y: " << y_ << " z: " << z_ << "\n";
	}
};

template <typename T>
vector_3d<T> vector_3d<T>::operator+(const vector_3d<T>& other)
{
	return vector_3d{ x_ + other.x_, y_ + other.y_, z_ + other.z_ };
}

template <typename T>
vector_3d<T>& vector_3d<T>::operator+=(const vector_3d<T>& other)
{
	return *this = *this + other;
}

template <typename T>
vector_3d<T> vector_3d<T>::operator-(const vector_3d<T>& other)
{
	return vector_3d{ x_ - other.x_, y_ - other.y_, z_ - other.z_ };
}

template <typename T>
vector_3d<T>& vector_3d<T>::operator-=(const vector_3d<T>& other)
{
	return *this = *this - other;
}

template <typename T>
vector_3d<T> vector_3d<T>::operator*(const T& scalar)
{
	return vector_3d(x_ * scalar, y_ * scalar, z_ * scalar);
}

template <typename T>
vector_3d<T>& vector_3d<T>::operator*=(const T& scalar)
{
	return *this = *this * scalar;
}

//(Dutch)inproduct
template <typename Scalar>
constexpr Scalar dot(vector_3d<Scalar> a, vector_3d<Scalar> b)
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

template <typename Scalar>
constexpr float vector_length(vector_3d<Scalar> v)
{
	return std::sqrt(std::pow(v.x(), 2) + std::pow(v.y(), 2) + std::pow(v.z(), 2));
}

template <typename Scalar>
constexpr float angle(vector_3d<Scalar> a, vector_3d<Scalar> b)
{
	return std::acos(dot(a, b) / (vector_length(a) * vector_length(b)));
}

//(Dutch) uitproduct
template <typename Scalar>
constexpr vector_3d<Scalar> cross(vector_3d<Scalar> a, vector_3d<Scalar> b)
{
	Scalar x = (a.y() * b.z()) - (a.z() * b.y());
	Scalar y = (a.z() * b.x()) - (a.x() * b.z());
	Scalar z = (a.x() * b.y()) - (a.y() * b.x());

	return vector_3d<Scalar>{x, y, z};
}