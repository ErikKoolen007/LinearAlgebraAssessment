#include "camera.h"

void camera::update(delta_time dt)
{
	vector_3d<double> direction = position_ - target_;
	direction = normalize(direction);

	vector_3d<double> up{ 0,1,0 };

	vector_3d<double> right = cross(up, direction);
	right = normalize(right);

	up = cross(direction, right);
	up = normalize(up);

	if(up_velocity_ != 0)
	{
		const vector_3d<double> up_vector = up * to_seconds(dt) * up_velocity_;
		position_ += up_vector;
	}
	if(right_velocity_ != 0)
	{
		const vector_3d<double> right_vector = right * to_seconds(dt) * right_velocity_;
		position_ += right_vector;
	}
	if(direction_velocity_ != 0)
	{
		const vector_3d<double> direction_vector = direction * to_seconds(dt) * direction_velocity_;
		position_ += direction_vector;
	}

	//update matrix
	update_matrix();
}

void camera::handle_event(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			direction_velocity_ -= movement_velocity_;
			break;
		case SDLK_DOWN:
			direction_velocity_ += movement_velocity_;
			break;
		case SDLK_LEFT:
			right_velocity_ -= movement_velocity_;
			break;
		case SDLK_RIGHT:
			right_velocity_ += movement_velocity_;
			break;
		case SDLK_PAGEUP:
			up_velocity_ -= movement_velocity_;
			break;
		case SDLK_PAGEDOWN:
			up_velocity_ += movement_velocity_;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			direction_velocity_ += movement_velocity_;
			break;
		case SDLK_DOWN:
			direction_velocity_ -= movement_velocity_;
			break;
		case SDLK_LEFT:
			right_velocity_ += movement_velocity_;
			break;
		case SDLK_RIGHT:
			right_velocity_ -= movement_velocity_;
			break;
		case SDLK_PAGEUP:
			up_velocity_ += movement_velocity_;
			break;
		case SDLK_PAGEDOWN:
			up_velocity_ -= movement_velocity_;
			break;
		}
	}
}

void camera::update_matrix()
{
	vector_3d<double> direction = position_ - target_;
	direction = normalize(direction);

	vector_3d<double> up{ 0,1,0 };

	vector_3d<double> right = cross(up, direction);
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
}
