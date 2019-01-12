#pragma once
#include "vector_3d.h"
#include "base_object.h"

class space_rock : public base_object
{
	matrix<float> matrix_{};
public:
	space_rock(const std::vector<vector_3d<float>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<float>& get_matrix() override { return matrix_; }
	void move(delta_time dt) override{}
	void handle_event(SDL_Event& e) override{}
};

