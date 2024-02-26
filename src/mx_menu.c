#include "../inc/header.h"

void mx_menu(SDL_Window **window, SDL_Renderer **renderer,
			 int *start, int *start_play, int *last_frame_time) {
	SDL_Texture *start_background_tex = mx_change_background("./resources/images/StartMenuImage.png",
															 renderer);
	if (start_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Texture *about_us_background_tex = mx_change_background("./resources/images/Image2.png",
															 renderer);
	if (about_us_background_tex == NULL) {
		SDL_DestroyTexture(start_background_tex);
		mx_destroy_window(window, renderer);
		exit(1);
	}
	mx_play_menu_music("./resources/music/StartMenuMusic.mp3");

	// create start menu buttons
	SDL_Rect play_button;
	SDL_Texture *play_button_tex = mx_create_button("./resources/images/buttons/play.png",
													renderer, &play_button, 610);
	if (play_button_tex == NULL) {
		SDL_DestroyTexture(start_background_tex);
		SDL_DestroyTexture(about_us_background_tex);
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect music_button;
	SDL_Texture *music_button_tex = mx_create_button("./resources/images/buttons/music.png",
													 renderer, &music_button, 490);
	if (music_button_tex == NULL) {
		SDL_DestroyTexture(start_background_tex);
		SDL_DestroyTexture(about_us_background_tex);
		SDL_DestroyTexture(play_button_tex);
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect about_us_button;
	SDL_Texture *about_us_button_tex = mx_create_button("./resources/images/buttons/about_us.png",
														renderer, &about_us_button, 370);
	if (about_us_button_tex == NULL) {
		SDL_DestroyTexture(start_background_tex);
		SDL_DestroyTexture(about_us_background_tex);
		SDL_DestroyTexture(play_button_tex);
		SDL_DestroyTexture(music_button_tex);
		mx_destroy_window(window, renderer);
		exit(1);
	}
	int start_about_us = false;
	SDL_Rect exit_button;
	SDL_Texture *exit_button_tex = mx_create_button("./resources/images/buttons/exit.png",
													renderer, &exit_button, 250);
	if (exit_button_tex == NULL) {
		SDL_DestroyTexture(start_background_tex);
		SDL_DestroyTexture(about_us_background_tex);
		SDL_DestroyTexture(play_button_tex);
		SDL_DestroyTexture(music_button_tex);
		SDL_DestroyTexture(about_us_button_tex);
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// start menu loop
	int start_menu = true;
	while (*start && start_menu) {
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				*start = false; // quit
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					start_about_us = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (event.button.x > (WIN_WIDTH - play_button.w) / 2
						&& event.button.x < (WIN_WIDTH - play_button.w) / 2 + play_button.w
						&& event.button.y > (WIN_HEIGHT - play_button.h) - 610
						&& event.button.y < (WIN_HEIGHT - play_button.h) - 610 + play_button.h) {
							if (!start_about_us) {
								start_menu = false; // finish menu loop
								*start_play = true; // play
							}
					}
					else if (event.button.x > (WIN_WIDTH - music_button.w) / 2
						&& event.button.x < (WIN_WIDTH - music_button.w) / 2 + music_button.w
						&& event.button.y > (WIN_HEIGHT - music_button.h) - 490
						&& event.button.y < (WIN_HEIGHT - music_button.h) - 490 + music_button.h) {
							if (!start_about_us) {
								if (Mix_VolumeMusic(-1) != 0)
									Mix_VolumeMusic(0); // no sound
								else
									Mix_VolumeMusic(MIX_MAX_VOLUME); // max sound
							}
					}
					else if (event.button.x > (WIN_WIDTH - about_us_button.w) / 2
						&& event.button.x < (WIN_WIDTH - about_us_button.w) / 2 + about_us_button.w
						&& event.button.y > (WIN_HEIGHT - about_us_button.h) - 370
						&& event.button.y < (WIN_HEIGHT - about_us_button.h) - 370 + about_us_button.h) {
							start_about_us = true; // open about us
					}
					else if (event.button.x > (WIN_WIDTH - exit_button.w) / 2
						&& event.button.x < (WIN_WIDTH - exit_button.w) / 2 + exit_button.w
						&& event.button.y > (WIN_HEIGHT - exit_button.h) - 250
						&& event.button.y < (WIN_HEIGHT - exit_button.h) - 250 + exit_button.h) {
							if (!start_about_us) {
								*start = false; // quit
							}
					}
				}
				break;
		}
		mx_menu_update(last_frame_time);
		SDL_RenderClear(*renderer);
		if (start_about_us) {
			SDL_RenderCopy(*renderer, about_us_background_tex, NULL, NULL);
		}
		else {
			SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
			SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
			SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
		}
    	SDL_RenderPresent(*renderer);
	}
	SDL_DestroyTexture(start_background_tex);
	SDL_DestroyTexture(about_us_background_tex);
    SDL_DestroyTexture(play_button_tex);
	SDL_DestroyTexture(music_button_tex);
	SDL_DestroyTexture(about_us_button_tex);
    SDL_DestroyTexture(exit_button_tex);
}

