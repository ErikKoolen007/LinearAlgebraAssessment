#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.h"
#include "space_ship.h"
#include "math_class.h"

//undef (macro)main to be able to let the linker find the non SDL main.
#undef main

void run()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		const float screen_buffer = 10;
		const float screen_count = 3;
		const float grid_size = 20;
		const float screen_width = 1500 + screen_buffer * screen_count;
		const float screen_height = 500 + screen_buffer;

		if (SDL_CreateWindowAndRenderer(static_cast<int>(screen_width), static_cast<int>(screen_height), 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			SDL_bool paused = SDL_TRUE;
			SDL_Event event;
			graphics graphics{ *renderer, screen_width / screen_count, screen_height, screen_buffer, grid_size };

			while (!done) {

				//Clear screen
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				//Left viewport 
				SDL_Rect left_viewport;
				left_viewport.x = 0;
				left_viewport.y = 0;
				left_viewport.w = screen_width / 3;
				left_viewport.h = screen_height;

				//Middle viewport 
				SDL_Rect middle_viewport;
				middle_viewport.x = screen_width / 3;
				middle_viewport.y = 0;
				middle_viewport.w = screen_width / 3;
				middle_viewport.h = screen_height;

				//Right viewport 
				SDL_Rect right_viewport;
				right_viewport.x = screen_width / 3 * 2;
				right_viewport.y = 0;
				right_viewport.w = screen_width / 3;
				right_viewport.h = screen_height;

				//Draw coordinate grid
				graphics.draw_coordinate_grid(left_viewport);
				graphics.draw_coordinate_grid(middle_viewport);
				graphics.draw_coordinate_grid(right_viewport);

				//Create space ship and translate, rotate and scale it
				space_ship space_ship{};
				math_class::translate(4, -2, -4, space_ship.matrix());
				//space_ship.pitch(5);
				//space_ship.pitch(40);
				space_ship.roll(45);
				space_ship.yaw(90);
				//math_class::scale(2, 2, 2, space_ship.line_matrix());

				vector_3d<float> center_point = math_class::centroid(space_ship.matrix());
				vector_3d<float> point_a = space_ship.matrix().get_vectors().at(0);
				vector_3d<float> point_b = space_ship.matrix().get_vectors().at(space_ship.matrix().get_vectors().size() - 1);
				vector_3d<float> vector_a = point_b - point_a;
				vector_3d<float> point_c = space_ship.matrix().get_vectors().at(5);
				vector_3d<float> vector_b = point_c - point_a;
				vector_3d<float> vector_c = cross(vector_a, vector_b);

				//Draw space ship
				graphics.draw_matrix_top(space_ship.matrix(), left_viewport);
				graphics.draw_matrix_front(space_ship.matrix(), middle_viewport);
				graphics.draw_vector(vector_c, center_point.x(), center_point.y());
				graphics.draw_matrix_side(space_ship.matrix(), right_viewport);

				float x = vector_c.x();
				float z = vector_c.z();
				vector_c.z(x);
				vector_c.x(z);
				graphics.draw_vector(vector_c, center_point.z(), center_point.y());

				//Update screen
				SDL_RenderPresent(renderer);

				//Pause the rendering
				while (paused)
				{
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_QUIT) {
							done = SDL_TRUE;
							paused = SDL_FALSE;
						}
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	run();
	std::cout << "Memory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
	return 0;
}
