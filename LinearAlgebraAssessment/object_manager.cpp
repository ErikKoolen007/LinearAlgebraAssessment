#include "object_manager.h"
#include "vector_3d.h"
#include <vector>
#include "space_ship.h"
#include "space_rock.h"
#include "math_class.h"

void object_manager::create_ship()
{
	const std::vector<vector_3d<float>> ship_vectors
	{
		{-5, 0, 0}, {-0.5, 0, 4}, {0.5, 0, 4}, {5, 0, 0}, {-5, 0, 0}, {-0.5, -1, 0}, {-0.5, 0, 4}, {0.5, 0, 4},
		{0.5, -1, 0}, {5, 0, 0}
	};

	objects_.push_back(std::make_unique<space_ship>(ship_vectors));
}

void object_manager::create_space_rock(vector_3d<float> position)
{
	std::vector<vector_3d<float>> rock_vectors
	{
		{0, -2, 0}, {2, 0, 0}, {0, 2, 0}, {-2, 0, 0}, {0, -2, 0}, {0, 0, 2}, {0, 2, 0}, {0, 0, -2},
		{0, -2, 0}
	};

	objects_.push_back(std::make_unique<space_rock>(rock_vectors));
	math_class::translate(position.x(), position.y(), position.z(), objects_.back()->get_matrix());
}
