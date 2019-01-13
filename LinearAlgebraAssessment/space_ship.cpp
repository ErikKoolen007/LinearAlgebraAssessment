#include "space_ship.h"
#include "math_class.h"

void space_ship::update(delta_time dt)
{
	if (current_pitch_velocity_ != 0) 
	{
		this->pitch(current_pitch_velocity_ * to_seconds(dt));
	}

	if(current_yaw_velocity_ != 0)
	{
		this->yaw(current_yaw_velocity_ * to_seconds(dt));
	}

	if(current_roll_velocity_ != 0)
	{
		this->roll(current_roll_velocity_ * to_seconds(dt));
	}

	if (current_velocity_ != 0) 
	{
		vector_3d<float> forward = forward_vector();
		vector_3d<float> new_position = forward * to_seconds(dt) * current_velocity_;

		for (unsigned i = 0; i < matrix_.get_cols(); i++) 
		{
			matrix_(0, i) += new_position.x();
			matrix_(1, i) += new_position.y();
			matrix_(2, i) += new_position.z();
		}
	}
}

void space_ship::handle_event(SDL_Event& e)
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) 
	{ 
		switch( e.key.keysym.sym )
		{
		case SDLK_LSHIFT: 
			current_velocity_ += forward_velocity_; 
			break;
		case SDLK_w:
			current_pitch_velocity_ += rotational_velocity_;
			break;
		case SDLK_s:
			current_pitch_velocity_ -= rotational_velocity_;
			break;
		case SDLK_e:
			current_roll_velocity_ += rotational_velocity_;
			break;
		case SDLK_q:
			current_roll_velocity_ -= rotational_velocity_;
			break;
		case SDLK_d:
			current_yaw_velocity_ -= rotational_velocity_;
			break;
		case SDLK_a:
			current_yaw_velocity_ += rotational_velocity_;
			break;
		case SDLK_r:
			reset_rotation();
			break;
		} 
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			current_velocity_ -= forward_velocity_;
			break;
		case SDLK_w:
			current_pitch_velocity_ -= rotational_velocity_;
			break;
		case SDLK_s:
			current_pitch_velocity_ += rotational_velocity_;
			break;
		case SDLK_e:
			current_roll_velocity_ -= rotational_velocity_;
			break;
		case SDLK_q:
			current_roll_velocity_ += rotational_velocity_;
			break;
		case SDLK_d:
			current_yaw_velocity_ += rotational_velocity_;
			break;
		case SDLK_a:
			current_yaw_velocity_ -= rotational_velocity_;
			break;
		}
	}
}

void space_ship::pitch(float degrees)
{
	math_class::rotate_x(matrix_, degrees, yaw_, roll_);
	add_degrees(pitch_, degrees);
}

void space_ship::yaw(float degrees)
{
	math_class::rotate_y(matrix_, degrees, pitch_, roll_);
	add_degrees(yaw_, degrees);
}

void space_ship::roll(float degrees)
{
	math_class::rotate_z(matrix_, degrees, pitch_, yaw_);
	add_degrees(roll_, degrees);
}

vector_3d<float> space_ship::forward_vector()
{
	std::vector<vector_3d<float>> vectors = matrix_.get_vectors();
	vector_3d<float> point_a = vectors.at(0);
	vector_3d<float> point_b = vectors.at(vectors.size() - 1);
	vector_3d<float> vector_a = point_b - point_a;
	vector_3d<float> point_c = vectors.at(5);
	vector_3d<float> vector_b = point_c - point_a;
	vector_3d<float> vector_c = cross(vector_b, vector_a);

	return normalize(vector_c);
}

void space_ship::reset_rotation()
{
	pitch(-pitch_);
	yaw(-yaw_);
	roll(-roll_);
}

void space_ship::add_degrees(float& action, float degrees)
{
	if (action + degrees > 360)
	{
		const float rest = action + degrees - 360;
		action = rest;
	}
	else if (action + degrees < 0)
	{
		const float rest = action + degrees;
		action = 360 + rest;
	}
	else
	{
		action += degrees;
	}
}
