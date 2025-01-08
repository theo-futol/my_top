/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

void my_getload_avg(double loadavg[])
{
    char *buffer = read_file("/proc/loadavg");
    char **word_array = NULL;

    if (buffer == NULL)
        return;
    word_array = my_str_to_word_array(buffer);
    for (int i = 0; i != 3; i++){
        loadavg[i] = atof(word_array[i]);
    }
    free(buffer);
}
