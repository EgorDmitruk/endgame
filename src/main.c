#include "../inc/header.h"

int main(void) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	mx_create_window(&window, &renderer);

	int start = true;
	int start_play = false;
	int last_frame_time = 0;
	mx_menu(&window, &renderer, &start, &start_play, &last_frame_time);

	// play loop
	while (start && start_play) {
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				start = false; // quit
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					//
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					
				}
				break;
		}
		mx_menu_update(&last_frame_time);
	}

	mx_destroy_window(&window, &renderer);

	return 0;
}

