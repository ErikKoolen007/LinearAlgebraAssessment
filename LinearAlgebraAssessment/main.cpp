#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.h"
#include "object_manager.h"
#include <algorithm>
#include "clock.h"
#include "space_ship.h"
#include "math_class.h"

//undef (macro)main to be able to let the linker find the non SDL main.
#undef main

void run()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;

		const double screen_width = 1920;
		const double screen_height = 1080;

		if (SDL_CreateWindowAndRenderer(static_cast<int>(screen_width), static_cast<int>(screen_height), 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			SDL_Event event;
			timer::time_point t_prev = now();

			object_manager object_manager{screen_width, screen_height};
			object_manager.create_ship();
			object_manager.create_space_rock(vector_3d<double>{10, 10, 10});
			object_manager.create_space_rock(vector_3d<double>{20, 20, 20});
			object_manager.create_space_rock(vector_3d<double>{-10, -10, 10});

			graphics graphics{ *renderer, object_manager.get_camera().get_matrix(), screen_width, screen_height };
			
			while (!done) {

				//Calculate delta time
				timer::time_point t_current = now();
				delta_time dt = t_current - t_prev;
				t_prev = t_current;

				//Handle events on queue
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}

					//Handle input for the objects
					object_manager.handle_object_events(event);
				}

				//Update the objects
				object_manager.update_objects(dt);
				
				//Clear screen
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				
				//Render objects
				std::for_each(object_manager.get_objects().begin(), object_manager.get_objects().end(), [&](auto& object)
				{
					graphics.draw_matrix(object->get_matrix());
				});

				//create hardcoded helpline
				auto sp = dynamic_cast<space_ship*>(object_manager.get_objects().at(0).get());
				vector_3d<double> sp_center = math_class::centroid(sp->get_matrix());
				vector_3d<double> sp_forward = sp->forward_vector();
				sp_forward *= 10;
				vector_3d<double> end_point = sp_center + sp_forward;
				graphics.draw_line(sp_center, end_point);

				//Update screen
				SDL_RenderPresent(renderer);
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
