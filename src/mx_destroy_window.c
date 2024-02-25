#include "../inc/header.h"

void mx_destroy_window(SDL_Window **window, SDL_Renderer **renderer) {
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	SDL_Quit();
}

