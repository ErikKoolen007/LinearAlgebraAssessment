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

//Pitch rotation
void math_class::rotate_x(matrix<float>& m, float degrees, float yaw, float roll)
{
	vector_3d<float> m_center = centroid(m);
	const matrix<float> rotation_matrix = matrix<float>::get_rotation_matrix_x(degrees);

	matrix<float> translation_back = matrix<float>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<float> translation_to_origin = matrix<float>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Pitch rotation so yaw and roll need to be 0
	const matrix<float> yaw_rotate_0 = matrix<float>::get_rotation_matrix_y(-yaw);
	const matrix<float> yaw_rotate_back = matrix<float>::get_rotation_matrix_y(yaw);
	const matrix<float> roll_rotate_0 = matrix<float>::get_rotation_matrix_z(-roll);
	const matrix<float> roll_rotate_back = matrix<float>::get_rotation_matrix_z(roll);

	matrix<float> mutation_matrix = translation_back * yaw_rotate_back * roll_rotate_back * 
										rotation_matrix * roll_rotate_0 * yaw_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

//Yaw rotation
void math_class::rotate_y(matrix<float>& m, float degrees, float pitch, float roll)
{
	vector_3d<float> m_center = centroid(m);
	const matrix<float> rotation_matrix = matrix<float>::get_rotation_matrix_y(degrees);

	matrix<float> translation_back = matrix<float>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<float> translation_to_origin = matrix<float>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Yaw rotation so pitch and roll need to be 0
	const matrix<float> pitch_rotate_0 = matrix<float>::get_rotation_matrix_x(-pitch);
	const matrix<float> pitch_rotate_back = matrix<float>::get_rotation_matrix_x(pitch);
	const matrix<float> roll_rotate_0 = matrix<float>::get_rotation_matrix_z(-roll);
	const matrix<float> roll_rotate_back = matrix<float>::get_rotation_matrix_z(roll);

	matrix<float> mutation_matrix = translation_back * pitch_rotate_back * roll_rotate_back *
										rotation_matrix * roll_rotate_0 * pitch_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

//Roll rotation
void math_class::rotate_z(matrix<float>& m, float degrees, float pitch, float yaw)
{
	vector_3d<float> m_center = centroid(m);
	const matrix<float> rotation_matrix = matrix<float>::get_rotation_matrix_z(degrees);

	matrix<float> translation_back = matrix<float>::get_translation_matrix(m_center.x(), m_center.y(), m_center.z());
	const matrix<float> translation_to_origin = matrix<float>::get_translation_matrix(-m_center.x(), -m_center.y(), -m_center.z());

	//Roll rotation so pitch and yaw need to be 0
	const matrix<float> pitch_rotate_0 = matrix<float>::get_rotation_matrix_x(-pitch);
	const matrix<float> pitch_rotate_back = matrix<float>::get_rotation_matrix_x(pitch);
	const matrix<float> yaw_rotate_0 = matrix<float>::get_rotation_matrix_y(-yaw);
	const matrix<float> yaw_rotate_back = matrix<float>::get_rotation_matrix_y(yaw);

	matrix<float> mutation_matrix = translation_back * pitch_rotate_back * yaw_rotate_back *
										rotation_matrix * yaw_rotate_0 * pitch_rotate_0 * translation_to_origin;

	mutation_matrix *= m;
	m = mutation_matrix;
}

void math_class::scale(float x_factor, float y_factor, float z_factor, matrix<float>& m)
{
	matrix<float> scaling_matrix = matrix<float>::get_scaling_matrix(x_factor, y_factor, z_factor);

	scaling_matrix *= m;
	m = scaling_matrix;
}

void math_class::translate(float x_factor, float y_factor, float z_factor, matrix<float>& m)
{
	matrix<float> translation_matrix = matrix<float>::get_translation_matrix(x_factor, y_factor, z_factor);

	translation_matrix *= m;
	m = translation_matrix;
}

void math_class::convert_to_3d(matrix<float>& m, camera& c, float screen_width, float screen_height)
{
	//Convert matrix with flat coords to 3d with camera matrix
	matrix<float> camera_matrix = c.matrix();

	//Set 3d converted matrix in perspective
	matrix<float> projection_matrix = matrix<float>::get_perspective_matrix(0.1f, 100, 90);

	matrix<float> mutation_matrix = projection_matrix * camera_matrix;
	mutation_matrix *= m;
	m = mutation_matrix;

	//Correct the vectors
	for (unsigned i = 0; i < m.get_cols(); i++)
	{
		const float x = m(0, i);
		const float y = m(1, i);
		const float z = m(2, i);
		const float w = m(3, i);

		m(0, i) = screen_width * (x / w + 1) / 2;
		//m(0, i) = screen_width / 2 + (x + 1) / w * screen_width * 0.5;
		m(1, i) = screen_height * (y / w + 1) / 2;
		//m(1, i) = screen_height / 2 + (y + 1) / w * screen_height * 0.5;
		m(2, i) = z * -1;
		m(3, i) = w / w;
	}
}
