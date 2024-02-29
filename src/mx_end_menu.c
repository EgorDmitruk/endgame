#include "../inc/header.h"

void mx_end_menu(SDL_Window **window, SDL_Renderer **renderer, int *start, int *start_play,
				 int *start_menu, int *start_end, uint32_t *start_time, uint32_t *pause_time) {
	SDL_Texture *end_background_tex = mx_change_background("./resources/images/Image2.png",
														   renderer);
	if (end_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	int MusicFlag = 1;
	mx_play_menu_music("./resources/music/StartMenuMusic.mp3", MusicFlag);
	Mix_Chunk *ChoiceButtonSoundEffect = Mix_LoadWAV("./resources/music/ChoiceButtonSoundEffect.wav");

	// messages
	SDL_Color color = {128, 0, 0, 255};
	char *tr_treasure1 = "Arrr-guh!!!! You won!!!!";
	char *tr_treasure2 = "Yo-ho-ho!!!!";
	SDL_Rect win1_text;
    SDL_Texture *win1_text_tex = mx_create_text(tr_treasure1, renderer, &win1_text,
    											color, 450, 0, 2, 2, 150);
    if (win1_text_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect win2_text;
    SDL_Texture *win2_text_tex = mx_create_text(tr_treasure2, renderer, &win2_text,
    											color, 275, 0, 2, 2, 150);
    if (win2_text_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// count time
	uint32_t end_time = SDL_GetTicks();
	int game_time = (end_time - *start_time - *pause_time) / 1000; // time in seconds
	int hours = game_time / 3600;
	int minutes = game_time / 60;
	int seconds = game_time % 60;
	char buffer[44];
	sprintf(buffer, "Your time: %i hours, %i minutes, %i seconds", hours, minutes, seconds);
	SDL_Rect time_text;
    SDL_Texture *time_text_tex = mx_create_text(buffer, renderer, &time_text,
    											color, 150, 0, 2, 2, 100);
    if (time_text_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// create end menu buttons
	int rd = 470;
	int md = 330;
	int ed = 190;

	// restart buttons
	SDL_Rect restart_button;
	SDL_Texture *restart_button_tex = mx_create_button("./resources/images/buttons/restart.png",
													   renderer, &restart_button, rd, 0, 2, 1);
	if (restart_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect restart_glow_button;
	SDL_Texture *restart_glow_button_tex = mx_create_button("./resources/images/buttons/restart_glow.png",
															renderer, &restart_glow_button, rd, 0, 2, 1);
	if (restart_glow_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

	// start menu buttons
	SDL_Rect menu_button;
	SDL_Texture *menu_button_tex = mx_create_button("./resources/images/buttons/menu.png",
													 renderer, &menu_button, md, 0, 2, 1);
	if (menu_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Rect menu_glow_button;
	SDL_Texture *menu_glow_button_tex = mx_create_button("./resources/images/buttons/menu_glow.png",
													 	 renderer, &menu_glow_button, md, 0, 2, 1);
	if (menu_glow_button_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}

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
	SDL_RenderCopy(*renderer, end_background_tex, NULL, NULL);
	SDL_RenderCopy(*renderer, restart_button_tex, NULL, &restart_button);
	SDL_RenderCopy(*renderer, menu_button_tex, NULL, &menu_button);
	SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
	SDL_RenderCopy(*renderer, win1_text_tex, NULL, &win1_text);
	SDL_RenderCopy(*renderer, win2_text_tex, NULL, &win2_text);
	SDL_RenderCopy(*renderer, time_text_tex, NULL, &time_text);
	SDL_RenderPresent(*renderer);

	int changes = false;
	int mouse_on_button = false;

	// end menu loop
	while (*start && *start_end) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					*start = false; // quit
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (event.button.x > restart_button.x
							&& event.button.x < restart_button.x + restart_button.w
							&& event.button.y > restart_button.y
							&& event.button.y < restart_button.y + restart_button.h) {
								Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
								*start_end = false;
								*start_play = true; // restart game
								changes = true;
								MusicFlag = 2;
								mx_play_menu_music("./resources/music/gameplayMusic.mp3", MusicFlag);
						}
						else if (event.button.x > menu_button.x
							&& event.button.x < menu_button.x + menu_button.w
							&& event.button.y > menu_button.y
							&& event.button.y < menu_button.y + menu_button.h) {
							Mix_PlayChannel(-1, ChoiceButtonSoundEffect, 0);
								*start_end = false;
								*start_menu = true; // back to menu
								changes = true;
						}
						else if (event.button.x > exit_button.x
							&& event.button.x < exit_button.x + exit_button.w
							&& event.button.y > exit_button.y
							&& event.button.y < exit_button.y + exit_button.h) {
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
		if (x > restart_button.x && x < restart_button.x + restart_button.w
			&& y > restart_button.y && y < restart_button.y + restart_button.h) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, end_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, menu_button_tex, NULL, &menu_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
			SDL_RenderCopy(*renderer, win1_text_tex, NULL, &win1_text);
			SDL_RenderCopy(*renderer, win2_text_tex, NULL, &win2_text);
			SDL_RenderCopy(*renderer, time_text_tex, NULL, &time_text);

			SDL_RenderCopy(*renderer, restart_glow_button_tex, NULL, &restart_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else if (x > menu_button.x && x < menu_button.x + menu_button.w
			&& y > menu_button.y && y < menu_button.y + menu_button.h) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, end_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, restart_button_tex, NULL, &restart_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
			SDL_RenderCopy(*renderer, win1_text_tex, NULL, &win1_text);
			SDL_RenderCopy(*renderer, win2_text_tex, NULL, &win2_text);
			SDL_RenderCopy(*renderer, time_text_tex, NULL, &time_text);

			SDL_RenderCopy(*renderer, menu_glow_button_tex, NULL, &menu_glow_button);
			SDL_RenderPresent(*renderer);
			mouse_on_button = true;
		}
		else if (x > exit_button.x && x < exit_button.x + exit_button.w
			&& y > exit_button.y && y < exit_button.y + exit_button.h) {
			SDL_RenderClear(*renderer);
			SDL_RenderCopy(*renderer, end_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, restart_button_tex, NULL, &restart_button);
			SDL_RenderCopy(*renderer, menu_button_tex, NULL, &menu_button);
			SDL_RenderCopy(*renderer, win1_text_tex, NULL, &win1_text);
			SDL_RenderCopy(*renderer, win2_text_tex, NULL, &win2_text);
			SDL_RenderCopy(*renderer, time_text_tex, NULL, &time_text);

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
			SDL_RenderCopy(*renderer, end_background_tex, NULL, NULL);
			SDL_RenderCopy(*renderer, restart_button_tex, NULL, &restart_button);
			SDL_RenderCopy(*renderer, menu_button_tex, NULL, &menu_button);
			SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
			SDL_RenderCopy(*renderer, win1_text_tex, NULL, &win1_text);
			SDL_RenderCopy(*renderer, win2_text_tex, NULL, &win2_text);
			SDL_RenderCopy(*renderer, time_text_tex, NULL, &time_text);
    		changes = false;
    		SDL_RenderPresent(*renderer);
    	}
	}
	SDL_DestroyTexture(end_background_tex);
	SDL_DestroyTexture(win1_text_tex);
	SDL_DestroyTexture(win2_text_tex);
	SDL_DestroyTexture(time_text_tex);
    SDL_DestroyTexture(restart_button_tex);
    SDL_DestroyTexture(restart_glow_button_tex);
	SDL_DestroyTexture(menu_button_tex);
	SDL_DestroyTexture(menu_glow_button_tex);
    SDL_DestroyTexture(exit_button_tex);
    SDL_DestroyTexture(exit_glow_button_tex);
}

