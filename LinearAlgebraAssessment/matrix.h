#pragma once
#include <vector>
#include <iostream>
#include <complex>

template<typename T> class matrix
{
	std::vector<std::vector<T> > mat_;
	unsigned rows_;
	unsigned cols_;

public:
	matrix() = default;
	matrix(unsigned rows, unsigned cols);
	void init_with_position_vectors(const std::vector<vector_3d<T>>& position_vectors);

	matrix<T> operator+(const matrix<T>& rhs_matrix);
	matrix<T> operator-(const matrix<T>& rhs_matrix);
	matrix<T> operator*(const matrix<T>& rhs_matrix);
	matrix<T>& operator*=(const matrix<T>& rhs_matrix);

	matrix<T> operator+(const T& rhs);
	matrix<T> operator-(const T& rhs);
	matrix<T> operator*(const T& rhs);

	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	unsigned get_rows() const;
	unsigned get_cols() const;

	static matrix<T> get_translation_matrix(const T& x, const T& y, const T& z);
	static matrix<T> get_scaling_matrix(const T& x, const T& y, const T& z);
	static matrix<T> get_rotation_matrix_x(const T& degrees);
	static matrix<T> get_rotation_matrix_y(const T& degrees);
	static matrix<T> get_rotation_matrix_z(const T& degrees);

	void debug_draw();
	static double convert_degrees_to_radian(const T& degrees);
};

template <typename T>
matrix<T>::matrix(unsigned rows, unsigned cols)
{
	mat_.resize(rows);
	for (unsigned i = 0; i < mat_.size(); i++)
	{
		mat_[i].resize(cols);
	}
	rows_ = rows;
	cols_ = cols;
}

template <typename T>
void matrix<T>::init_with_position_vectors(const std::vector<vector_3d<T>>& position_vectors)
{
	this->mat_.resize(4);
	this->rows_ = 4;
	this->cols_ = position_vectors.size();

	for (unsigned i = 0; i < 4; i++)
	{
		this->mat_[i].resize(position_vectors.size());
	}

	for (auto i = 0; i < position_vectors.size(); i++)
	{
		this->mat_[0][i] = position_vectors[i].x();
		this->mat_[1][i] = position_vectors[i].y();
		this->mat_[2][i] = position_vectors[i].z();;
		this->mat_[3][i] = 1;
	}
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& rhs_matrix)
{
	matrix result(rows_, cols_);

	for (unsigned i = 0; i < rows_; i++) {
		for (unsigned j = 0; j < cols_; j++) {
			result(i, j) = this->mat_[i][j] + rhs_matrix(i, j);
		}
	}

	return result;
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& rhs_matrix)
{
	unsigned rows = rhs_matrix.get_rows();
	unsigned cols = rhs_matrix.get_cols();
	matrix result(rows, cols);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat_[i][j] - rhs_matrix(i, j);
		}
	}

	return result;
}

template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& rhs_matrix)
{
	unsigned int rows = rhs_matrix.get_rows();
	unsigned cols = rhs_matrix.get_cols();
	matrix result(rows, cols);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			for (unsigned k = 0; k < rows; k++) {
				result(i, j) += this->mat_[i][k] * rhs_matrix(k, j);
			}
		}
	}

	return result;
}

template <typename T>
matrix<T>& matrix<T>::operator*=(const matrix<T>& rhs_matrix)
{
	matrix result = (*this) * rhs_matrix;
	(*this) = result;
	return *this;
}

template <typename T>
matrix<T> matrix<T>::operator+(const T& rhs)
{
	matrix result(rows_, cols_);

	for (unsigned i = 0; i < rows_; i++) {
		for (unsigned j = 0; j < cols_; j++) {
			result(i, j) = this->mat_[i][j] + rhs;
		}
	}

	return result;
}

template <typename T>
matrix<T> matrix<T>::operator-(const T& rhs)
{
	matrix result(rows_, cols_);

	for (unsigned i = 0; i < rows_; i++) {
		for (unsigned j = 0; j < cols_; j++) {
			result(i, j) = this->mat_[i][j] - rhs;
		}
	}

	return result;
}

template <typename T>
matrix<T> matrix<T>::operator*(const T& rhs)
{
	matrix result(rows_, cols_);

	for (unsigned i = 0; i < rows_; i++) {
		for (unsigned j = 0; j < cols_; j++) {
			result(i, j) = this->mat_[i][j] * rhs;
		}
	}

	return result;
}

template <typename T>
T& matrix<T>::operator()(const unsigned& row, const unsigned& col)
{
	return this->mat_[row][col];
}

