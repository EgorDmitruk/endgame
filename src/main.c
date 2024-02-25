#include "../inc/header.h"

void mx_update(int *last_frame_time) {
	int wait = FRAME_TIME - (SDL_GetTicks() - *last_frame_time);

	if (wait > 0 && wait <= FRAME_TIME)
		SDL_Delay(wait);
} 

int main(void) {
	SDL_Init(SDL_INIT_AUDIO);
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	mx_create_window(&window, &renderer);
	int start = true;
	int last_frame_time = 0;
	mx_change_background("./resoursec/images/StartMenuImage.png", &renderer);
	mx_play_menu_music("./resoursec/music/StartMenuMusic.mp3");

	while (start) {
		mx_scan_input(&start);
		mx_update(&last_frame_time);
		// mx_render(&renderer);
	}

	mx_destroy_window(&window, &renderer);

	return 0;
}

