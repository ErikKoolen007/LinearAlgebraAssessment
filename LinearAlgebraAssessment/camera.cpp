#include "camera.h"

matrix<float> camera::matrix()
{
	vector_3d<float> direction = position_ - target_;
	direction = normalize(direction);

	vector_3d<float> up{ 0,1,0 };

	vector_3d<float> right = cross(up, direction);
	right = normalize(right);

	up = cross(direction, right);
	up = normalize(up);

	matrix_(0, 0) = right.x();
	matrix_(0, 1) = right.y();
	matrix_(0, 2) = right.z();
	matrix_(0, 3) = -dot(right, position_);

	matrix_(1, 0) = up.x();
	matrix_(1, 1) = up.y();
	matrix_(1, 2) = up.z();
	matrix_(1, 3) = -dot(up, position_);

	matrix_(2, 0) = direction.x();
	matrix_(2, 1) = direction.y();
	matrix_(2, 2) = direction.z();
	matrix_(2, 3) = -dot(direction, position_);

	matrix_(3, 3) = 1;

	return matrix_;
}
