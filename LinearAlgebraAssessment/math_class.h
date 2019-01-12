#pragma once
#include "vector_3d.h"
#include "matrix.h"
#include "camera.h"

constexpr double pi = 3.14159265358979323846;

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
	static void convert_to_3d(matrix<float>& m, camera& c, float screen_width, float screen_height);

	template <typename T>
	static constexpr double degrees_to_radian(const T& degrees)
	{
		return (degrees * pi) / 180;
	}

	template <typename T>
	static constexpr double radian_to_degrees(const T& radian)
	{
		return radian * 180.0 / pi;
	}
};