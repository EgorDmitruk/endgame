#include "../inc/header.h"

void mx_render_field(int y, int x, cell map[10][10], SDL_Renderer **renderer, SDL_Texture *element[16], SDL_Rect rectangles[5][5]) {
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
	    if (map[i][j].treasure_shown)
                SDL_RenderCopy(*renderer, element[11], NULL, &(rectangles[iteri][iterj]));
	    ++iterj;
	}
        ++iteri;
    }
}

