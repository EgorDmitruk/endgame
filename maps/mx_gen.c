#include "header.h"

int mx_count_wall(cell square) {
    int res = 0;
    if (square.wall_up == true)
        ++res;
    if (square.wall_down == true)
        ++res;
    if (square.wall_left == true)
        ++res;
    if (square.wall_right == true)
        ++res;
    return res;
}

int mx_count_free(cell map[10][10], int i, int j) {
    int res = 0;
    if (map[i][j].wall_up == false && map[i - 1][j].river == NULL
        && map[i - 1][j].portal == NULL)
        ++res;
    if (map[i][j].wall_down == false && map[i + 1][j].river == NULL
        && map[i + 1][j].portal == NULL)
        ++res;
    if (map[i][j].wall_left == false && map[i][j - 1].river == NULL
        && map[i][j - 1].portal == NULL)
        ++res;
    if (map[i][j].wall_right == false && map[i][j + 1].river == NULL
        && map[i][j + 1].portal == NULL)
        ++res;
    return res;
}

void mx_trim(cell map[10][10]) {
    int count, iter;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 10; ++j) {
            count = 0;
            while (map[j][i].wall_down == false) {
                if (map[j][i].wall_right == false) {
                    count = -1;
                    break;
                }
                else {
                    ++count;
                    ++j;
                }
            }
            if (count != -1) {
                j -= count;
                iter = rand() % (count + 1) + j;
                map[iter][i].wall_right = false;
                map[iter][i + 1].wall_left = false;
            }
            while (map[j][i].wall_down == false)
                ++j;
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 10; ++j) {
            count = 0;
            while (map[i][j].wall_right == false) {
                if (map[i][j].wall_down == false) {
                    count = -1;
                    break;
                }
                else {
                    ++count;
                    ++j;
                }
            }
            if (count != -1) {
                j -= count;
                iter = rand() % (count + 1) + j;
                map[i][iter].wall_down = false;
                map[i + 1][iter].wall_up = false;
            }
            while (map[i][j].wall_right == false)
                ++j;
        }
    }
    for (int i = 9; i > 0; --i) {
        for (int j = 9; j >= 0; --j) {
            count = 0;
            while (map[j][i].wall_up == false) {
                if (map[j][i].wall_left == false) {
                    count = -1;
                    break;
                }
                else {
                    ++count;
                    --j;
                }
            }
            if (count != -1) {
                j += count;
                iter = j - rand() % (count + 1);
                map[iter][i].wall_left = false;
                map[iter][i - 1].wall_right = false;
            }
            while (map[j][i].wall_up == false)
                --j;
        }
    }
    for (int i = 9; i > 0; --i) {
        for (int j = 9; j >= 0; --j) {
            count = 0;
            while (map[i][j].wall_left == false) {
                if (map[i][j].wall_up == false) {
                    count = -1;
                    break;
                }
                else {
                    ++count;
                    --j;
                }
            }
            if (count != -1) {
                j += count;
                iter = j - rand() % (count + 1);
                map[i][iter].wall_up = false;
                map[i - 1][iter].wall_down = false;
            }
            while (map[i][j].wall_left == false)
                --j;
        }
    }
}

// речки 1-3, порталы 1-3
// речка, стены, порталы, клады, выход

