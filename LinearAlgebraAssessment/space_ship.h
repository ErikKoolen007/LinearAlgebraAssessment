#pragma once
#include "vector_3d.h"
#include <vector>
#include "base_object.h"

class space_ship : public base_object
{
	float pitch_ = 0.0f;
	float yaw_ = 0.0f;
	float roll_ = 0.0f;
	matrix<float> matrix_{};

	static void add_degrees(float& action, float degrees);
public:
	space_ship(const std::vector<vector_3d<float>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<float>& get_matrix() override { return matrix_; }
	void move(delta_time dt) override{}
	void handle_event(SDL_Event& e) override{}

	void pitch(float degrees);
	void yaw(float degrees);
	void roll(float degrees);
};

