#include "../inc/header.h"

void mx_menu(SDL_Window **window, SDL_Renderer **renderer,
			 int *start, int *start_play) {
	SDL_Texture *start_background_tex = mx_change_background("./resources/images/StartMenuImage.png",
															 renderer);
	if (start_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Texture *about_us_background_tex = mx_change_background("./resources/images/about_us_background.png",
																renderer);
	if (about_us_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	mx_play_menu_music("./resources/music/StartMenuMusic.mp3");
	Mix_Chunk *ChoiceButtonSoundEffect = Mix_LoadWAV("./resources/music/ChoiceButtonSoundEffect.wav");

	// create start menu buttons
	int pd = 610;
	int md = 470;
	int ad = 330;
	int ed = 190;

	// play buttons
	SDL_Rect play_button;
	SDL_Texture *play_button_tex = mx_create_button("./resources/images/buttons/play.png",
													renderer, &play_button, pd, 0, 2, 1);
	if (play_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect play_glow_button;
	SDL_Texture *play_glow_button_tex = mx_create_button("./resources/images/buttons/play_glow.png",
														 renderer, &play_glow_button, pd, 0, 2, 1);
	if (play_glow_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// music buttons
	SDL_Rect music_button;
	SDL_Texture *music_button_tex = mx_create_button("./resources/images/buttons/music.png",
													 renderer, &music_button, md, 0, 2, 1);
	if (music_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect music_glow_button;
	SDL_Texture *music_glow_button_tex = mx_create_button("./resources/images/buttons/music_glow.png",
													 	  renderer, &music_glow_button, md, 0, 2, 1);
	if (music_glow_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// about us buttons
	SDL_Rect about_us_button;
	SDL_Texture *about_us_button_tex = mx_create_button("./resources/images/buttons/about_us.png",
														renderer, &about_us_button, ad, 0, 2, 1);
	if (about_us_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect about_us_glow_button;
	SDL_Texture *about_us_glow_button_tex = mx_create_button("./resources/images/buttons/about_us_glow.png",
															 renderer, &about_us_glow_button, ad, 0, 2, 1);
	if (about_us_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	int start_about_us = false;

	// exit buttons
	SDL_Rect exit_button;
	SDL_Texture *exit_button_tex = mx_create_button("./resources/images/buttons/exit.png",
													renderer, &exit_button, ed, 0, 2, 1);
	if (exit_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect exit_glow_button;
	SDL_Texture *exit_glow_button_tex = mx_create_button("./resources/images/buttons/exit_glow.png",
														 renderer, &exit_glow_button, ed, 0, 2, 1);
	if (exit_glow_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	SDL_RenderClear(*renderer);
	SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
	SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
	SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
	SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);
	SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
	SDL_RenderPresent(*renderer);

	int changes = false;
	int mouse_on_button = false;

	// start menu loop
	int start_menu = true;
	while (*start && start_menu) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					*start = false; // quit
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						start_about_us = false; // close about us
						changes = true;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (event.button.x > play_button.x
							&& event.button.x < play_button.x + play_button.w
							&& event.button.y > play_button.y
							&& event.button.y < play_button.y + play_button.h) {
								if (!start_about_us) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									start_menu = false; // finish menu loop
									*start_play = true; // play
									changes = true;
								}
						}
						else if (event.button.x > music_button.x
							&& event.button.x < music_button.x + music_button.w
							&& event.button.y > music_button.y
							&& event.button.y < music_button.y + music_button.h) {
								if (!start_about_us) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									if (Mix_VolumeMusic(-1) != 0)
										Mix_VolumeMusic(0); // no sound
									else
										Mix_VolumeMusic(MIX_MAX_VOLUME); // max sound
									changes = true;
								}
						}
						else if (event.button.x > about_us_button.x
							&& event.button.x < about_us_button.x + about_us_button.w
							&& event.button.y > about_us_button.y
							&& event.button.y < about_us_button.y + about_us_button.h) {
								if (!start_about_us) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									start_about_us = true; // open about us
									changes = true;
								}
						}
						else if (event.button.x > exit_button.x
							&& event.button.x < exit_button.x + exit_button.w
							&& event.button.y > exit_button.y
							&& event.button.y < exit_button.y + exit_button.h) {
								if (!start_about_us)
									*start = false; // quit
						}
					}
					break;
			}
		}
		SDL_Delay(100);

		int x;
		int y;
		SDL_GetMouseState(&x, &y);
		if (x > play_button.x && x < play_button.x + play_button.w
			&& y > play_button.y && y < play_button.y + play_button.h && !start_about_us) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
			SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);

			SDL_RenderCopy(*renderer, play_glow_button_tex, NULL, &play_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else if (x > music_button.x && x < music_button.x + music_button.w
			&& y > music_button.y && y < music_button.y + music_button.h && !start_about_us) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
			SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);

			SDL_RenderCopy(*renderer, music_glow_button_tex, NULL, &music_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else if (x > about_us_button.x && x < about_us_button.x + about_us_button.w
			&& y > about_us_button.y && y < about_us_button.y + about_us_button.h && !start_about_us) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
			SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);

			SDL_RenderCopy(*renderer, about_us_glow_button_tex, NULL, &about_us_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else if (x > exit_button.x && x < exit_button.x + exit_button.w
			&& y > exit_button.y && y < exit_button.y + exit_button.h && !start_about_us) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
			SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
			SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);

			SDL_RenderCopy(*renderer, exit_glow_button_tex, NULL, &exit_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else {
			if (mouse_on_button == true) {
				mouse_on_button = false;
				changes = true;
			}
		}
		if (changes == true) {
			SDL_RenderClear(*renderer);
			if (start_about_us)
				SDL_RenderCopy(*renderer, about_us_background_tex, NULL, NULL);
			else {
				SDL_RenderCopy(*renderer, start_background_tex, NULL, NULL);
				SDL_RenderCopy(*renderer, play_button_tex, NULL, &play_button);
				SDL_RenderCopy(*renderer, music_button_tex, NULL, &music_button);
				SDL_RenderCopy(*renderer, about_us_button_tex, NULL, &about_us_button);
				SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
			}
    		changes = false;
    		SDL_RenderPresent(*renderer);
    	}
	}
	SDL_DestroyTexture(start_background_tex);
	SDL_DestroyTexture(about_us_background_tex);
    SDL_DestroyTexture(play_button_tex);
    SDL_DestroyTexture(play_glow_button_tex);
	SDL_DestroyTexture(music_button_tex);
	SDL_DestroyTexture(music_glow_button_tex);
	SDL_DestroyTexture(about_us_button_tex);
	SDL_DestroyTexture(about_us_glow_button_tex);
    SDL_DestroyTexture(exit_button_tex);
    SDL_DestroyTexture(exit_glow_button_tex);
}

