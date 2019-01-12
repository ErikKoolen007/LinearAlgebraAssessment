#pragma once
#include <vector>
#include <memory>
#include "base_object.h"
#include "vector_3d.h"
#include "camera.h"

class object_manager
{
	std::vector<std::unique_ptr<base_object>> objects_;
	camera camera_{ 0, 50, 50 };
	float screen_width_;
	float screen_height_;
	
public:
	object_manager(float screen_width, float screen_height) : screen_width_(screen_width), screen_height_(screen_height)
	{
	}

	void create_ship();
	void create_space_rock(vector_3d<float> position);
	const std::vector<std::unique_ptr<base_object>>& get_objects() const { return objects_; }
	void update_objects(delta_time dt);
	void handle_object_events(SDL_Event& e);
};

