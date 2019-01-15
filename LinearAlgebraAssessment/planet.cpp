#include "planet.h"
#include "math_class.h"

void planet::update(delta_time dt)
{
	t_since_scaling_ += dt;
	if (to_seconds(t_since_scaling_) >= waiting_time_) {
		if (growing_)
		{
			current_scale_ *= scale_factor_;
			math_class::scale(scale_factor_, scale_factor_, scale_factor_, matrix_);
			if (current_scale_ >= max_scale_)
				growing_ = false;
		}
		else
		{
			const double inverted_scale = 1 / scale_factor_;
			current_scale_ *= 1 / scale_factor_;
			math_class::scale(inverted_scale, inverted_scale, inverted_scale, matrix_);
			if (current_scale_ <= min_scale_)
				growing_ = true;
		}

		t_since_scaling_ = from_seconds(0);
	}
}

bounding_box planet::get_bounding_box() 
{
	auto vector_list = matrix_.get_vectors();
	const double min_x = vector_list.at(0).x();
	const double min_y = vector_list.at(0).y();
	const double min_z = vector_list.at(0).z();
	const double max_x = vector_list.at(3).x();
	const double max_y = vector_list.at(3).y();
	const double max_z = vector_list.at(3).z();

	return bounding_box{ min_x, min_y, min_z, max_x, max_y, max_z };
}
