/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

void count_user(int *users)
{
    DIR *dh = NULL;
    struct dirent *folder = NULL;
    int result_users = -2;

    dh = opendir("/var/run/user");
    if (dh == NULL)
        return;
    folder = readdir(dh);
    while (folder != NULL){
        folder = readdir(dh);
        result_users++;
    }
    closedir(dh);
    (*users) = result_users;
}
