#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define FPS 60
#define FRAME_TIME (1000 / FPS)

        //~~~//

typedef struct cell {
    int x;
    int y;
    bool cell_shown;
    bool wall_up;
    bool wall_up_shown;
    bool wall_up_unlocked;
    bool wall_down;
    bool wall_down_shown;
    bool wall_down_unlocked;
    bool wall_right;
    bool wall_right_shown;
    bool wall_right_unlocked;
    bool wall_left;
    bool wall_left_shown;
    bool wall_left_unlocked;
    struct cell *river;
    int river_num;
    bool river_shown;
    struct cell *portal;
    int portal_num;
    bool portal_shown;
    int treasure; // -1 - нет клада, 0 - ложный, 1 - истинный
    bool treasure_shown;
}              cell;

void mx_map(cell karta[10][10]);
void mx_gen(cell map[10][10]);
void mx_randyx(int *y, int *x);
int mx_check_up(cell map[10][10], int y, int x);
int mx_check_down(cell map[10][10], int y, int x);
int mx_check_left(cell map[10][10], int y, int x);
int mx_check_right(cell map[10][10], int y, int x);
void mx_render_field(int y, int x, cell map[10][10], SDL_Renderer **renderer, SDL_Texture *element[16], SDL_Rect rectangles[5][5]);

void mx_drawmap(SDL_Surface **image, SDL_Surface **tempsurf, int x, int y);
void mx_upload_map(SDL_Surface **tempsurf, SDL_Renderer **renderer, SDL_Texture **prew);
void mx_draw_unlocked(cell map[10][10], int x, int y, SDL_Surface **tempsurf, SDL_Surface *miniel[16]);

        //~~~//

void mx_create_window(SDL_Window **window, SDL_Renderer **renderer);
void mx_destroy_window(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture *mx_change_background(const char* imagePath, SDL_Renderer **renderer);
SDL_Texture *mx_create_button(const char *image_path, SDL_Renderer **renderer,
							  SDL_Rect *button, int down, int side, int cx, int cy);
SDL_Texture *mx_create_text(const char *text, SDL_Renderer **renderer, SDL_Rect *font_rect,
							SDL_Color color, int down, int side, int cx, int cy, int size);
void mx_menu(SDL_Window **window, SDL_Renderer **renderer, int *start,
			 int *start_play, int *start_menu);
void mx_game(SDL_Window **window, SDL_Renderer **renderer, int *start,
			 int *start_play, int *start_end, uint32_t *start_time, uint32_t *pause_time);
void mx_end_menu(SDL_Window **window, SDL_Renderer **renderer, int *start, int *start_play,
				 int *start_menu, int *start_end, uint32_t *start_time, uint32_t *pause_time);
void mx_play_menu_music(const char *musicPath, int MusicFlag);

void mx_printerr(const char *s);
int mx_strlen(const char *s);

#endif
