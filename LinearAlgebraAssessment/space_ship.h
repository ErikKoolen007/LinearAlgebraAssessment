#pragma once
#include "vector_3d.h"
#include <vector>
#include "matrix.h"

class space_ship
{
	float pitch_ = 0.0f;
	float yaw_ = 0.0f;
	float roll_ = 0.0f;
	matrix<float> matrix_{};

	static void add_degrees(float& action, float degrees);
public:
	space_ship()
	{
		const std::vector<vector_3d<float>> line_vectors
		{
			{-5,0,0},{-0.5,0,4},{0.5,0,4},{5,0,0},{-5,0,0},{-0.5,-1,0},{-0.5,0,4},{0.5,0,4},{0.5,-1,0},{5,0,0}
		};
		matrix_.init_with_position_vectors(line_vectors);
	}

	matrix<float>& matrix() { return matrix_; }

	void pitch(float degrees);
	void yaw(float degrees);
	void roll(float degrees);
};

