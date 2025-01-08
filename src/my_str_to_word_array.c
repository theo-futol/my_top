/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** function that splits a string into words
*/

#include <stdlib.h>
#include "../include/my.h"
#include <sys/stat.h>

static int is_alphanumeric(char c)
{
    if (c > 47 && c < 58){
        return 1;
    } else if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '.'){
        return 1;
    }
    return 0;
}

static int count_words(char const *str)
{
    int value = 1;

    for (int i = 0; str[i] != '\0'; i++){
        if (!is_alphanumeric(str[i])){
            value++;
        }
    }
    return value;
}

static char *add_word(char const *str, int i, int last)
{
    char *dest;
    int a = 0;

    dest = malloc(sizeof(char) * (i - last));
    for (; last <= i; last++){
        if (is_alphanumeric(str[last])){
            dest[a] = str[last];
            a++;
        }
    }
    dest[a] = '\0';
    return dest;
}

static int find_last_word(char const *str, int i)
{
    while (is_alphanumeric(str[i]))
        i++;
    return i;
}

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

char **my_str_to_word_array(char const *str)
{
    char **dest = NULL;
    int j = 0;
    int last_word = 0;
    int len_word = my_strlen(str) + 1;

    dest = malloc(sizeof(char *) * count_words(str) + 1);
    if (str == NULL || dest == NULL)
        return NULL;
    for (int i = 0; i != len_word; i++)
        if (!is_alphanumeric(str[i]) && i >= last_word){
            dest[j] = add_word(str, i, last_word);
            last_word = find_last_word(str, i);
            j++;
        }
    dest[j] = NULL;
    return dest;
}
