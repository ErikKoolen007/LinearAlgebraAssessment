#pragma once
#include "vector_3d.h"
#include "matrix.h"

class camera
{
	//Eye
	vector_3d<double> position_;
	//lookat
	vector_3d<double> target_;

public:
	camera(double x, double y, double z) : position_{ x,y,z }
	{
	}

	vector_3d<double>& position() { return position_; }
	vector_3d<double>& target() { return target_; }
	void set_target(const vector_3d<double>& target) { target_.x(target.x()); target_.y(target.y()); target_.z(target.z()); }
	matrix<double> get_matrix() const;
};

