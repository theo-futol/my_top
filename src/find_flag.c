/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static my_window_t *get_flag(char **argv, int i, my_window_t *window)
{
    char flag = argv[i][1];

    if (flag == 'U')
        window->username = argv[i + 1];
    if (flag == 'd')
        window->delay_refresh = atof(argv[i + 1]);
    if (flag == 'n')
        window->frames = atoi(argv[i + 1]);
    return window;
}

my_window_t *find_flag(int argc, char **argv, my_window_t *window)
{
    for (int i = 1; i != argc; i++){
        if (argv[i][0] == '-')
            window = get_flag(argv, i, window);
    }
    return window;
}
