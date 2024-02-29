#include "../inc/header.h"

int main(void) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	mx_create_window(&window, &renderer);

	int start = true;
	int start_menu = true;
	int start_play = false;
	int start_end = false;
	uint32_t start_time;
	uint32_t pause_time = 0;
	while (start == true) {
		if (start_menu == true)
			mx_menu(&window, &renderer, &start, &start_play, &start_menu);
		if (start_play == true)
			mx_game(&window, &renderer, &start, &start_play,
					&start_end, &start_time, &pause_time);
		if (start_end == true)
			mx_end_menu(&window, &renderer, &start, &start_play, &start_menu,
						&start_end, &start_time, &pause_time);
	}

	mx_destroy_window(&window, &renderer);

	return 0;
}

