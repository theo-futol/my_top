/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static int open_file(char *path)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1)
        return 84;
    return fd;
}

char *read_file(char *path)
{
    int fd = open_file(path);
    struct stat info_file = {0};
    char *buffer = NULL;

    if (stat(path, &info_file) == -1 || fd == 84)
        return NULL;
    if (info_file.st_size == 0)
        info_file.st_size = 2048;
    buffer = malloc(sizeof(char) * info_file.st_size + 1);
    if (buffer == NULL)
        return NULL;
    if (read(fd, buffer, info_file.st_size) == -1)
        return NULL;
    close(fd);
    return buffer;
}
