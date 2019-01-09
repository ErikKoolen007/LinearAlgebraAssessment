#pragma once
#include "vector_3d.h"
#include "matrix.h"

class math_class
{
	math_class() = default;
public:

	static vector_3d<float> centroid(const matrix<float>& matrix);
	static void rotate_x(matrix<float>& m, float degrees, float yaw, float roll);
	static void rotate_y(matrix<float>& m, float degrees, float pitch, float roll);
	static void rotate_z(matrix<float>& m, float degrees, float pitch, float yaw);
	static void scale(float x_factor, float y_factor, float z_factor, matrix<float>& m);
	static void translate(float x_factor, float y_factor, float z_factor, matrix<float>& m);

	
};

template <typename Scalar>
constexpr Scalar dot(vector_3d<Scalar> a, vector_3d<Scalar> b)
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}
