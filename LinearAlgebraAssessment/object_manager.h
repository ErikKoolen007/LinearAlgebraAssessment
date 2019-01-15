#pragma once
#include <vector>
#include <memory>
#include "base_object.h"
#include "vector_3d.h"
#include "camera.h"

class object_manager
{
	std::vector<std::unique_ptr<base_object>> objects_;
	camera camera_{ 0, 0, 50 };
	double screen_width_;
	double screen_height_;
	double max_bullet_existence_time_ = 0.5;
	bool game_won_ = false;
	
public:
	object_manager(double screen_width, double screen_height) : screen_width_(screen_width), screen_height_(screen_height)
	{
	}

	void create_ship();
	void create_space_rock(vector_3d<double> position);
	void create_planet(vector_3d<double> position);
	void create_bullet();
	const std::vector<std::unique_ptr<base_object>>& get_objects() const { return objects_; }
	void check_bullet_collision(base_object& bullet);
	void update_objects(delta_time dt);
	void handle_object_events(SDL_Event& e);
	camera& get_camera() { return camera_; }
	std::vector<std::unique_ptr<base_object>>::iterator remove_object(const base_object& b);
	bool game_won() const { return game_won_; }
};

