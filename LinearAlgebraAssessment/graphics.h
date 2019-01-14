#pragma once
#include <SDL2/SDL.h>
#include "vector_3d.h"
#include "matrix.h"

class graphics
{
	SDL_Renderer* renderer_;
	const matrix<double>* camera_matrix_;
	double screen_width_;
	double screen_height_;
	double center_x_;
	double center_y_;
public:
	graphics(SDL_Renderer& renderer, const matrix<double>& camera_matrix, double screen_width, double screen_height) :
		renderer_(&renderer), camera_matrix_(&camera_matrix), screen_width_(screen_width), screen_height_(screen_height)
	{
		center_x_ = screen_width / 2;
		center_y_ = screen_height / 2;
	}

	void draw_matrix(const matrix<double>& m) const;
	void draw_line(vector_3d<double> point_a, vector_3d<double> point_b) const;
};

