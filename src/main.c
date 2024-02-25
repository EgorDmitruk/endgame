#include "../inc/header.h"

/* void mx_update(int *last_frame_time) {
	int wait = FRAME_TIME - (SDL_GetTicks() - *last_frame_time);

	if (wait > 0 && wait <= FRAME_TIME)
		SDL_Delay(wait);
} */

void mx_render(SDL_Renderer **renderer) {
	SDL_SetRenderDrawColor(*renderer, 177, 222, 250, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderPresent(*renderer);
}

int main(void) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	int start = mx_create_window(&window, &renderer);

	if (start == true) {
		// int last_frame_time = 0;

		while (start) {
			mx_scan_input(&start);
			// mx_update(&last_frame_time);
			mx_render(&renderer);
		}
	}
	mx_destroy_window(&window, &renderer);
	return 0;
}

