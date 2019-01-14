#include "object_manager.h"
#include "vector_3d.h"
#include <vector>
#include "space_ship.h"
#include "space_rock.h"
#include "math_class.h"
#include <algorithm>
#include "planet.h"

void object_manager::create_ship()
{
	const std::vector<vector_3d<double>> ship_vectors
	{
		{-5, 0, 0}, {-0.5, 0, -4}, {0.5, 0, -4}, {5, 0, 0}, {-5, 0, 0}, {-0.5, -1, 0}, {-0.5, 0, -4}, {0.5, 0, -4},
		{0.5, -1, 0}, {5, 0, 0}
	};

	objects_.push_back(std::make_unique<space_ship>(ship_vectors));
}

void object_manager::create_space_rock(vector_3d<double> position)
{
	std::vector<vector_3d<double>> rock_vectors
	{
		{0, -2, 0}, {2, 0, 0}, {0, 2, 0}, {-2, 0, 0}, {0, -2, 0}, {0, 0, 2}, {0, 2, 0}, {0, 0, -2},
		{0, -2, 0}
	};

	objects_.push_back(std::make_unique<space_rock>(rock_vectors));
	math_class::translate(position.x(), position.y(), position.z(), objects_.back()->get_matrix());
}

void object_manager::create_planet(vector_3d<double> position)
{
	const std::vector<vector_3d<double>> planet_vectors
	{
		{0, 0, 0}, {0, 0, 1}, {0, 1, 1}, {1, 1, 1}, {1, 1, 0}, {0, 1, 0}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1},
		{0, 0, 1}, {0, 1, 1}, {0, 1, 0}, {1, 1, 0}, {1, 0, 0}, {1, 0, 1}, {1, 1, 1}
	};

	objects_.push_back(std::make_unique<planet>(planet_vectors));
	math_class::translate(position.x(), position.y(), position.z(), objects_.back()->get_matrix());
}

void object_manager::update_objects(delta_time dt)
{
	camera_.update(dt);

	std::for_each(objects_.begin(), objects_.end(), [&](std::unique_ptr<base_object>& object)
	{
		object->update(dt);
	});
}

void object_manager::handle_object_events(SDL_Event& e)
{
	camera_.handle_event(e);

	std::for_each(objects_.begin(), objects_.end(), [&](std::unique_ptr<base_object>& object)
	{
		object->handle_event(e);
	});
}
