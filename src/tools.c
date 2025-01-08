/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static int sub_len_int(int x)
{
    if (x >= 10000)
        return 5;
    if (x >= 1000)
        return 4;
    if (x >= 100)
        return 3;
    if (x >= 10)
        return 2;
    return 1;
}

int len_int(long int x)
{
    int count = 0;

    if (x < 0)
        count++;
    x = labs(x);
    if (x >= 1000000000)
        return count + 10;
    if (x >= 100000000)
        return count + 9;
    if (x >= 10000000)
        return count + 8;
    if (x >= 1000000)
        return count + 7;
    if (x >= 100000)
        return count + 6;
    if (count < 2)
        count += sub_len_int(x);
    return count;
}

char **str_word_in_array(char **array, char *str, char *delim, int lim)
{
    char *result = strtok(str, delim);
    int i = 0;

    for (; i != lim && result != NULL; i++){
        array[i] = result;
        result = strtok(NULL, delim);
    }
    array[i] = NULL;
    return array;
}

int is_digit(int c)
{
    return c >= '0' && c <= '9';
}
