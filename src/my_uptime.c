/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

void my_getuptime(my_window_t **window)
{
    char *buffer = read_file("/proc/uptime");
    char time[100] = {0};
    my_window_t *w = *window;

    if (buffer == NULL)
        return;
    for (int i = 0; buffer[i] != ' '; i++)
        time[i] = buffer[i];
    w->days = 0;
    w->minutes = atof(time);
    w->uptime = w->minutes;
    w->hour = w->minutes / 3600;
    w->minutes = ((int)(w->minutes) % 3600);
    w->minutes = w->minutes / 3600 * 60;
    free(buffer);
}
