#include "bullet.h"
#include "math_class.h"

void bullet::update(delta_time dt)
{
	time_alive_ += dt;
	vector_3d<double> new_position = heading_ * to_seconds(dt) * (start_velocity_ + velocity_);

	math_class::translate(new_position.x(), new_position.y(), new_position.z(), matrix_);
}
