#include "../inc/header.h"

void mx_create_window(SDL_Window **window, SDL_Renderer **renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		mx_printerr("error initialising SDL: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
		exit(1);
	}

	*window = SDL_CreateWindow("ENDGAME",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WIN_WIDTH, WIN_HEIGHT, 0);
	if (*window == NULL) {
		mx_printerr("error creating window: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
		SDL_Quit();
		exit(1);
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL) {
		mx_printerr("error creating renderer: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
		SDL_DestroyWindow(*window);
		SDL_Quit();
		exit(1);
	}
}

