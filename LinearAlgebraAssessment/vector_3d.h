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

	T x() const;
	T y() const;
	T z() const;
	void x(T x);
	void y(T y);
	void z(T z);
	void set(T x, T y, T z);

	vector_3d<T> operator+(const vector_3d<T>& other);
	vector_3d<T>& operator+=(const vector_3d<T>& other);

	vector_3d<T> operator-(const vector_3d<T>& other);
	vector_3d<T>& operator-=(const vector_3d<T>& other);

	vector_3d<T> operator*(const T& scalar);
	vector_3d<T>& operator*=(const T& scalar);
};

template <typename T>
T vector_3d<T>::x() const
{
	return x_;
}

template <typename T>
T vector_3d<T>::y() const
{
	return y_;
}

template <typename T>
T vector_3d<T>::z() const
{
	return z_;
}

template <typename T>
void vector_3d<T>::x(T x)
{
	x_ = x;
}

template <typename T>
void vector_3d<T>::y(T y)
{
	y_ = y;
}

template <typename T>
void vector_3d<T>::z(T z)
{
	z_ = z;
}

template <typename T>
void vector_3d<T>::set(T x, T y, T z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

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
