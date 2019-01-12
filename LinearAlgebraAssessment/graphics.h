#pragma once
#include <SDL2/SDL.h>
#include "vector_3d.h"
#include "matrix.h"

class graphics
{
	SDL_Renderer* renderer_;
	float screen_width_;
	float screen_height_;
	float center_x_;
	float center_y_;
public:
	graphics(SDL_Renderer& renderer, float screen_width, float screen_height) : 
		renderer_(&renderer), screen_width_(screen_width), screen_height_(screen_height)
	{
		center_x_ = screen_width / 2;
		center_y_ = screen_height / 2;
	}

	void draw_matrix(matrix<float>& m) const;
};

