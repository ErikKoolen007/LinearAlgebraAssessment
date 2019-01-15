#include "object_manager.h"
#include "vector_3d.h"
#include <vector>
#include "space_ship.h"
#include "space_rock.h"
#include "math_class.h"
#include <algorithm>
#include "planet.h"
#include "bullet.h"

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

void object_manager::create_bullet()
{
	const std::vector<vector_3d<double>> bullet_vectors
	{
		{-0.2, 0.2, 0}, {0.2, 0.2, 0}, {0.2, -0.2, 0}, {-0.2, -0.2, 0}, {-0.2, 0.2, 0}
	};

	//Get spaceship for velocity and heading
	auto sp = dynamic_cast<space_ship*>(get_objects().at(0).get());
	
	//Create bullet
	objects_.push_back(std::make_unique<bullet>(bullet_vectors, sp->get_velocity(), sp->forward_vector()));

	//Set bullet position to spaceship position
	vector_3d<double> ship_loc = math_class::centroid(sp->get_matrix());
	math_class::translate(ship_loc.x(), ship_loc.y(), ship_loc.z(), objects_.back()->get_matrix());
}

void object_manager::update_objects(delta_time dt)
{
	camera_.update(dt);

	for (auto it = objects_.begin(); it != objects_.end() /* !!! */;)
	{
		it->get()->update(dt);

		if (it->get()->name() == "bullet")
		{
			const auto bullet = dynamic_cast<::bullet*>(it->get());
			if (bullet->time_alive() >= max_bullet_existence_time_)
				it = remove_object(*it->get());
			else
				++it;
		}
		else
			++it;
	}
}

void object_manager::handle_object_events(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			create_bullet();
			break;
		}
	}
	camera_.handle_event(e);

	std::for_each(objects_.begin(), objects_.end(), [&](std::unique_ptr<base_object>& object)
	{
		object->handle_event(e);
	});
}

std::vector<std::unique_ptr<base_object>>::iterator object_manager::remove_object(const base_object& b)
{
	return objects_.erase(
		std::remove_if(objects_.begin(), objects_.end(),
			[&b](auto const &ptr) { return &b == ptr.get(); }),
		objects_.end());
}
