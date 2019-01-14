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
		vector_3d<double> forward = forward_vector();
		vector_3d<double> new_position = forward * to_seconds(dt) * current_velocity_;

		math_class::translate(new_position.x(), new_position.y(), new_position.z(), matrix_);
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
		case SDLK_h:
			if (helpline_)
				helpline_ = false;
			else
				helpline_ = true;
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

void space_ship::pitch(double degrees)
{
	math_class::rotate_x(matrix_, degrees, yaw_, roll_);
	add_degrees(pitch_, degrees);
}

void space_ship::yaw(double degrees)
{
	math_class::rotate_y(matrix_, degrees, pitch_, roll_);
	add_degrees(yaw_, degrees);
}

void space_ship::roll(double degrees)
{
	math_class::rotate_z(matrix_, degrees, pitch_, yaw_);
	add_degrees(roll_, degrees);
}

vector_3d<double> space_ship::forward_vector()
{
	std::vector<vector_3d<double>> vectors = matrix_.get_vectors();
	vector_3d<double> point_a = vectors.at(0);
	vector_3d<double> point_b = vectors.at(vectors.size() - 1);
	vector_3d<double> vector_a = point_b - point_a;
	vector_3d<double> point_c = vectors.at(5);
	vector_3d<double> vector_b = point_c - point_a;
	vector_3d<double> vector_c = cross(vector_a, vector_b);

	return normalize(vector_c);
}

void space_ship::reset_rotation()
{
	pitch(-pitch_);
	yaw(-yaw_);
	roll(-roll_);
}

matrix<double> space_ship::create_helpline()
{
	vector_3d<double> sp_center = math_class::centroid(matrix_);
	vector_3d<double> sp_forward = forward_vector();
	sp_forward *= 10;
	vector_3d<double> end_point = sp_center + sp_forward;

	matrix<double> matrix_2D{ 4,2 };
	matrix_2D.init_with_position_vectors(std::vector<vector_3d<double>>{sp_center, end_point});

	return matrix_2D;
}

void space_ship::add_degrees(double& action, double degrees)
{
	if (action + degrees > double(360))
	{
		const double rest = action + degrees - double(360);
		action = rest;
	}
	else if (action + degrees < double(0))
	{
		const double rest = action + degrees;
		action = double(360) + rest;
	}
	else
	{
		action += degrees;
	}
}
