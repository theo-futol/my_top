/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

my_program_t *allocate_memory_program(my_program_t *all_program, int *all_proc)
{
    DIR *dh = opendir("/proc/");
    struct dirent *folder = NULL;
    int count = 0;

    if (dh == NULL)
        return all_program;
    folder = readdir(dh);
    while (folder != NULL){
        if (is_digit(folder->d_name[0]))
            count++;
        folder = readdir(dh);
    }
    (*all_proc) = count;
    if (all_program != NULL)
        free(all_program);
    all_program = malloc(sizeof(my_program_t) * count);
    closedir(dh);
    return all_program;
}