void mx_gen(cell map[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            map[j][i].x = i;
            map[j][i].y = j;
            map[j][i].wall_up = false;
            map[j][i].wall_down = false;
            map[j][i].wall_left = false;
            map[j][i].wall_right = false;
            map[j][i].river = NULL;
            map[j][i].river_num = -1;
            map[j][i].portal = NULL;
            map[j][i].portal_num = -1;
            map[j][i].treasure = -1;
        }
    }

    for (int i = 0; i < 10; ++i) {
        map[i][0].wall_left = true;
        map[i][9].wall_right = true;
        map[0][i].wall_up = true;
        map[9][i].wall_down = true;
    }

    srand(time(0));
    int river_count = rand() % 3;
    // одна речка - её длина 12; две - 3-9 / 4-8 / 5-7 / 6-6;
    // три - 3-3-6 / 3-4-5 / 4-4-4
    int portal_count = rand() % 3;
    // один портал - в цепочке 6 порталов; два - 2-4 / 3-3; три - 2-2-2
    int x, y, currx, curry;

    // река не должна течь под стенкой, не должна соприкосаться с собой и другими реками
    int iter = river_count == 0 ? 12 : river_count == 1 ? rand() % 4 + 3 : rand() % 2 + 3;
    int prev_iter = iter;
    cell *next1, *next2;
    for (int i = 0; i < river_count + 1; ++i) {
        mx_randyx(&y, &x);
        while (mx_count_free(map, y, x) != 4 || map[y][x].river != NULL)
            mx_randyx(&y, &x);
        next1 = &map[y][x];
        next2 = &map[y][x];
        map[y][x].river = &map[y][x];
        map[y][x].river_num = i;
        curry = y;
        currx = x;
        for (int j = 1; j < iter; ++j) {
            if (j > 1 && ((map[y - 1][x].river != NULL && mx_count_free(map, y + 1, x) < 3
                && mx_count_free(map, y, x - 1) < 3 && mx_count_free(map, y, x + 1) < 3)
                || (mx_count_free(map, y - 1, x) < 3 && map[y + 1][x].river != NULL
                && mx_count_free(map, y, x - 1) < 3 && mx_count_free(map, y, x + 1) < 3)
                || (mx_count_free(map, y - 1, x) < 3 && mx_count_free(map, y + 1, x) < 3
                && map[y][x - 1].river != NULL && mx_count_free(map, y, x + 1) < 3)
                || (mx_count_free(map, y - 1, x) < 3 && mx_count_free(map, y + 1, x) < 3
                && mx_count_free(map, y, x - 1) < 3 && map[y][x + 1].river != NULL))) {
                if (j > 2)
                    break;
                else {
                    map[curry][currx].river = NULL;
                    map[curry][currx].river_num = -1;
                    for (int k = curry - 1; k <= curry + 1; ++k) {
                        for (int n = currx - 1; n <= currx + 1; ++n) {
                            if (&map[k][n] == next2) {
                                curry = k;
                                currx = n;
                                j = 1;
                                break;
                            }
                        }
                    }
                }
            }
            x = currx;
            y = curry;
            int sign = rand() % 2 == 0 ? 1 : -1;
            if (rand() % 2 == 0)
                y = curry + sign;
            else
                x = currx + sign;
            while (mx_count_free(map, y, x) != 3 || map[y][x].river != NULL) {
                x = currx;
                y = curry;
                sign = rand() % 2 == 0 ? 1 : -1;
                if (rand() % 2 == 0)
                    y = curry + sign;
                else
                    x = currx + sign;
            }
            map[y][x].river = j % 2 == 1 ? next1 : next2;
            map[y][x].river_num = i;
            if (j % 2 == 1)
                next1 = &map[y][x];
            else
                next2 = &map[y][x];
            curry = y;
            currx = x;
        }
        if (river_count == 2)
            iter = i == 2 ? 12 - prev_iter - iter : rand() % 2 + 3;
        else
            iter = 12 - iter;
    }

    // на одну клетку максимум две стенки, стенка не должна идти по берегу речки
    for (int i = 0; i < 10; ++i) {
        for (int j = 1; j < 10; ++j) {
            if (map[i][j].river == NULL && mx_count_free(map, i, j) == 4) {
                int corner = rand() % 4;
                switch(corner) {
                    case 0: {
                        map[i][j].wall_up = true;
                        map[i - 1][j].wall_down = true;
                        map[i][j].wall_left = true;
                        map[i][j - 1].wall_right = true;
                        break;
                    }
                    case 1: {
                        map[i][j].wall_up = true;
                        map[i - 1][j].wall_down = true;
                        map[i][j].wall_right = true;
                        map[i][j + 1].wall_left = true;
                        break;
                    }
                    case 2: {
                        map[i][j].wall_down = true;
                        map[i + 1][j].wall_up = true;
                        map[i][j].wall_left = true;
                        map[i][j - 1].wall_right = true;
                        break;
                    }
                    case 3: {
                        map[i][j].wall_down = true;
                        map[i + 1][j].wall_up = true;
                        map[i][j].wall_right = true;
                        map[i][j + 1].wall_left = true;
                        break;
                    }
                }
            }
        }
    }
    int wall;
    for (int i = 0; i < 10; ++i) {
        if (mx_count_wall(map[0][i]) == 1) {
            if ((i == 0 && mx_count_wall(map[0][i + 1]) == 1)
                || (i == 9 && mx_count_wall(map[0][i - 1]) == 1)
                || (mx_count_wall(map[0][i - 1]) == 1 && mx_count_wall(map[0][i + 1]) == 1)) {
                wall = rand() % 2;
                if (wall == 0) {
                    map[0][i].wall_left = true;
                    map[0][i - 1].wall_right = true;
                }
                else {
                    map[0][i].wall_right = true;
                    map[0][i + 1].wall_left = true;
                }
            }
        }
        if (mx_count_wall(map[9][i]) == 1) {
            if ((i == 0 && mx_count_wall(map[9][i + 1]) == 1)
                || (i == 9 && mx_count_wall(map[9][i - 1]) == 1)
                || (mx_count_wall(map[9][i - 1]) == 1 && mx_count_wall(map[9][i + 1]) == 1)) {
                wall = rand() % 2;
                if (wall == 0) {
                    map[9][i].wall_left = true;
                    map[9][i - 1].wall_right = true;
                }
                else {
                    map[9][i].wall_right = true;
                    map[9][i + 1].wall_left = true;
                }
            }
        }
        if (mx_count_wall(map[i][0]) == 1) {
            if ((i == 0 && mx_count_wall(map[i + 1][0]) == 1)
                || (i == 9 && mx_count_wall(map[i - 1][0]) == 1)
                || (mx_count_wall(map[i - 1][0]) == 1 && mx_count_wall(map[i + 1][0]) == 1)) {
                wall = rand() % 2;
                if (wall == 0) {
                    map[i][0].wall_up = true;
                    map[i - 1][0].wall_down = true;
                }
                else {
                    map[i][0].wall_down = true;
                    map[i + 1][0].wall_up = true;
                }
            }
        }
        if (mx_count_wall(map[i][9]) == 1) {
            if ((i == 0 && mx_count_wall(map[i + 1][9]) == 1)
                || (i == 9 && mx_count_wall(map[i - 1][9]) == 1)
                || (mx_count_wall(map[i - 1][9]) == 1 && mx_count_wall(map[i + 1][9]) == 1)) {
                wall = rand() % 2;
                if (wall == 0) {
                    map[i][9].wall_up = true;
                    map[i - 1][9].wall_down = true;
                }
                else {
                    map[i][9].wall_down = true;
                    map[i + 1][9].wall_up = true;
                }
            }
        }
    }
    mx_trim(map);

    // две стены-две свободные / одна стена-от двух свободных / нет стен-от двух свободных
    iter = portal_count == 0 ? 6 : portal_count == 2 ? 2 : rand() % 2 + 2;
    cell *first_portal;
    for (int i = 0; i < portal_count + 1; ++i) {
        mx_randyx(&y, &x);
        while (!((mx_count_wall(map[y][x]) == 2 && mx_count_free(map, y, x) == 2)
               || (mx_count_wall(map[y][x]) == 1 && mx_count_free(map, y, x) > 1)
               || (mx_count_wall(map[y][x]) == 0 && mx_count_free(map, y, x) > 1))
               || map[y][x].portal != NULL || map[y][x].river != NULL)
            mx_randyx(&y, &x);
        first_portal = &map[y][x];
        curry = y;
        currx = x;
        for (int j = 1; j < iter; ++j) {
            mx_randyx(&y, &x);
            while (!((mx_count_wall(map[y][x]) == 2 && mx_count_free(map, y, x) == 2)
                   || (mx_count_wall(map[y][x]) == 1 && mx_count_free(map, y, x) > 1)
                   || (mx_count_wall(map[y][x]) == 0 && mx_count_free(map, y, x) > 1))
                   || map[y][x].portal != NULL || map[y][x].river != NULL)
                mx_randyx(&y, &x);
            map[curry][currx].portal = &map[y][x];
            map[curry][currx].portal_num = i;
            curry = y;
            currx = x;
        }
        map[curry][currx].portal = first_portal;
        map[curry][currx].portal_num = i;
        iter = portal_count == 2 ? 2 : 6 - iter;
    }

    // не река не портал
    for (int i = 0; i < 2; ++i) {
        mx_randyx(&y, &x);
        while (map[y][x].river != NULL || map[y][x].portal != NULL
               || map[y][x].treasure != -1)
            mx_randyx(&y, &x);
        map[y][x].treasure = i;
    }

    // нет ни портала, ни клада
    mx_randyx(&y, &x);
    wall = rand() % 4;
    switch(wall) {
        case 0: {
            x = 0;
            break;
        }
        case 1: {
            x = 9;
            break;
        }
        case 2: {
            y = 0;
            break;
        }
        case 3: {
            y = 9;
            break;
        }
    }
    while (map[y][x].portal != NULL || map[y][x].treasure != -1
           || (x == 0 && map[y][x + 1].river != NULL)
           || (x == 9 && map[y][x - 1].river != NULL)
           || (y == 0 && map[y + 1][x].river != NULL)
           || (y == 9 && map[y - 1][x].river != NULL)) {
        mx_randyx(&y, &x);
        wall = rand() % 4;
        switch(wall) {
            case 0: {
                x = 0;
                break;
            }
            case 1: {
                x = 9;
                break;
            }
            case 2: {
                y = 0;
                break;
            }
            case 3: {
                y = 9;
                break;
            }
        }
    }
    if (x == 0)
        map[y][x].wall_left = false;
    else if (x == 9)
        map[y][x].wall_right = false;
    else if (y == 0)
        map[y][x].wall_up = false;
    else
        map[y][x].wall_down = false;
}

