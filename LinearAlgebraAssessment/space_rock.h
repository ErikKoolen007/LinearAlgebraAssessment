#pragma once
#include "base_object.h"

class space_rock : public base_object
{
	matrix<double> matrix_{};
public:
	space_rock(const std::vector<vector_3d<double>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<double>& get_matrix() override { return matrix_; }
	void update(delta_time dt) override{}
	void handle_event(SDL_Event& e) override{}
	std::string name() const override { return "space_rock"; }
};

