#pragma once
#include "base_object.h"

class planet : public base_object
{
	matrix<double> matrix_{};

	double scale_factor_ = 1.1;
	double max_scale_ = 10;
	double min_scale_ = 1;
	double current_scale_ = 1;
	bool growing_ = true;

	double waiting_time_ = 0.1;
	delta_time t_since_scaling_{};

public:
	planet(const std::vector<vector_3d<double>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<double>& get_matrix() override { return matrix_; }
	void update(delta_time dt) override;
	void handle_event(SDL_Event& e) override {}
	std::string name() const override { return "planet"; }
};

