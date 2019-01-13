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
	
public:
	object_manager(double screen_width, double screen_height) : screen_width_(screen_width), screen_height_(screen_height)
	{
	}

	void create_ship();
	void create_space_rock(vector_3d<double> position);
	const std::vector<std::unique_ptr<base_object>>& get_objects() const { return objects_; }
	void update_objects(delta_time dt);
	void handle_object_events(SDL_Event& e);
	const camera& get_camera() const { return camera_; }
};

