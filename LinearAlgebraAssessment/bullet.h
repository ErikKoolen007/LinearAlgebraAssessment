#pragma once
#include "base_object.h"

class bullet : public base_object
{
	matrix<double> matrix_{};
	double start_velocity_ = 0;
	double velocity_ = 200;
	vector_3d<double> heading_;
	delta_time time_alive_{};

public:
	bullet(const std::vector<vector_3d<double>>& vector_draw_points, double start_velocity, vector_3d<double> heading) : 
		start_velocity_(start_velocity), heading_(heading)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	void handle_event(SDL_Event& e) override{}
	void update(delta_time dt) override;
	matrix<double>& get_matrix() override { return matrix_; }
	std::string name() const override { return "bullet"; }

	double time_alive() const { return to_seconds(time_alive_); }
};

