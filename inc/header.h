#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define FPS 60
#define FRAME_TIME (1000 / FPS)

void mx_create_window(SDL_Window **window, SDL_Renderer **renderer);
void mx_destroy_window(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture *mx_change_background(const char* imagePath, SDL_Renderer **renderer);
SDL_Texture *mx_create_button(const char *image_path, SDL_Renderer **renderer, SDL_Rect *button, int down);
void mx_menu(SDL_Window **window, SDL_Renderer **renderer, int *start, int *start_play);
void mx_play_menu_music(const char *musicPath);

void mx_printerr(const char *s);
int mx_strlen(const char *s);

#endif

