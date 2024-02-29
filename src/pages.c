#include "../inc/header.h"

void mx_drawmap(SDL_Surface **image, SDL_Surface **tempsurf, int x, int y) {
    SDL_Rect copyrect;
    copyrect.x = x * 67;
    copyrect.y = y * 67;
    copyrect.w = 67;
    copyrect.h = 67;
    SDL_BlitSurface(*image, NULL, *tempsurf, &copyrect);
}

void mx_upload_map(SDL_Surface **tempsurf, SDL_Renderer **renderer, SDL_Texture **prew) {
    SDL_DestroyTexture(*prew);
    *prew = SDL_CreateTextureFromSurface(*renderer, *tempsurf);
    if (prew == NULL) {
        mx_printerr("error creating map texture: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	return;
    }
}

void mx_draw_unlocked(cell map[10][10], int x, int y, SDL_Surface **tempsurf, SDL_Surface *miniel[16]) {
    if (map[y][x].wall_up_unlocked) {
        mx_drawmap(&miniel[1], tempsurf, x, y);
    }
    if (map[y][x].wall_down_unlocked) {
        mx_drawmap(&miniel[2], tempsurf, x, y);
    }
    if (map[y][x].wall_left_unlocked) {
        mx_drawmap(&miniel[3], tempsurf, x, y);
    }
    if (map[y][x].wall_right_unlocked) {
        mx_drawmap(&miniel[4], tempsurf, x, y);
    }
}

