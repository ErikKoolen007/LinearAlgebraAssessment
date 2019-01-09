#pragma once
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
