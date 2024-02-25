#include "../inc/header.h"

bool mx_create_window(SDL_Window **window, SDL_Renderer **renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		mx_printerr("error initialising SDL\n");
		return false;
	}
	*window = SDL_CreateWindow("ENDGAME",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WIN_WIDTH,
							  WIN_HEIGHT,
							  0);
	if (*window == NULL) {
		mx_printerr("error creating window\n");
		return false;
	}
	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL) {
		mx_printerr("error creating renderer\n");
		return false;
	}
	return true;
}

