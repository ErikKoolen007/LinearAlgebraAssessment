#include "graphics.h"

void graphics::draw_matrix(matrix<float>& m) const
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);

	for (unsigned i = 0; i < m.get_cols(); i++) {

		if (i != 0)
		{
			const int previous_point_x = m(0, i - 1);
			const int previous_point_y = m(1, i - 1);
			const int current_point_x = m(0, i);
			const int current_point_y = m(1, i);
			SDL_RenderDrawLine(renderer_, previous_point_x, previous_point_y, current_point_x, current_point_y);
		}
	}
}

void graphics::draw_line(vector_3d<float> point_a, vector_3d<float> point_b) const
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer_, point_a.x(), point_a.y(), point_b.x(), point_b.y());
}
