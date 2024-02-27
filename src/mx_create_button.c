#include "../inc/header.h"

SDL_Texture *mx_create_button(const char *image_path, SDL_Renderer **renderer,
							  SDL_Rect *button, int down, int side, int cx, int cy) {
    SDL_Surface *button_surf = IMG_Load(image_path);
    if (button_surf == NULL) {
        mx_printerr("error creating button surface: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
        return NULL;
    }

    SDL_Texture* button_tex = SDL_CreateTextureFromSurface(*renderer, button_surf);
    SDL_FreeSurface(button_surf);
    if (button_tex == NULL) {
        mx_printerr("error creating button texture: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
        return NULL;
    }

    SDL_QueryTexture(button_tex, NULL, NULL, &button->w, &button->h);
    button->x = (WIN_WIDTH - button->w) / cx - side;
    button->y = (WIN_HEIGHT - button->h) / cy - down;

    return button_tex;
}

