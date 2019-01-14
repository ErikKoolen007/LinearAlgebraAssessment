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
