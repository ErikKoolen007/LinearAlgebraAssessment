#pragma once
#include "vector_3d.h"
#include "base_object.h"

class camera : public base_object
{
	//Eye
	vector_3d<double> position_;
	//lookat
	vector_3d<double> target_;
	matrix<double> matrix_{4,4};

	double movement_velocity_ = 40;
	double right_velocity_ = 0;
	double up_velocity_ = 0;
	double direction_velocity_ = 0;

public:
	camera(double x, double y, double z) : position_{ x,y,z }
	{
	}

	vector_3d<double>& position() { return position_; }
	vector_3d<double>& target() { return target_; }
	void set_target(const vector_3d<double>& target) { target_.x(target.x()); target_.y(target.y()); target_.z(target.z()); }

	matrix<double>& get_matrix() override { return matrix_; }
	void update(delta_time dt) override;
	void handle_event(SDL_Event& e) override;
	std::string name() const override { return "camera"; }

	void update_matrix();
};

