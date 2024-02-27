#include "../inc/header.h"

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

