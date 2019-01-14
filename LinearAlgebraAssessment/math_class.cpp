#include "math_class.h"

vector_3d<double> math_class::centroid(const matrix<double>& matrix)
{
	double total_x = 0.0f;
	double total_y = 0.0f;
	double total_z = 0.0f;
	const unsigned col_size = matrix.get_cols();

	for (unsigned i = 0; i < col_size; ++i)
	{
		total_x += matrix(0, i);
		total_y += matrix(1, i);
		total_z += matrix(2, i);
	}

	return vector_3d<double>{total_x / col_size, total_y / col_size, total_z / col_size};
}

//Pitch rotation
void math_class::rotate_x(matrix<double>& m, double degrees, double yaw, double roll)
{
	vector_3d<double> m_center = centroid(m);
	const matrix<double> rotation_matrix = matrix<double>::get_rotation_matrix_x(degrees);

	matrix<double> translation_back = matrix<double>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<double> translation_to_origin = matrix<double>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Pitch rotation so yaw and roll need to be 0
	const matrix<double> yaw_rotate_0 = matrix<double>::get_rotation_matrix_y(-yaw);
	const matrix<double> yaw_rotate_back = matrix<double>::get_rotation_matrix_y(yaw);
	const matrix<double> roll_rotate_0 = matrix<double>::get_rotation_matrix_z(-roll);
	const matrix<double> roll_rotate_back = matrix<double>::get_rotation_matrix_z(roll);

	matrix<double> mutation_matrix = translation_back * yaw_rotate_back * roll_rotate_back * 
										rotation_matrix * roll_rotate_0 * yaw_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

//Yaw rotation
void math_class::rotate_y(matrix<double>& m, double degrees, double pitch, double roll)
{
	vector_3d<double> m_center = centroid(m);
	const matrix<double> rotation_matrix = matrix<double>::get_rotation_matrix_y(degrees);

	matrix<double> translation_back = matrix<double>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<double> translation_to_origin = matrix<double>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Yaw rotation so pitch and roll need to be 0
	const matrix<double> pitch_rotate_0 = matrix<double>::get_rotation_matrix_x(-pitch);
	const matrix<double> pitch_rotate_back = matrix<double>::get_rotation_matrix_x(pitch);
	const matrix<double> roll_rotate_0 = matrix<double>::get_rotation_matrix_z(-roll);
	const matrix<double> roll_rotate_back = matrix<double>::get_rotation_matrix_z(roll);

	matrix<double> mutation_matrix = translation_back * pitch_rotate_back * roll_rotate_back *
										rotation_matrix * roll_rotate_0 * pitch_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

//Roll rotation
void math_class::rotate_z(matrix<double>& m, double degrees, double pitch, double yaw)
{
	vector_3d<double> m_center = centroid(m);
	const matrix<double> rotation_matrix = matrix<double>::get_rotation_matrix_z(degrees);

	matrix<double> translation_back = matrix<double>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<double> translation_to_origin = matrix<double>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Roll rotation so pitch and yaw need to be 0
	const matrix<double> pitch_rotate_0 = matrix<double>::get_rotation_matrix_x(-pitch);
	const matrix<double> pitch_rotate_back = matrix<double>::get_rotation_matrix_x(pitch);
	const matrix<double> yaw_rotate_0 = matrix<double>::get_rotation_matrix_y(-yaw);
	const matrix<double> yaw_rotate_back = matrix<double>::get_rotation_matrix_y(yaw);

	matrix<double> mutation_matrix = translation_back * pitch_rotate_back * yaw_rotate_back *
										rotation_matrix * yaw_rotate_0 * pitch_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

void math_class::scale(double x_factor, double y_factor, double z_factor, matrix<double>& m)
{
	vector_3d<double> m_center = centroid(m);

	matrix<double> translation_back = matrix<double>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<double> translation_to_origin = matrix<double>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());
	matrix<double> scaling_matrix = matrix<double>::get_scaling_matrix(x_factor, y_factor, z_factor);

	matrix<double> mutation_matrix = translation_back * scaling_matrix * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

void math_class::translate(double x, double y, double z, matrix<double>& m)
{
	matrix<double> translation_matrix = matrix<double>::get_translation_matrix(x, y, z);

	translation_matrix *= m;
	m = translation_matrix;
}

matrix<double> math_class::convert_to_3d(const matrix<double>& m, const matrix<double>& camera_matrix, double screen_width, double screen_height)
{
	matrix<double> matrix_3D{ 4, m.get_cols() };

	//Set 3d converted matrix in perspective
	matrix<double> projection_matrix = matrix<double>::get_perspective_matrix(0.1f, 100, 90);

	matrix<double> mutation_matrix = projection_matrix * camera_matrix;
	mutation_matrix *= m;
	matrix_3D = mutation_matrix;

	//Correct the vectors
	for (unsigned i = 0; i < m.get_cols(); i++)
	{
		const double x = matrix_3D(0, i);
		const double y = matrix_3D(1, i);
		const double z = matrix_3D(2, i);
		const double w = matrix_3D(3, i);

		matrix_3D(0, i) = screen_width * (x / w + 1) / 2;
		//m(0, i) = screen_width / 2 + (x + 1) / w * screen_width * 0.5;
		matrix_3D(1, i) = screen_height * (y / w + 1) / 2;
		//m(1, i) = screen_height / 2 + (y + 1) / w * screen_height * 0.5;
		//matrix_3D(2, i) = z * -1;
		//matrix_3D(3, i) = 1;
	}

	return matrix_3D;
}
