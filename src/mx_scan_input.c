#include "../inc/header.h"

void mx_scan_input(int *start) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			*start = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					*start = false;
					break;
			}
			break;
	}
}

