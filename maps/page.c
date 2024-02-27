int mx_check_up(cell map[10][10], int y, int x) {
    if (map[y][x].wall_up == true)
        return 1;
    else if (map[y][x].wall_up == false && y == 0)
        return 2;
    else if (map[y - 1][x].river != NULL)
        return 3;
    else if (map[y - 1][x].portal != NULL)
        return 4;
    else if (map[y - 1][x].treasure != -1)
        return 5;
    return 0;
}

int mx_check_down(cell map[10][10], int y, int x) {
    if (map[y][x].wall_down == true)
        return 1;
    else if (map[y][x].wall_down == false && y == 9)
        return 2;
    else if (map[y + 1][x].river != NULL)
        return 3;
    else if (map[y + 1][x].portal != NULL)
        return 4;
    else if (map[y + 1][x].treasure != -1)
        return 5;
    return 0;
}

int mx_check_left(cell map[10][10], int y, int x) {
    if (map[y][x].wall_left == true)
        return 1;
    else if (map[y][x].wall_left == false && x == 0)
        return 2;
    else if (map[y][x - 1].river != NULL)
        return 3;
    else if (map[y][x - 1].portal != NULL)
        return 4;
    else if (map[y][x - 1].treasure != -1)
        return 5;
    return 0;
}

int mx_check_right(cell map[10][10], int y, int x) {
    if (map[y][x].wall_right == true)
        return 1;
    else if (map[y][x].wall_right == false && x == 9)
        return 2;
    else if (map[y][x + 1].river != NULL)
        return 3;
    else if (map[y][x + 1].portal != NULL)
        return 4;
    else if (map[y][x + 1].treasure != -1)
        return 5;
    return 0;
}

    cell map[10][10];
    mx_gen(map);
    int x, y; // для ориентации на сгенерированной карте
    int maxx = 0; // для создания квадрата, который будет использоваться для создания текстуры листика; возможно, надо будет домножать х и у на какой-то коэффициент (ориентируясь на размеры картинок пустой клетки, речки, портала и т.д.)
    int maxy = 0;
    int minx = 0;
    int miny = 0;
    int check_up = -1;
    int check_down = -1;
    int check_left = -1;
    int check_right = -1;
    int moved_page = -1;
    int max_page = 20;
    int page_num = 0;
    int treasure = -1;
    bool moving = false;
    SDL_Surfase *tempsurf_forpages = NULL; // структура, на которую будут копироваться картинки, пока ходим, а когда пора создавать новый листик, из определённой области (с макс и мин х и у) будут копироваться данные
    SDL_Surface *elements[11]; // массив с картинками пустой клетки, стен, рек, порталов
    // загрузить в каждый элемент картинку с помощью IMG_Load(определённая картинка);
    SDL_Texture *pages[20] = malloc(sizeof(SDL_Texture *) * 20);
    mx_randyx(&y, &x); //закидываем игрока в самом начале игры
    while (map[y][x].river != NULL || map[y][x].portal != NULL
           || map[y][x].treasure != -1)
        mx_randyx(&y, &x);
    while (start && start_play) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    start = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        start = false;
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_UP) {
                        check_up = mx_check_up(map, y, x);
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN) {
                        check_down = mx_check_down(map, y, x);
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT) {
                        check_left = mx_check_left(map, y, x);
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT) {
                        check_right = mx_check_right(map, y, x);
                    }
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (!moving) {
                            for (int i = page_num; i >= 0; --i) {
                                if (event.button.x > pages[i].x // возможно, х и у надо будет домножить на какой-то коэффициент
                                    && event.button.x < pages[i].x + pages[i].w
                                    && event.button.y > pages[i].y
                                    && event.button.y < pages[i].y + pages[i].h) {
                                    moved_page = i;
                                    moving = true;
                                    break;
                                }
                            }
                        }
                    }
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        moved_page = -1;
                        moving = false;
                    }
                break;
            }
        }
        SDL_Delay(100);
        if (check_up != -1) {
            switch(check_up) {
                case 0: {
                    // нарисовать пустую клеточку на карте и на листике
                    // рисуем на листике
                    if (tempsurf_forpages == NULL) {
                        tempsurf_forpages = прозрачная поверхность, на которую будут копироваться определённые объекты;
                    }
                    if (maxx == 0 & maxy = 0 && minx == 0 && miny == 0) {
                        maxx = x;
                        maxy = y - 1;
                        minx = x;
                        miny = y - 1;
                    }
                    if (x > maxx)
                        maxx = x
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    if (!(map[y - 1][x].cell_shown)) {
                        SDL_Rect *copyrect;
                        copyrect.x = x;
                        copyrect.y = y - 1;
                        // ширина и длина как у картинки, которую будем вставлять
                        SDL_BlitSurfase(elements[0], NULL, tempsurf_forpages, copyrect);
                        map[y - 1][x].cell_shown = true;
                    }
                    y -= 1;
                }
                case 1: {
                    // нарисовать верхнюю стену на карте и на листике
                    if (!(map[y][x].wall_up_shown)) {
                        SDL_Rect *copyrect;
                        copyrect.x = x;
                        copyrect.y = y;
                        // ширина и длина как у картинки, которую будем вставля>
                        SDL_BlitSurfase(elements[1], NULL, tempsurf_forpages, copyrect);
                        map[y - 1][x].wall_up_shown = true;
                    }
                }
                case 2: {
                    if (treasure == 1)
                        // победа
                    else if (treasure == 0)
                        // ложный клад
                    else
                        // без клада
                }
                case 3: {
                    // нарисовать речку определённого номера на карте и на листике
                    // сначала дорисовываем листик
                    if (x > maxx)
                        maxx = x
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    SDL_Rect *copyrect;
                    copyrect.x = x;
                    copyrect.y = y - 1;
                    // ширина и длина как у картинки, которую будем вставлять
                    SDL_BlitSurfase(elements[5 + map[y - 1][x].river_num], NULL, tempsurf_forpages, copyrect);
                    copyrect.x = minx;
                    copyrect.y = miny;
                    copyrect.w = maxx - minx;
                    copyrect.h = maxy - miny;
                    // cоздать тоже прозрачную поверхность размеров maxy - miny : maxx - minx, и потом SDL_BlitSurfase(tempsurf_forpages, copyrect, новая поверхность, NULL);
                    pages[page_num] = SDL_CreateTextureFromSurface(рендерер, новая поверхность);
                    SDL_FreeSurface(новая поверхность);
                    SDL_FreeSurfase(tempsurf_forpages);
                    tempsurf_forpages = NULL;
                    // выводим листок
                    // сделать все видимые клетки невидимыми (..._shown = false)
                    y -= 1; // перемещаемся
                    y = map[y][x].river.y;
                    x = map[y][x].river.x;
                    page_num += 1;
                    maxy = 0, miny = 0; maxx = 0; minx = 0; // начинаем создавать новый листок
                    if (tempsurf_forpages == NULL) {
                        tempsurf_forpages = прозрачная поверхность, на которую будут копироваться определённые объекты;
                    }
                    if (maxx == 0 & maxy = 0 && minx == 0 && miny == 0) {
                        maxx = x;
                        maxy = y;
                        minx = x;
                        miny = y;
                    }
                    SDL_Rect *copyrect;
                    copyrect.x = x;
                    copyrect.y = y;
                    // ширина и длина как у картинки, которую будем вставлять
                    SDL_BlitSurfase(elements[5 + map[y][x].river_num], NULL, tempsurf_forpages, copyrect);
                    map[y][x].river_shown = true;
                }
                case 4: {
                    // нарисовать портал определённого номера на карте и на листике
                    // наподобие как с рекой
                    y -= 1;
                    y = map[y][x].portal.y;
                    x = map[y][x].portal.x;
                    page_num += 1;

                }
                case 5: {
                    // персонаж с кладом, на карте и на листике пустая клетка
                    if (x > maxx)
                        maxx = x
                    if (x < minx)
                        minx = x;
                    if (y - 1 > maxy)
                        maxy = y - 1;
                    if (y - 1 < miny)
                        miny = y - 1;
                    if (!(map[y - 1][x].cell_shown)) {
                        SDL_Rect *copyrect;
                        copyrect.x = x;
                        copyrect.y = y - 1;
                        // ширина и длина как у картинки, которую будем вставлять
                        SDL_BlitSurfase(elements[0], NULL, tempsurf_forpages, copyrect);
                    }
                    y -= 1;
                    treasure = map[y][x].treasure;
                }
            }
        }
        if (check_down != -1) { // со следующими свичами наподобие как с предыдущим
            switch(check_down) {
                case 0: {
                    // нарисовать пустую клеточку на карте и на листике
                    y += 1;
                }
                case 1: {
                    // нарисовать нижнюю стену на карте и на листике
                }
                case 2: {
                    if (treasure == 1)
                        // победа
                    else if (treasure == 0)
                        // ложный клад
                    else
                        // без клада
                }
                case 3: {
                    // нарисовать речку определённого номера на карте и на листике
                    y += 1;
                    y = map[y][x].river.y;
                    x = map[y][x].river.x;
                    page_num += 1;
                }
                case 4: {
                    // нарисовать портал определённого номера на карте и на листике
                    y += 1;
                    y = map[y][x].portal.y;
                    x = map[y][x].portal.x;
                    page_num += 1;

                }
                case 5: {
                    // персонаж с кладом, на карте и на листике пустая клетка
                    y += 1;
                    treasure = map[y][x].treasure;
                }
            }
        }
        if (check_left != -1) {
            switch(check_left) {
                case 0: {
                    // нарисовать пустую клеточку на карте и на листике
                    x -= 1;
                }
                case 1: {
                    // нарисовать левую стену на карте и на листике
                }
                case 2: {
                    if (treasure == 1)
                        // победа
                    else if (treasure == 0)
                        // ложный клад
                    else
                        // без клада
                }
                case 3: {
                    // нарисовать речку определённого номера на карте и на листике
                    x -= 1;
                    y = map[y][x].river.y;
                    x = map[y][x].river.x;
                    page_num += 1;
                }
                case 4: {
                    // нарисовать портал определённого номера на карте и на листике
                    x -= 1;
                    y = map[y][x].portal.y;
                    x = map[y][x].portal.x;
                    page_num += 1;

                }
                case 5: {
                    // персонаж с кладом, на карте и на листике пустая клетка
                    x -= 1;
                    treasure = map[y][x].treasure;
                }
            }
        }
        if (check_right != -1) {
            switch(check_right) {
                case 0: {
                    // нарисовать пустую клеточку на карте и на листике
                    x += 1;
                }
                case 1: {
                    // нарисовать правую стену на карте и на листике
                }
                case 2: {
                    if (treasure == 1)
                        // победа
                    else if (treasure == 0)
                        // ложный клад
                    else
                        // без клада
                }
                case 3: {
                    // нарисовать речку определённого номера на карте и на листике
                    x += 1;
                    y = map[y][x].river.y;
                    x = map[y][x].river.x;
                    page_num += 1;
                }
                case 4: {
                    // нарисовать портал определённого номера на карте и на листике
                    x += 1;
                    y = map[y][x].portal.y;
                    x = map[y][x].portal.x;
                    page_num += 1;

                }
                case 5: {
                    // персонаж с кладом, на карте и на листике пустая клетка
                    x += 1;
                    treasure = map[y][x].treasure;
                }
            }
        }
        if (page_num == max_pages) {
            max_pages += 10;
            pages = realloc(pages, sizeof(SDL_Texture) * max_pages);
        }
        check_up = -1;
        check_down = -1;
        check_left = -1;
        check_right = -1;
        int mousex, mousey; // двигаем листочек
        SDL_GetMouseState(&x, &y);
        if (moving) {
            pages[moved_page].x = mousex;
            pages[moved_page].y = mousey;
        }
    }
    free(pages);
