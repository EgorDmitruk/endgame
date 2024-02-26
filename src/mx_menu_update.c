#include "../inc/header.h"

void mx_menu_update(int *last_frame_time) {
	int wait = FRAME_TIME - (SDL_GetTicks() - *last_frame_time);

	if (wait > 0 && wait <= FRAME_TIME)
		SDL_Delay(wait);
}

