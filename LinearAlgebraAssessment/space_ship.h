#pragma once
#include <vector>
#include "base_object.h"
#include "vector_3d.h"

class space_ship : public base_object
{
	matrix<float> matrix_{};

	float pitch_ = 0.0f;
	float yaw_ = 0.0f;
	float roll_ = 0.0f;

	float rotational_velocity_ = 100.f;
	float forward_velocity_ = 200.f;

	float current_velocity_ = 0.f;
	float current_pitch_velocity_ = 0.f;
	float current_yaw_velocity_ = 0.f;
	float current_roll_velocity_ = 0.f;

	static void add_degrees(float& action, float degrees);
public:
	space_ship(const std::vector<vector_3d<float>>& vector_draw_points)
	{
		matrix_.init_with_position_vectors(vector_draw_points);
	}

	matrix<float>& get_matrix() override { return matrix_; }
	void update(delta_time dt) override;
	void handle_event(SDL_Event& e) override;

	void pitch(float degrees);
	void yaw(float degrees);
	void roll(float degrees);
	vector_3d<float> forward_vector();
	void reset_rotation();
};

