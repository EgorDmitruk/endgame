#include "../inc/header.h"

void mx_newpage(SDL_Surface **tempsurf, char *image, int *maxx, int *maxy, int *minx, int *miny, int x, int y) {
    *tempsurf = IMG_Load(image);
    if (*tempsurf == NULL) {
        mx_printerr("error creating new page (temp): ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	exit(1);
    }
    *maxx = x;
    *maxy = y;
    *minx = x;
    *miny = y;
}

void mx_drawpage(SDL_Surface **image, SDL_Surface **tempsurf, int x, int y) {
    SDL_Rect copyrect;
    copyrect.x = x * 67;
    copyrect.y = y * 67;
    copyrect.w = 67;
    copyrect.h = 67;
    SDL_BlitSurface(*image, NULL, *tempsurf, &copyrect);
}

SDL_Texture *mx_createpage(int minx, int miny, int maxx, int maxy, SDL_Surface **tempsurf, SDL_Renderer **renderer) {
    SDL_Rect pagerect;
    pagerect.x = minx * 67;
    pagerect.y = miny * 67;
    pagerect.w = (maxx - minx + 1) * 67;
    pagerect.h = (maxy - miny + 1) * 67;
    SDL_Surface *pagesurf = SDL_CreateRGBSurface(0, pagerect.w, pagerect.h, 24, 0xff, 0xff, 0xff, 0xff);
    if (pagesurf == NULL) {
        mx_printerr("error creating page surface: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	return NULL;
    }
    SDL_SetColorKey(pagesurf, SDL_TRUE, 0x000000);
    SDL_BlitSurface(*tempsurf, &pagerect, pagesurf, NULL);
    SDL_Texture *res = SDL_CreateTextureFromSurface(*renderer, pagesurf);
    SDL_FreeSurface(pagesurf);
    SDL_FreeSurface(*tempsurf);
    *tempsurf = NULL;
    if (res == NULL) {
        mx_printerr("error creating page texture: ");
	mx_printerr(SDL_GetError());
	mx_printerr("\n");
	return NULL;
    }
    return res;
}

void mx_draw_unlocked(cell map[10][10], int x, int y, SDL_Surface **tempsurf, SDL_Surface *miniel[16]) {
    if (map[y][x].wall_up_unlocked) {
        if (y == 0)
            mx_drawpage(&miniel[1], tempsurf, x, y);
        else
            mx_drawpage(&miniel[5], tempsurf, x, y);
    }
    if (map[y][x].wall_down_unlocked) {
        if (y == 9)
            mx_drawpage(&miniel[2], tempsurf, x, y);
        else
            mx_drawpage(&miniel[6], tempsurf, x, y);
    }
    if (map[y][x].wall_left_unlocked) {
        if (x == 0)
            mx_drawpage(&miniel[3], tempsurf, x, y);
        else
            mx_drawpage(&miniel[7], tempsurf, x, y);
    }
    if (map[y][x].wall_right_unlocked) {
        if (x == 9)
            mx_drawpage(&miniel[4], tempsurf, x, y);
        else
            mx_drawpage(&miniel[8], tempsurf, x, y);
    }
}


