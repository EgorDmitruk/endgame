#include "../inc/header.h"

void mx_game(SDL_Window **window, SDL_Renderer **renderer, int *start,
			 int *start_play, int *start_end, uint32_t *start_time, uint32_t *pause_time) {
	SDL_Texture *game_background_tex = mx_change_background("./resources/images/game_background.png",
															 renderer);
	if (game_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Texture *dark_background_tex = mx_change_background("./resources/images/dark_background.png",
															renderer);
	if (dark_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
	SDL_Texture *rules_background_tex = mx_change_background("./resources/images/Image2.png",
															 renderer);
	if (rules_background_tex == NULL) {
		mx_destroy_window(window, renderer);
		exit(1);
	}
    Mix_Chunk *FootStepSound = Mix_LoadWAV("./resources/music/FootStepSound.wav");
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
												   renderer, &pause_text, 400, 475, 1, 1);
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
    cell map[10][10];
    mx_map(map);
    int x, y;
    int check_up = -1;
    int check_down = -1;
    int check_left = -1;
    int check_right = -1;
    int treasure = -1;
    SDL_Surface *tempsurf = IMG_Load("./resources/images/locations/fog.png");
    if (tempsurf == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
        mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    SDL_Texture *fog = SDL_CreateTextureFromSurface(*renderer, tempsurf);
    SDL_FreeSurface(tempsurf);
    SDL_Rect fogrect;
    fogrect.x = 265;
    fogrect.y = 180;
    fogrect.w = 670;
    fogrect.h = 670;
    SDL_Surface *elements[11]; // массив с картинками пустой клетки, стен, рек, порталов
    elements[0] = IMG_Load("./resources/images/locations/0.png");// загрузить в каждый элемент картинку с помощью IMG_Load(определённая картинка);
    if (elements[0] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[1] = IMG_Load("./resources/images/locations/1.png");
    if (elements[1] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[2] = IMG_Load("./resources/images/locations/2.png");
    if (elements[2] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[3] = IMG_Load("./resources/images/locations/3.png");
    if (elements[3] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[4] = IMG_Load("./resources/images/locations/4.png");
    if (elements[4] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[5] = IMG_Load("./resources/images/locations/5.png");
    if (elements[5] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[6] = IMG_Load("./resources/images/locations/6.png");
    if (elements[6] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[7] = IMG_Load("./resources/images/locations/7.png");
    if (elements[7] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[8] = IMG_Load("./resources/images/locations/8.png");
    if (elements[8] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[9] = IMG_Load("./resources/images/locations/9.png");
    if (elements[9] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    elements[10] = IMG_Load("./resources/images/locations/10.png");
    if (elements[10] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    SDL_Texture *element[11];
    for (int i = 0; i < 11; ++i) {
        element[i] = SDL_CreateTextureFromSurface(*renderer, elements[i]);
	SDL_FreeSurface(elements[i]);
        if (element[i] == NULL) {
            mx_printerr("error creating field surface: ");
	    mx_printerr(SDL_GetError());
	    mx_printerr("\n");
	    mx_destroy_window(window, renderer);
	    exit(1);
        }
    }
    SDL_Rect rectangles[5][5];
    for (int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
	    rectangles[i][j].x = 265 + 134 * j;
            rectangles[i][j].y = 180 + 134 * i;
            rectangles[i][j].w = 134;
            rectangles[i][j].h = 134;
	}
    }
    tempsurf = IMG_Load("./resources/images/locations/character.png");
    if (tempsurf == NULL) {
        mx_printerr("error creating character surface: ");
	mx_printerr(SDL_GetError());
        mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    SDL_Texture *character = SDL_CreateTextureFromSurface(*renderer, tempsurf);
    SDL_FreeSurface(tempsurf);
    SDL_Rect charrect;
    charrect.x = 533;
    charrect.y = 448;
    charrect.w = 134;
    charrect.h = 134;
    x = 6;
    y = 3;
    map[y][x].cell_shown = true;

	SDL_RenderClear(*renderer);
	SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

	SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
	int stopi = y + 3 < 10 ? y + 3 : 10;
	int stopj = x + 3 < 10 ? x + 3 : 10;
	int iteri = y - 2 > 0 ? 0 : 2 - y;
	int iterj = x - 2 > 0 ? 0 : 2 - x;
	for (int i = y - 2 > -1 ? y - 2 : 0; i < stopi; ++i) {
	    iterj = x - 2 > 0 ? 0 : 2 - x;
	    for (int j = x - 2 > -1 ? x - 2 : 0; j < stopj; ++j) {
		if (map[i][j].cell_shown)
	            SDL_RenderCopy(*renderer, element[0], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].wall_up_shown)
                    SDL_RenderCopy(*renderer, element[1], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].wall_down_shown)
                    SDL_RenderCopy(*renderer, element[2], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].wall_left_shown)
                    SDL_RenderCopy(*renderer, element[3], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].wall_right_shown)
                    SDL_RenderCopy(*renderer, element[4], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].river_shown)
                    SDL_RenderCopy(*renderer, element[5 + map[i][j].river_num], NULL, &(rectangles[iteri][iterj]));
		if (map[i][j].portal_shown)
                    SDL_RenderCopy(*renderer, element[8 + map[i][j].portal_num], NULL, &(rectangles[iteri][iterj]));
		++iterj;
	    }
	    ++iteri;
	}
	SDL_RenderCopy(*renderer, character, NULL, &charrect);

	SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
	SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
	SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
	SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
	SDL_RenderPresent(*renderer);

	int changes = false;

	// game loop
	uint32_t pause_start;
	uint32_t pause_finish;
	*start_time = SDL_GetTicks();
	while (*start && *start_play) {
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
					else if (event.key.keysym.sym == SDLK_UP && !rules && !pause) {
                        Mix_PlayChannel(-1, FootStepSound, 0);
                        check_up = mx_check_up(map, y, x, treasure);
                        changes = true;
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN && !rules && !pause) {
                        Mix_PlayChannel(-1, FootStepSound, 0);
                        check_down = mx_check_down(map, y, x, treasure);
                        changes = true;
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT && !rules && !pause) {
                        Mix_PlayChannel(-1, FootStepSound, 0);
                        check_left = mx_check_left(map, y, x, treasure);
                        changes = true;
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT && !rules && !pause) {
                        Mix_PlayChannel(-1, FootStepSound, 0);
                        check_right = mx_check_right(map, y, x, treasure);
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
									if (pause == false) {
										pause = true; // open pause text
										pause_start = SDL_GetTicks();
									}
									else {
										pause = false;
										pause_finish = SDL_GetTicks();
										*pause_time = *pause_time + pause_finish - pause_start;
									}
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

	    if (check_up != -1) {
            switch(check_up) {
                case 0: {
                    map[y - 1][x].cell_shown = true;
		    y -= 1;
		    break;
                }
                case 1: {
                    map[y][x].wall_up_shown = true;
		    break;
                }
                case 2: {
                    if (treasure == 1) {
                        *start_play = false;
                        *start_end = true;
                    }
                    else if (treasure == 0)
                        treasure = -1;// ложный клад
                    //else
                        // без клада
		    break;
                }
                case 3: {
                    map[y - 1][x].river_shown = true;
		    y -= 1;
		    int prevy = y;
		    int prevx = x;
		    y = map[prevy][prevx].river->y;
		    x = map[prevy][prevx].river->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].river_shown = true;
		    break;
                }
                case 4: {
                    map[y - 1][x].portal_shown = true;
                    y -= 1;
                    int prevy = y;
		    int prevx = x;
                    y = map[prevy][prevx].portal->y;
                    x = map[prevy][prevx].portal->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].portal_shown = true;
                    break;
                }
                case 5: {
		    y -= 1;
                    treasure = map[y][x].treasure;
		    map[y][x].cell_shown = true;
                    map[y][x].treasure = -1;
                }
            }
        }
        if (check_down != -1) { // со следующими свичами наподобие как с предыдущим
            switch(check_down) {
                case 0: {
                    map[y + 1][x].cell_shown = true;
                    y += 1;
                    break;
                }
                case 1: {
                    map[y][x].wall_down_shown = true;
                    break;
                }
                case 2: {
                    if (treasure == 1) {
                        *start_play = false;
                        *start_end = true;
                    }
                    else if (treasure == 0)
                        treasure = -1;// ложный клад
                    //else
                        // без клада
                    break;
                }
                case 3: {
                    map[y + 1][x].river_shown = true;
                    y += 1;
                    int prevy = y;
		    int prevx = x;
                    y = map[prevy][prevx].river->y;
                    x = map[prevy][prevx].river->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].river_shown = true;
                    break;
                }
                case 4: {
                    map[y + 1][x].portal_shown = true;
                    y += 1;
                    int prevy = y;
		    int prevx = x;
                    y = map[prevy][prevx].portal->y;
                    x = map[prevy][prevx].portal->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].portal_shown = true;
                    break;
                }
                case 5: {
		    y += 1;
                    treasure = map[y][x].treasure;
		    map[y][x].cell_shown = true;
                    map[y][x].treasure = -1;
                }
            }
        }
        if (check_left != -1) {
            switch(check_left) {
                case 0: {
                    map[y][x - 1].cell_shown = true;
                    x -= 1;
                    break;
                }
                case 1: {
                    map[y][x].wall_left_shown = true;
                    break;
                }
                case 2: {
                    if (treasure == 1) {
                        *start_play = false;
                        *start_end = true;
                    }
                    else if (treasure == 0)
                        treasure = -1;// ложный клад
                    //else
                        // без клада
                    break;
                }
                case 3: {
                    map[y][x - 1].river_shown = true;
                    x -= 1;
                    int prevy = y;
                    int prevx = x;
                    y = map[prevy][prevx].river->y;
                    x = map[prevy][prevx].river->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].river_shown = true;
                    break;
                }
                case 4: {
                    map[y][x - 1].portal_shown = true;
                    x -= 1;
                    int prevy = y;
                    int prevx = x;
                    y = map[prevy][prevx].portal->y;
                    x = map[prevy][prevx].portal->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].portal_shown = true;
                    break;
                }
                case 5: {
                    x -= 1;
                    treasure = map[y][x].treasure;
                    map[y][x].cell_shown = true;
                    map[y][x].treasure = -1;
                }
            }
        }
        if (check_right != -1) {
            switch(check_right) {
                case 0: {
                    map[y][x + 1].cell_shown = true;
                    x += 1;
                    break;
                }
                case 1: {
                    map[y][x].wall_right_shown = true;
                    break;
                }
                case 2: {
                    if (treasure == 1) {
                        *start_play = false;
                        *start_end = true;
                    }
                    else if (treasure == 0)
                        treasure = -1;// ложный клад
                    //else
                        // без клада
                    break;
                }
                case 3: {
                    map[y][x + 1].river_shown = true;
                    x += 1;
                    int prevy = y;
                    int prevx = x;
                    y = map[prevy][prevx].river->y;
                    x = map[prevy][prevx].river->x;
		    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            map[i][j].cell_shown = false;
                            map[i][j].wall_up_shown = false;
                            map[i][j].wall_down_shown = false;
                            map[i][j].wall_left_shown = false;
                            map[i][j].wall_right_shown = false;
                            map[i][j].river_shown = false;
                            map[i][j].portal_shown = false;
                        }
                    }
		    map[y][x].river_shown = true;
                    break;
                }
                case 4: {
                    map[y][x + 1].portal_shown = true;
                    x += 1;
                    int prevy = y;
                    int prevx = x;
                    y = map[prevy][prevx].portal->y;
                    x = map[prevy][prevx].portal->x;
		    for (int i = 0; i < 10; ++i) {
		        for (int j = 0; j < 10; ++j) {
			    map[i][j].cell_shown = false;
			    map[i][j].wall_up_shown = false;
			    map[i][j].wall_down_shown = false;
			    map[i][j].wall_left_shown = false;
			    map[i][j].wall_right_shown = false;
			    map[i][j].river_shown = false;
			    map[i][j].portal_shown = false;
			}
		    }
		    map[y][x].portal_shown = true;
                    break;
                }
                case 5: {
                    x += 1;
                    treasure = map[y][x].treasure;
                    map[y][x].cell_shown = true;
                    map[y][x].treasure = -1;
                }
            }
        }
        check_up = -1;
        check_down = -1;
        check_left = -1;
        check_right = -1;

		if (changes == true) {
			SDL_RenderClear(*renderer);
			if (rules)
				SDL_RenderCopy(*renderer, rules_background_tex, NULL, NULL);
			else {
				SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

				SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
				stopi = y + 3 < 10 ? y + 3 : 10;
				stopj = x + 3 < 10 ? x + 3 : 10;
	                        iteri = y - 2 > 0 ? 0 : 2 - y;
	                        iterj = x - 2 > 0 ? 0 : 2 - x;
                        	for (int i = y - 2 > -1 ? y - 2 : 0; i < stopi; ++i) {
	                           iterj = x - 2 > 0 ? 0 : 2 - x;
	                           for (int j = x - 2 > -1 ? x - 2 : 0; j < stopj; ++j) {
		                       if (map[i][j].cell_shown)
	                                   SDL_RenderCopy(*renderer, element[0], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].wall_up_shown)
                                           SDL_RenderCopy(*renderer, element[1], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].wall_down_shown)
                                           SDL_RenderCopy(*renderer, element[2], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].wall_left_shown)
                                           SDL_RenderCopy(*renderer, element[3], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].wall_right_shown)
                                           SDL_RenderCopy(*renderer, element[4], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].river_shown)
                                           SDL_RenderCopy(*renderer, element[5 + map[i][j].river_num], NULL, &(rectangles[iteri][iterj]));
		                       if (map[i][j].portal_shown)
                                           SDL_RenderCopy(*renderer, element[8 + map[i][j].portal_num], NULL, &(rectangles[iteri][iterj]));
		                       ++iterj;
	                           }
	                           ++iteri;
	                       }
	                       SDL_RenderCopy(*renderer, character, NULL, &charrect);

				if (pause) {
					SDL_RenderCopy(*renderer, dark_background_tex, NULL, NULL);
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
	for (int i = 0; i < 11; ++i)
	    SDL_DestroyTexture(element[i]);
	SDL_DestroyTexture(fog);
	SDL_DestroyTexture(character);
	SDL_DestroyTexture(game_background_tex);
	SDL_DestroyTexture(dark_background_tex);
	SDL_DestroyTexture(rules_background_tex);
	SDL_DestroyTexture(pause_text_tex);
    SDL_DestroyTexture(music_on_button_tex);
    SDL_DestroyTexture(music_off_button_tex);
	SDL_DestroyTexture(rules_button_tex);
	SDL_DestroyTexture(pause_button_tex);
	SDL_DestroyTexture(start_button_tex);
    SDL_DestroyTexture(exit_button_tex);
}
