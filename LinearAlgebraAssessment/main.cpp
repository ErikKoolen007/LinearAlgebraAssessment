#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.h"

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

				std::vector<vector_3d<float> > vectors;
				vectors.emplace_back(1, 0, 0);
				vectors.emplace_back(3, 0, 0);
				vectors.emplace_back(3, 2, 0);
				vectors.emplace_back(1, 2, 0);
				vectors.emplace_back(1, 0, 1);
				vectors.emplace_back(3, 0, 1);
				vectors.emplace_back(3, 0, 0);
				matrix<float> m{ vectors };

				graphics.draw_matrix_top(m, left_viewport);
				graphics.draw_matrix_front(m, middle_viewport);
				graphics.draw_matrix_side(m, right_viewport);
				//Scaling DEMO
				/*m.translate_vector_matrix(-2, -1, -0.5).scale_vector_matrix(2, 2, 2).translate_vector_matrix(2, 1, 0.5);
				graphics.draw_matrix_top(m, left_viewport);
				graphics.draw_matrix_front(m, middle_viewport);
				graphics.draw_matrix_side(m, right_viewport);*/

				//Rotation DEMO
				/*m.translate_vector_matrix(-2, -1, -0.5).x_rotate_vector_matrix(90, true).translate_vector_matrix(2, 1, 0.5);
				graphics.draw_matrix_top(m, left_viewport);
				graphics.draw_matrix_front(m, middle_viewport);
				graphics.draw_matrix_side(m, right_viewport);*/

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
