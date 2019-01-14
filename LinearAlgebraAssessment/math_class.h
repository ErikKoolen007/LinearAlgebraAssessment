#pragma once
#include "vector_3d.h"
#include "matrix.h"
#include "camera.h"

constexpr double pi = 3.14159265358979323846;

class math_class
{
	math_class() = default;
public:

	static vector_3d<double> centroid(const matrix<double>& matrix);
	static void rotate_x(matrix<double>& m, double degrees, double yaw, double roll);
	static void rotate_y(matrix<double>& m, double degrees, double pitch, double roll);
	static void rotate_z(matrix<double>& m, double degrees, double pitch, double yaw);
	static void scale(double x_factor, double y_factor, double z_factor, matrix<double>& m);
	static void translate(double x, double y, double z, matrix<double>& m);
	static matrix<double> convert_to_3d(const matrix<double>& m, const matrix<double>& camera_matrix, double screen_width, double screen_height);

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