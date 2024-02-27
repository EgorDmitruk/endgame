#include "../inc/header.h"

int main(void) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	mx_create_window(&window, &renderer);

	int start = true;
	int start_play = false;
	mx_menu(&window, &renderer, &start, &start_play);
	if (start == true && start_play == true)
		mx_game(&window, &renderer, &start, &start_play);

	mx_destroy_window(&window, &renderer);

	return 0;
}

