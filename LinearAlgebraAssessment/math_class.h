#pragma once
#include "vector_3d.h"
#include "matrix.h"

class math_class
{
	math_class() = default;
public:

	static vector_3d<float> centroid(const matrix<float>& matrix);
	static void rotate_x(matrix<float>& m, float degrees, bool clockwise, float pitch, float yaw, float roll);
	static void rotate_y(matrix<float>& m, float degrees, bool clockwise, float pitch, float yaw, float roll);
	static void rotate_z(matrix<float>& m, float degrees, bool clockwise, float pitch, float yaw, float roll);
	static void scale(float factor, matrix<float>& matrix);
};