template <typename T>
const T& matrix<T>::operator()(const unsigned& row, const unsigned& col) const
{
	return this->mat_[row][col];
}

template <typename T>
unsigned matrix<T>::get_rows() const
{
	return this->rows_;
}

template <typename T>
unsigned matrix<T>::get_cols() const
{
	return this->cols_;
}

template <typename T>
matrix<T> matrix<T>::get_translation_matrix(const T& x, const T& y, const T& z)
{
	matrix translation_matrix(4, 4);
	translation_matrix(0, 0) = 1;
	translation_matrix(1, 1) = 1;
	translation_matrix(2, 2) = 1;
	translation_matrix(3, 3) = 1;
	translation_matrix(0, 3) = x;
	translation_matrix(1, 3) = y;
	translation_matrix(2, 3) = z;

	return translation_matrix;
}

template <typename T>
matrix<T> matrix<T>::get_scaling_matrix(const T& x, const T& y, const T& z)
{
	matrix scaling_matrix(4, 4);
	scaling_matrix(0, 0) = x;
	scaling_matrix(1, 1) = y;
	scaling_matrix(2, 2) = z;
	scaling_matrix(3, 3) = 1;

	return scaling_matrix;
}

template <typename T>
matrix<T> matrix<T>::get_rotation_matrix_x(const T& degrees)
{
	double radian = convert_degrees_to_radian(degrees);

	matrix rotation_matrix(4, 4);
	if (degrees >= 0) {
		rotation_matrix(0, 0) = 1;
		rotation_matrix(1, 1) = std::cos(radian);
		rotation_matrix(1, 2) = -std::sin(radian);
		rotation_matrix(2, 1) = std::sin(radian);
		rotation_matrix(2, 2) = std::cos(radian);
		rotation_matrix(3, 3) = 1;

		return rotation_matrix;
	}

	radian = radian * -1;
	rotation_matrix(0, 0) = 1;
	rotation_matrix(1, 1) = std::cos(radian);
	rotation_matrix(1, 2) = std::sin(radian);
	rotation_matrix(2, 1) = -std::sin(radian);
	rotation_matrix(2, 2) = std::cos(radian);
	rotation_matrix(3, 3) = 1;

	return rotation_matrix;
}

template <typename T>
matrix<T> matrix<T>::get_rotation_matrix_y(const T& degrees)
{
	double radian = convert_degrees_to_radian(degrees);

	matrix rotation_matrix(4, 4);
	if (degrees >= 0) {
		rotation_matrix(0, 0) = std::cos(radian);
		rotation_matrix(0, 2) = std::sin(radian);
		rotation_matrix(1, 1) = 1;
		rotation_matrix(2, 0) = -std::sin(radian);
		rotation_matrix(2, 2) = std::cos(radian);
		rotation_matrix(3, 3) = 1;

		return rotation_matrix;
	}

	radian = radian * -1;
	rotation_matrix(0, 0) = std::cos(radian);
	rotation_matrix(0, 2) = -std::sin(radian);
	rotation_matrix(1, 1) = 1;
	rotation_matrix(2, 0) = std::sin(radian);
	rotation_matrix(2, 2) = std::cos(radian);
	rotation_matrix(3, 3) = 1;

	return rotation_matrix;
}

template <typename T>
matrix<T> matrix<T>::get_rotation_matrix_z(const T& degrees)
{
	double radian = convert_degrees_to_radian(degrees);

	matrix rotation_matrix(4, 4);
	if (degrees >= 0) {
		rotation_matrix(0, 0) = std::cos(radian);
		rotation_matrix(0, 1) = -std::sin(radian);
		rotation_matrix(1, 0) = std::sin(radian);
		rotation_matrix(1, 1) = std::cos(radian);
		rotation_matrix(2, 2) = 1;
		rotation_matrix(3, 3) = 1;

		return rotation_matrix;
	}

	radian = radian * -1;
	rotation_matrix(0, 0) = std::cos(radian);
	rotation_matrix(0, 1) = std::sin(radian);
	rotation_matrix(1, 0) = -std::sin(radian);
	rotation_matrix(1, 1) = std::cos(radian);
	rotation_matrix(2, 2) = 1;
	rotation_matrix(3, 3) = 1;

	return rotation_matrix;
}

template <typename T>
void matrix<T>::debug_draw()
{
	for (unsigned i = 0; i < rows_; i++) {
		for (unsigned j = 0; j < cols_; j++) {
			std::cout << this->mat_[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

template <typename T>
double matrix<T>::convert_degrees_to_radian(const T& degrees)
{
	const double pi = 3.14159265358979323846;
	
	return (degrees * pi) / 180;
}

