#include "../inc/header.h"

SDL_Texture *mx_create_text(const char *text, SDL_Renderer **renderer, SDL_Rect *font_rect,
							SDL_Color color, int down, int side, int cx, int cy, int size) {
	TTF_Font *font = TTF_OpenFont("./resources/type/pixeltype.ttf", size);
	if (font == NULL) {
		mx_printerr("error opening font: ");
		mx_printerr(TTF_GetError());
		mx_printerr("\n");
		return NULL;
	}

	SDL_Surface *font_surf = TTF_RenderText_Blended(font, text, color);
    if (font_surf == NULL) {
        mx_printerr("error creating font surface: ");
		mx_printerr(TTF_GetError());
		mx_printerr("\n");
        return NULL;
    }

    SDL_Texture* font_tex = SDL_CreateTextureFromSurface(*renderer, font_surf);
    SDL_FreeSurface(font_surf);
    if (font_tex == NULL) {
        mx_printerr("error creating font texture: ");
		mx_printerr(SDL_GetError());
		mx_printerr("\n");
        return NULL;
    }
    TTF_CloseFont(font);

    SDL_QueryTexture(font_tex, NULL, NULL, &font_rect->w, &font_rect->h);
    font_rect->x = (WIN_WIDTH - font_rect->w) / cx - side;
    font_rect->y = (WIN_HEIGHT - font_rect->h) / cy - down;

    return font_tex;
}

