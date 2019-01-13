#include "camera.h"

matrix<double> camera::get_matrix() const 
{
	vector_3d<double> position = position_;
	vector_3d<double> target = target_;
	matrix<double> camera_matrix{ 4,4 };

	vector_3d<double> direction = position - target;
	direction = normalize(direction);

	vector_3d<double> up{ 0,1,0 };

	vector_3d<double> right = cross(up, direction);
	right = normalize(right);

	up = cross(direction, right);
	up = normalize(up);

	camera_matrix(0, 0) = right.x();
	camera_matrix(0, 1) = right.y();
	camera_matrix(0, 2) = right.z();
	camera_matrix(0, 3) = -dot(right, position_);

	camera_matrix(1, 0) = up.x();
	camera_matrix(1, 1) = up.y();
	camera_matrix(1, 2) = up.z();
	camera_matrix(1, 3) = -dot(up, position_);

	camera_matrix(2, 0) = direction.x();
	camera_matrix(2, 1) = direction.y();
	camera_matrix(2, 2) = direction.z();
	camera_matrix(2, 3) = -dot(direction, position_);

	camera_matrix(3, 3) = 1;

	return camera_matrix;
}
