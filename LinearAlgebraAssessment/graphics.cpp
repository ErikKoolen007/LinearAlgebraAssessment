#include "graphics.h"
#include "math_class.h"

void graphics::draw_matrix(const matrix<double>& m) const
{
	matrix<double> matrix_3D = math_class::convert_to_3d(m, *camera_matrix_, screen_width_, screen_height_);

	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);

	for (unsigned i = 0; i < matrix_3D.get_cols(); i++) 
	{
		if (i != 0 && matrix_3D(3, i) > 0)
		{
			const int previous_point_x = matrix_3D(0, i - 1);
			const int previous_point_y = matrix_3D(1, i - 1);
			const int current_point_x = matrix_3D(0, i);
			const int current_point_y = matrix_3D(1, i);
			SDL_RenderDrawLine(renderer_, previous_point_x, previous_point_y, current_point_x, current_point_y);
		}
	}
}

void graphics::draw_line(vector_3d<double> point_a, vector_3d<double> point_b) const
{
	matrix<double> matrix_2D{ 4,2 };
	matrix_2D.init_with_position_vectors(std::vector<vector_3d<double>>{point_a, point_b});

	draw_matrix(matrix_2D);
}
