/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static void complete_with_mem(my_window_t *window, char **stat2, int j)
{
    if (j == 0)
        window->my_line_four.total = atof(stat2[1]) / 1024;
    if (j == 1)
        window->my_line_four.free = atof(stat2[1]) / 1024;
    if (j == 3)
        window->my_line_four.buffer = atof(stat2[1]) / 1024;
    if (j == 23)
        window->my_line_four.SReclaimable = atof(stat2[1]) / 1024;
    if (j == 2)
        window->my_line_four.avail = atof(stat2[1]) / 1024;
    if (j == 4)
        window->my_line_four.cache = atof(stat2[1]) / 1024;
    if (j == 14)
        window->my_line_five.total = atof(stat2[1]) / 1024;
    if (j == 15)
        window->my_line_five.free = atof(stat2[1]) / 1024;
}

my_window_t *get_mem_info(char *path, my_window_t *window)
{
    char *buffer = read_file(path);
    char **stat = malloc(sizeof(char *) * 26);
    char **stat2 = malloc(sizeof(char *) * 3);

    if (buffer == NULL || stat == NULL || stat2 == NULL)
        return window;
    stat = str_word_in_array(stat, buffer, "\n", 25);
    for (int j = 0; stat[j] != NULL; j++){
        stat2 = str_word_in_array(stat2, stat[j], ":", 2);
        complete_with_mem(window, stat2, j);
    }
    window->my_line_four.used = window->my_line_four.total - window->
    my_line_four.free - (window->my_line_four.buffer + window->
    my_line_four.cache + window->my_line_four.SReclaimable);
    free(stat);
    free(stat2);
    return window;
}
