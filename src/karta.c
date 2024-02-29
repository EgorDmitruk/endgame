#include "../inc/header.h"

void mx_map(cell karta[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            karta[j][i].x = i;
            karta[j][i].y = j;
            karta[j][i].wall_up = false;
            karta[j][i].wall_down = false;
            karta[j][i].wall_left = false;
            karta[j][i].wall_right = false;
            karta[j][i].river = NULL;
            karta[j][i].river_num = -1;
            karta[j][i].portal = NULL;
            karta[j][i].portal_num = -1;
            karta[j][i].treasure = -1;
            karta[j][i].cell_shown = false;
            karta[j][i].wall_up_shown = false;
            karta[j][i].wall_down_shown = false;
            karta[j][i].wall_left_shown = false;
            karta[j][i].wall_right_shown = false;
            karta[j][i].wall_up_unlocked = false;
            karta[j][i].wall_down_unlocked = false;
            karta[j][i].wall_left_unlocked = false;
            karta[j][i].wall_right_unlocked = false;
            karta[j][i].river_shown = false;
            karta[j][i].portal_shown = false;
            karta[j][i].treasure_shown = false;
        }
    }
    karta[1][2].river = &karta[3][2];
    karta[1][2].river_num = 0;
    karta[2][2].river = &karta[3][1];
    karta[2][2].river_num = 0;
    karta[3][2].river = &karta[3][1];
    karta[3][2].river_num = 0;
    karta[3][1].river = &karta[3][1];
    karta[3][1].river_num = 0;

    karta[8][5].river = &karta[7][6];
    karta[8][5].river_num = 1;
    karta[7][5].river = &karta[7][7];
    karta[7][5].river_num = 1;
    karta[7][6].river = &karta[6][7];
    karta[7][6].river_num = 1;
    karta[7][7].river = &karta[6][6];
    karta[7][7].river_num = 1;
    karta[6][7].river = &karta[5][6];
    karta[6][7].river_num = 1;
    karta[5][7].river = &karta[5][6];
    karta[5][7].river_num = 1;
    karta[5][6].river = &karta[5][6];
    karta[5][6].river_num = 1;

    karta[1][8].portal = &karta[8][7];
    karta[1][8].portal_num = 0;
    karta[8][7].portal = &karta[5][1];
    karta[8][7].portal_num = 0;
    karta[5][1].portal = &karta[1][8];
    karta[5][1].portal_num = 0;

    karta[1][5].portal = &karta[2][8];
    karta[1][5].portal_num = 1;
    karta[2][8].portal = &karta[4][8];
    karta[2][8].portal_num = 1;
    karta[4][8].portal = &karta[1][5];
    karta[4][8].portal_num = 1;

    karta[4][4].treasure = 1;
    karta[8][2].treasure = 0;

    for (int i = 0; i < 10; ++i) {
        karta[i][0].wall_left = true;
        karta[i][9].wall_right = true;
        karta[0][i].wall_up = true;
        karta[9][i].wall_down = true;
    }

    karta[0][3].wall_up = false;

    karta[2][3].wall_up = true;
    karta[2][4].wall_up = true;
    karta[2][5].wall_up = true;
    karta[2][7].wall_up = true;
    karta[2][8].wall_up = true;
    karta[4][3].wall_up = true;
    karta[5][7].wall_up = true;
    karta[5][8].wall_up = true;
    karta[6][2].wall_up = true;
    karta[6][5].wall_up = true;
    karta[7][1].wall_up = true;
    karta[7][2].wall_up = true;
    karta[7][3].wall_up = true;
    karta[7][4].wall_up = true;
    karta[8][8].wall_up = true;
    karta[8][8].wall_up = true;
    karta[9][1].wall_up = true;
    karta[9][2].wall_up = true;

    karta[1][3].wall_down = true;
    karta[1][4].wall_down = true;
    karta[1][5].wall_down = true;
    karta[1][7].wall_down = true;
    karta[1][8].wall_down = true;
    karta[3][3].wall_down = true;
    karta[4][7].wall_down = true;
    karta[4][8].wall_down = true;
    karta[5][2].wall_down = true;
    karta[5][5].wall_down = true;
    karta[6][1].wall_down = true;
    karta[6][2].wall_down = true;
    karta[6][3].wall_down = true;
    karta[6][4].wall_down = true;
    karta[7][8].wall_down = true;
    karta[7][8].wall_down = true;
    karta[8][1].wall_down = true;
    karta[8][2].wall_down = true;

    karta[6][1].wall_left = true;
    karta[8][3].wall_left = true;
    karta[5][3].wall_left = true;
    karta[4][4].wall_left = true;
    karta[5][4].wall_left = true;
    karta[3][5].wall_left = true;
    karta[4][5].wall_left = true;
    karta[5][5].wall_left = true;
    karta[2][6].wall_left = true;
    karta[3][6].wall_left = true;
    karta[1][7].wall_left = true;
    karta[8][8].wall_left = true;
    karta[5][9].wall_left = true;
    karta[6][9].wall_left = true;

    karta[6][0].wall_right = true;
    karta[8][2].wall_right = true;
    karta[5][2].wall_right = true;
    karta[4][3].wall_right = true;
    karta[5][3].wall_right = true;
    karta[3][4].wall_right = true;
    karta[4][4].wall_right = true;
    karta[5][4].wall_right = true;
    karta[2][5].wall_right = true;
    karta[3][5].wall_right = true;
    karta[1][6].wall_right = true;
    karta[8][7].wall_right = true;
    karta[5][8].wall_right = true;
    karta[6][8].wall_right = true;

}

