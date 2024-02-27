#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cell {
    int x;
    int y;
    bool cell_shown;
    bool wall_up;
    bool wall_up_shown;
    bool wall_down;
    bool wall_down_shown;
    bool wall_right;
    bool wall_right_shown;
    bool wall_left;
    bool wall_left_shown;
    struct cell *river;
    int river_num;
    bool river_shown;
    struct cell *portal;
    int portal_num;
    bool portal_shown;
    int treasure; // -1 - нет клада, 0 - ложный, 1 - истинный
}              cell;

void mx_gen(cell map[10][10]);
void mx_randyx(int *y, int *x);

#endif

