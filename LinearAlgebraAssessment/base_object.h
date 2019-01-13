#pragma once
#include "clock.h"
#include "matrix.h"
#include <SDL2/SDL.h>

class base_object
{
public:
	base_object() = default;
	virtual ~base_object() = default;

	base_object(const base_object &) = delete;
	base_object(base_object &&) = delete;
	base_object &operator=(const base_object &) = delete;
	base_object &operator=(base_object &&) = delete;

	virtual matrix<double>& get_matrix() = 0;
	virtual void update(delta_time dt){}
	virtual void handle_event(SDL_Event& e){}
};
