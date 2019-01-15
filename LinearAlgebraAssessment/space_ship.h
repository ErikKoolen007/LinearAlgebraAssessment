#pragma once
#include <vector>
#include "base_object.h"
#include "vector_3d.h"

class space_ship : public base_object
{
	matrix<double> matrix_{};
	bool helpline_ = false;

	double pitch_ = 0.0f;
	double yaw_ = 0.0f;
	double roll_ = 0.0f;

	double rotational_velocity_ = 100.f;
	double forward_velocity_ = 40.f;

	double current_velocity_ = 0.f;
	double current_pitch_velocity_ = 0.f;
	double current_yaw_velocity_ = 0.f;
	double current_roll_velocity_ = 0.f;

	static void add_degrees(double& action, double degrees);
public:
	space_ship(const std::vector<vector_3d<double>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<double>& get_matrix() override { return matrix_; }
	void update(delta_time dt) override;
	void handle_event(SDL_Event& e) override;
	std::string name() const override { return "space_ship"; }

	void pitch(double degrees);
	void yaw(double degrees);
	void roll(double degrees);
	vector_3d<double> forward_vector();

	bool helpline() const { return helpline_; }
	void helpline(bool b) { helpline_ = b; }
	matrix<double> create_helpline();

	double get_velocity() const { return current_velocity_; }
};

