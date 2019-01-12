#pragma once
#include "vector_3d.h"
#include "matrix.h"

class camera
{
	//Eye
	vector_3d<float> position_;
	//lookat
	vector_3d<float> target_;
	matrix<float> matrix_;

public:
	camera(float x, float y, float z) : position_{ x,y,z }, matrix_(4, 4)
	{
	}

	vector_3d<float>& position() { return position_; }
	vector_3d<float>& target() { return target_; }
	void set_target(const vector_3d<float>& target) { target_.x(target.x()); target_.y(target.y()); target_.z(target.z()); }
	matrix<float> matrix();
};

