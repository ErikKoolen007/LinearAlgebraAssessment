#pragma once
#include <SDL2/SDL.h>
#include "vector_3d.h"
#include "matrix.h"

class graphics
{
	SDL_Renderer* renderer_;
	float center_x_;
	float center_y_;
	float end_x_;
	float end_y_;
	float zero_;
	float step_;
public:
	graphics(SDL_Renderer& renderer, float screen_width, float screen_height, float screen_buffer, float grid_size) :
		renderer_(&renderer)
	{
		center_x_ = screen_width / 2;
		center_y_ = screen_height / 2;
		end_x_ = screen_width - screen_buffer / 2;
		end_y_ = screen_height - screen_buffer / 2;
		zero_ = screen_buffer / 2;
		step_ = (screen_width - screen_buffer) / grid_size;
	}

	void draw_coordinate_grid(SDL_Rect& viewport) const;
	void draw_vector(vector_3d<float>& vector, float start_x = 0, float start_y = 0) const;
	void draw_matrix_front(matrix<float> m, SDL_Rect& viewport) const;
	void draw_matrix_top(matrix<float> m, SDL_Rect& viewport) const;
	void draw_matrix_side(matrix<float> m, SDL_Rect& viewport) const;
	void draw_point(vector_3d<float>& vector) const;
	void draw_matrix(matrix<float>& m);
};

