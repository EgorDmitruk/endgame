#include "../inc/header.h"

void mx_game(SDL_Window **window, SDL_Renderer **renderer,
			 int *start, int *start_play) {
	SDL_Texture *game_background_tex = mx_change_background("./resources/images/game_background.png",
															 renderer);
	if (game_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Texture *rules_background_tex = mx_change_background("./resources/images/Image2.png",
															 renderer);
	if (rules_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	// mx_play_menu_music("./resources/music/StartMenuMusic.mp3");
	Mix_Chunk *ChoiceButtonSoundEffect = Mix_LoadWAV("./resources/music/ChoiceButtonSoundEffect.wav");

	// create side buttons
	int md = 750;
	int rd = 550;
	int pd = 350;
	int ed = 150;

	int side = 1760;

	// music buttons
	SDL_Rect music_on_button;
	SDL_Texture *music_on_button_tex = mx_create_button("./resources/images/buttons/music_on_game.png",
														renderer, &music_on_button, md, side, 1, 1);
	if (music_on_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect music_off_button;
	SDL_Texture *music_off_button_tex = mx_create_button("./resources/images/buttons/music_off_game.png",
														 renderer, &music_off_button, md, side, 1, 1);
	if (music_off_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// rules button
	SDL_Rect rules_button;
	SDL_Texture *rules_button_tex = mx_create_button("./resources/images/buttons/rules_game.png",
													 renderer, &rules_button, rd, side, 1, 1);
	if (rules_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	int rules = false;

	// pause and start buttons
	SDL_Rect pause_button;
	SDL_Texture *pause_button_tex = mx_create_button("./resources/images/buttons/pause_game.png",
													 renderer, &pause_button, pd, side, 1, 1);
	if (pause_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	int pause = false;
	SDL_Rect pause_text;
	SDL_Texture *pause_text_tex = mx_create_button("./resources/images/pause_text.png",
												   renderer, &pause_text, 350, 475, 1, 1);
	if (pause_text_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect start_button;
	SDL_Texture *start_button_tex = mx_create_button("./resources/images/buttons/start_game.png",
													 renderer, &start_button, pd, side, 1, 1);
	if (start_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// exit button
	SDL_Rect exit_button;
	SDL_Texture *exit_button_tex = mx_create_button("./resources/images/buttons/exit_game.png",
													renderer, &exit_button, ed, side, 1, 1);
	if (exit_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	SDL_RenderClear(*renderer);
	SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);
	SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
	SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
	SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
	SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
	SDL_RenderPresent(*renderer);

	int changes = false;

	// game loop
	while (*start && start_play) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					*start = false; // quit
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						rules = false; // close rules
						changes = true;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (event.button.x > music_on_button.x
							&& event.button.x < music_on_button.x + music_on_button.w
							&& event.button.y > music_on_button.y
							&& event.button.y < music_on_button.y + music_on_button.h) {
								if (!rules) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									if (Mix_VolumeMusic(-1) != 0)
										Mix_VolumeMusic(0); // no sound
									else
										Mix_VolumeMusic(MIX_MAX_VOLUME); // max sound
									changes = true;
								}
							}
						else if (event.button.x > rules_button.x
							&& event.button.x < rules_button.x + rules_button.w
							&& event.button.y > rules_button.y
							&& event.button.y < rules_button.y + rules_button.h) {
								if (!rules) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									rules = true; // open rules
									changes = true;
								}
						}
						else if (event.button.x > pause_button.x
							&& event.button.x < pause_button.x + pause_button.w
							&& event.button.y > pause_button.y
							&& event.button.y < pause_button.y + pause_button.h) {
								if (!rules) {
									Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
									if (pause == false)
										pause = true; // open pause text
									else
										pause = false;
									changes = true;
								}
						}
						else if (event.button.x > exit_button.x
							&& event.button.x < exit_button.x + exit_button.w
							&& event.button.y > exit_button.y
							&& event.button.y < exit_button.y + exit_button.h) {
								if (!rules)
									*start = false; // quit
							}
					}
					break;
			}
		}
		SDL_Delay(100);

		if (changes == true) {
			SDL_RenderClear(*renderer);
			if (rules)
				SDL_RenderCopy(*renderer, rules_background_tex, NULL, NULL);
			else {
				SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);
				if (pause) {
					SDL_RenderCopy(*renderer, start_button_tex, NULL, &start_button);
					SDL_RenderCopy(*renderer, pause_text_tex, NULL, &pause_text);
				}
				else
					SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
				if (Mix_VolumeMusic(-1) != 0)
					SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
				else
					SDL_RenderCopy(*renderer, music_off_button_tex, NULL, &music_off_button);
				SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
				SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
			}
    		changes = false;
    		SDL_RenderPresent(*renderer);
    	}
	}
	SDL_DestroyTexture(game_background_tex);
	SDL_DestroyTexture(rules_background_tex);
	SDL_DestroyTexture(pause_text_tex);
    SDL_DestroyTexture(music_on_button_tex);
    SDL_DestroyTexture(music_off_button_tex);
	SDL_DestroyTexture(rules_button_tex);
	SDL_DestroyTexture(pause_button_tex);
	SDL_DestroyTexture(start_button_tex);
    SDL_DestroyTexture(exit_button_tex);
}

