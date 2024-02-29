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
    SDL_Surface *elements[12]; // массив с картинками пустой клетки, стен, рек, порталов
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
    elements[11] = IMG_Load("./resources/images/locations/treasure.png");
    if (elements[11] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    SDL_Texture *element[12];
    for (int i = 0; i < 12; ++i) {
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

    int maxx, maxy, minx, miny;
    int page_num = 0;
    bool moving = false;
    int moved_page = -1;
    SDL_Surface *miniel[12];
    miniel[0] = IMG_Load("./resources/images/locations/0small.png");
    if (miniel[0] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[1] = IMG_Load("./resources/images/locations/1small.png");
    if (miniel[1] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[2] = IMG_Load("./resources/images/locations/2small.png");
    if (miniel[2] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[3] = IMG_Load("./resources/images/locations/3small.png");
    if (miniel[3] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[4] = IMG_Load("./resources/images/locations/4small.png");
    if (miniel[4] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[5] = IMG_Load("./resources/images/locations/5small.png");
    if (miniel[5] == NULL) {
        mx_printerr("error creating field surface: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        mx_destroy_window(window, renderer);
        exit(1);
    }
    miniel[6] = IMG_Load("./resources/images/locations/6small.png");
    if (miniel[6] == NULL) {
        mx_printerr("error creating field surface: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        mx_destroy_window(window, renderer);
        exit(1);
    }
    miniel[7] = IMG_Load("./resources/images/locations/7small.png");
    if (miniel[7] == NULL) {
        mx_printerr("error creating field surface: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        mx_destroy_window(window, renderer);
        exit(1);
    }
    miniel[8] = IMG_Load("./resources/images/locations/8small.png");
    if (miniel[8] == NULL) {
        mx_printerr("error creating field surface: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        mx_destroy_window(window, renderer);
        exit(1);
    }
    miniel[9] = IMG_Load("./resources/images/locations/9small.png");
    if (miniel[9] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[10] = IMG_Load("./resources/images/locations/10small.png");
    if (miniel[10] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }
    miniel[11] = IMG_Load("./resources/images/locations/treasure_small.png");
    if (miniel[11] == NULL) {
        mx_printerr("error creating field surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	mx_destroy_window(window, renderer);
	exit(1);
    }

    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
    mx_drawpage(&miniel[0], &tempsurf, x, y);
    SDL_Texture *pages[500];
    SDL_Rect pagesrect[500];
    
    int xoffset = -1;
    int yoffset = -1;
    int mousex, mousey;

	SDL_RenderClear(*renderer);
	SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

	SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
	mx_render_field(y, x, map, renderer, element, rectangles);
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
						else if (!moving) {
                                                  for (int i = page_num; i >= 0; --i) {
                                                      if (event.button.x > pagesrect[i].x
                                                          && event.button.x < pagesrect[i].x + pagesrect[i].w
                                                          && event.button.y > pagesrect[i].y
                                                          && event.button.y < pagesrect[i].y + pagesrect[i].h) {
                                                          moved_page = i;
                                                          moving = true;
                                                          changes = true;
                                                          break;
                                                      }
                                                  }
                                              }
					}
					break;
				case SDL_MOUSEBUTTONUP:
                                          if (event.button.button == SDL_BUTTON_LEFT) {
                                              if (moving) {
                                                  if (event.button.x > pagesrect[moved_page].x
                                                          && event.button.x < pagesrect[moved_page].x + pagesrect[moved_page].w
                                                          && event.button.y > pagesrect[moved_page].y
                                                          && event.button.y < pagesrect[moved_page].y + pagesrect[moved_page].h) {
                                                          moved_page = -1;
                                                          xoffset = -1;
                                                          yoffset = -1;
                                                          moving = false;
                                                  }
                                              }
                                       }
				break;
			}
		}
		SDL_Delay(100);

	    if (check_up != -1) {
            switch(check_up) {
                case 0: {
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    if (!(map[y - 1][x].cell_shown)) {
                        mx_drawpage(&miniel[0], &tempsurf, x, y - 1);
                        mx_draw_unlocked(map, x, y - 1, &tempsurf, miniel);
                        map[y - 1][x].cell_shown = true;
                    }
		    y -= 1;
		    break;
                }
                case 1: {
                    if (!(map[y][x].wall_up_shown)) {
                        map[y][x].wall_up_shown = true;
                        map[y][x].wall_up_unlocked = true;
			mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    }
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
		    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    map[y - 1][x].river_shown = true;
		    y -= 1;

		    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
		    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

		    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
		    break;
                }
                case 4: {
		    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    map[y - 1][x].portal_shown = true;
                    y -= 1;

		    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
		    
		    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 5: {
		    y -= 1;
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
		    if (treasure != -1) {
		        if (!(map[y][x].treasure_shown)) {
		            map[y][x].treasure_shown = true;
		            mx_drawpage(&miniel[0], &tempsurf, x, y);
		            mx_drawpage(&miniel[11], &tempsurf, x, y);
		        }
		    }
		    else {
                        treasure = map[y][x].treasure;
                        map[y][x].treasure = -1;
                        map[y][x].treasure_shown = false;
                        mx_drawpage(&miniel[0], &tempsurf, x, y);
		    }
		    map[y][x].cell_shown = true;
		    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                }
            }
        }
        if (check_down != -1) { // со следующими свичами наподобие как с предыдущим
            switch(check_down) {
                case 0: {
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y + 1 > maxy)
                        maxy = y + 1;
                    if (y + 1 < miny)
                        miny = y + 1;
                    if (!(map[y + 1][x].cell_shown)) {
                        mx_drawpage(&miniel[0], &tempsurf, x, y + 1);
                        mx_draw_unlocked(map, x, y + 1, &tempsurf, miniel);
                        map[y + 1][x].cell_shown = true;
                    }
                    y += 1;
                    break;
                }
                case 1: {
                    if (!(map[y][x].wall_down_shown)) {
                        map[y][x].wall_down_shown = true;
                        map[y][x].wall_down_unlocked = true;
			mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    }
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
		    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y + 1 > maxy)
                        maxy = y + 1;
                    if (y + 1 < miny)
                        miny = y + 1;
                    map[y + 1][x].river_shown = true;
                    y += 1;

		    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 4: {
		    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y + 1 > maxy)
                        maxy = y + 1;
                    if (y + 1 < miny)
                        miny = y + 1;
                    map[y + 1][x].portal_shown = true;
                    y += 1;

		    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 5: {
		    y += 1;
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
		    if (treasure != -1) {
		        if (!(map[y][x].treasure_shown)) {
                            map[y][x].treasure_shown = true;
                            mx_drawpage(&miniel[0], &tempsurf, x, y);
		            mx_drawpage(&miniel[11], &tempsurf, x, y);
                        }
                    }
                    else {
                        treasure = map[y][x].treasure;
                        map[y][x].treasure = -1;
                        map[y][x].treasure_shown = false;
                        mx_drawpage(&miniel[0], &tempsurf, x, y);
                    }
                    map[y][x].cell_shown = true;
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                }
            }
        }
        if (check_left != -1) {
            switch(check_left) {
                case 0: {
                    if (x - 1 > maxx)
                        maxx = x - 1;
                    if (x - 1 < minx)
                        minx = x - 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    if (!(map[y][x - 1].cell_shown)) {
                        mx_drawpage(&miniel[0], &tempsurf, x - 1, y);
                        mx_draw_unlocked(map, x - 1, y, &tempsurf, miniel);
                        map[y][x - 1].cell_shown = true;
                    }
                    x -= 1;
                    break;
                }
                case 1: {
                    if (!(map[y][x].wall_left_shown)) {
                        map[y][x].wall_left_shown = true;
                        map[y][x].wall_left_unlocked = true;
			mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    }
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
		    if (x - 1 > maxx)
                        maxx = x - 1;
                    if (x - 1 < minx)
                        minx = x - 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    map[y][x - 1].river_shown = true;
                    x -= 1;

		    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 4: {
		    if (x - 1 > maxx)
                        maxx = x - 1;
                    if (x - 1 < minx)
                        minx = x - 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    map[y][x - 1].portal_shown = true;
                    x -= 1;

		    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 5: {
                    x -= 1;
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
		    if (treasure != -1) {
		        if (!(map[y][x].treasure_shown)) {
                            map[y][x].treasure_shown = true;
                            mx_drawpage(&miniel[0], &tempsurf, x, y);
		            mx_drawpage(&miniel[11], &tempsurf, x, y);
                        }
                    }
                    else {
                        treasure = map[y][x].treasure;
                        map[y][x].treasure = -1;
                        map[y][x].treasure_shown = false;
                        mx_drawpage(&miniel[0], &tempsurf, x, y);
                    }
                    map[y][x].cell_shown = true;
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                }
            }
        }
        if (check_right != -1) {
            switch(check_right) {
                case 0: {
                    if (x + 1 > maxx)
                        maxx = x + 1;
                    if (x + 1 < minx)
                        minx = x + 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    if (!(map[y][x + 1].cell_shown)) {
                        mx_drawpage(&miniel[0], &tempsurf, x + 1, y);
                        mx_draw_unlocked(map, x + 1, y, &tempsurf, miniel);
                        map[y][x + 1].cell_shown = true;
                    }
                    x += 1;
                    break;
                }
                case 1: {
                    if (!(map[y][x].wall_right_shown)) {
                        map[y][x].wall_right_shown = true;
                        map[y][x].wall_right_unlocked = true;
			mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    }
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
		    if (x + 1 > maxx)
                        maxx = x + 1;
                    if (x + 1 < minx)
                        minx = x + 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    map[y][x + 1].river_shown = true;
                    x += 1;

		    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[5 + map[y][x].river_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 4: {
		    if (x + 1 > maxx)
                        maxx = x + 1;
                    if (x + 1 < minx)
                        minx = x + 1;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    map[y][x + 1].portal_shown = true;
                    x += 1;

		    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);

                    SDL_RenderClear(*renderer);
                    SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

                    SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
                    mx_render_field(y, x, map, renderer, element, rectangles);
                    SDL_RenderCopy(*renderer, character, NULL, &charrect);

                    SDL_RenderCopy(*renderer, music_on_button_tex, NULL, &music_on_button);
                    SDL_RenderCopy(*renderer, rules_button_tex, NULL, &rules_button);
                    SDL_RenderCopy(*renderer, pause_button_tex, NULL, &pause_button);
                    SDL_RenderCopy(*renderer, exit_button_tex, NULL, &exit_button);
                    
                    for (int i = 0; i < page_num; ++i)
                        SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
                    
                    SDL_RenderPresent(*renderer);

                    SDL_Delay(1000);
                    
                    pages[page_num] = mx_createpage(minx, miny, maxx, maxy, &tempsurf, renderer);
		    pagesrect[page_num].x = 1000;
		    pagesrect[page_num].y = 225;
		    SDL_QueryTexture(pages[page_num], NULL, NULL, &pagesrect[page_num].w, &pagesrect[page_num].h);
		    page_num += 1;
			
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
		    mx_newpage(&tempsurf, "./resources/images/locations/prozrachnyy.png", &maxx, &maxy, &minx, &miny, x, y);
                    mx_drawpage(&miniel[8 + map[y][x].portal_num], &tempsurf, x, y);
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                    break;
                }
                case 5: {
                    x += 1;
                    if (x > maxx)
                        maxx = x;
                    if (x < minx)
                        minx = x;
                    if (y > maxy)
                        maxy = y;
                    if (y < miny)
                        miny = y;
                    if (treasure != -1) {
                        if (!(map[y][x].treasure_shown)) {
                            map[y][x].treasure_shown = true;
                            mx_drawpage(&miniel[0], &tempsurf, x, y);
		            mx_drawpage(&miniel[11], &tempsurf, x, y);
                        }
                    }
                    else {
                        treasure = map[y][x].treasure;
                        map[y][x].treasure = -1;
                        map[y][x].treasure_shown = false;
                        mx_drawpage(&miniel[0], &tempsurf, x, y);
                    }
                    map[y][x].cell_shown = true;
                    mx_draw_unlocked(map, x, y, &tempsurf, miniel);
                }
            }
        }
        check_up = -1;
        check_down = -1;
        check_left = -1;
        check_right = -1;

	// двигаем листочек
        SDL_GetMouseState(&mousex, &mousey);
        if (moving) {
            if (xoffset == -1 && yoffset == -1) {
                xoffset = mousex - pagesrect[moved_page].x;
                yoffset = mousey - pagesrect[moved_page].y;
            }
            pagesrect[moved_page].x = mousex - xoffset;
            pagesrect[moved_page].y = mousey - yoffset;
            changes = true;
        }

		if (changes == true) {
			SDL_RenderClear(*renderer);
			if (rules)
				SDL_RenderCopy(*renderer, rules_background_tex, NULL, NULL);
			else {
				SDL_RenderCopy(*renderer, game_background_tex, NULL, NULL);

				SDL_RenderCopy(*renderer, fog, NULL, &fogrect);
				mx_render_field(y, x, map, renderer, element, rectangles);
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

			for (int i = 0; i < page_num; ++i)
                        	SDL_RenderCopy(*renderer, pages[i], NULL, &(pagesrect[i]));
			
    		changes = false;
    		SDL_RenderPresent(*renderer);
    	}
	}
	for (int i = 0; i < page_num; ++i)
	    SDL_DestroyTexture(pages[i]);
	for (int i = 0; i < 12; ++i) {
	    SDL_DestroyTexture(element[i]);
	    SDL_FreeSurface(miniel[i]);
	}
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
