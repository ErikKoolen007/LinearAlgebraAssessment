#pragma once
#include "space_ship.h"

class object_manager
{
	std::vector<std::unique_ptr<base_object>> objects_;
	
public:
	object_manager() = default;

	void create_ship();
	void create_space_rock(vector_3d<float> position);

	const std::vector<std::unique_ptr<base_object>>& get_objects() const { return objects_; }
};

