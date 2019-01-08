#include "math_class.h"

vector_3d<float> math_class::centroid(const matrix<float>& matrix)
{
	float total_x = 0.0f;
	float total_y = 0.0f;
	float total_z = 0.0f;
	const unsigned col_size = matrix.get_cols();

	for (unsigned i = 0; i < col_size; ++i)
	{
		total_x += matrix(0, i);
		total_y += matrix(1, i);
		total_z += matrix(2, i);
	}

	return vector_3d<float>{total_x / col_size, total_y / col_size, total_z / col_size};
}

void math_class::rotate_x(matrix<float>& m, float degrees, bool clockwise, float pitch, float yaw, float roll)
{
	matrix<float> rotation_matrix = matrix<float>::get_rotation_matrix_x(degrees, clockwise);

	vector_3d<float> m_center = centroid(m);

	matrix<float> translation_back = matrix<float>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	matrix<float> translation_to_origin = matrix<float>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());
	matrix<float> rotate_y_to_xy = matrix<float>::get_rotation_matrix_y(yaw, false);
	matrix<float> rotate_y_back = matrix<float>::get_rotation_matrix_y(yaw, true);
	matrix<float> rotate_z_to_x = matrix<float>::get_rotation_matrix_z(roll, false);
	matrix<float> rotate_z_back = matrix<float>::get_rotation_matrix_z(roll, true);

	matrix<float> mutation_matrix = translation_back * rotate_y_back * rotate_z_back * 
										rotation_matrix * translation_to_origin * rotate_z_to_x * rotate_y_to_xy;

	mutation_matrix *= m;
	m = mutation_matrix;
}
