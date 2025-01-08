/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static my_window_t *update_line_two(my_window_t *window, char type, int i)
{
    window->all_program[i].s = type;
    switch (type){
        case 'R':
            window->my_line_two.running++;
            return window;
        case 'S':
        case 'I':
        case 'D':
            window->my_line_two.sleeping++;
            return window;
        case 'T':
            window->my_line_two.stopped++;
            return window;
        case 'Z':
            window->my_line_two.zombie++;
            return window;
    }
    return window;
}

static my_window_t *sub_complete_with_stat(my_window_t *window, char **stat,
    int i)
{
    double ticks = (double)sysconf(_SC_CLK_TCK);
    double time = 0.0;

    window->all_program[i].pr = atoi(stat[17]);
    window->all_program[i].ni = atoi(stat[18]);
    window->all_program[i].utime = atof(stat[13]);
    window->all_program[i].stime = atof(stat[14]);
    window->all_program[i].starttime = atof(stat[21]);
    window->all_program[i].cutime = atof(stat[15]);
    window->all_program[i].cstime = atof(stat[16]);
    window->all_program[i].cpu = window->all_program[i].utime + window->
    all_program[i].stime + window->all_program[i].cutime + window->all_program
    [i].cstime;
    time = window->uptime - (window->all_program[i].starttime / ticks);
    window->all_program[i].cpu = 100 * ((window->all_program[i].cpu / ticks) /
    time);
    return window;
}

static my_window_t *open_stat(my_window_t *window, int i, char *path)
{
    char new_path[20] = {0};
    char *buffer = NULL;
    char **stat = malloc(sizeof(char *) * 46);
    int idDel = 0;

    sprintf(new_path, "%s/%s/stat", "/proc", path);
    buffer = read_file(new_path);
    if (buffer == NULL || stat == NULL)
        return window;
    stat = str_word_in_array(stat, buffer, " ", 45);
    window = sub_complete_with_stat(window, stat, i);
    memmove(&stat[1][0], &stat[1][0 + 1], strlen(stat[1]) - 0);
    idDel = strlen(stat[1]) - 1;
    memmove(&stat[1][idDel], &stat[1][idDel + 1], strlen(stat[1]) - idDel);
    window->all_program[i].command = stat[1];
    free(stat);
    return window;
}

static my_program_t *cut_beggin(my_program_t *prog, int i)
{
    while (prog[i].shr[0] == 32 || prog[i].shr[0] == 9)
        memmove(&prog[i].shr[0], &prog[i].shr[0 + 1], strlen(prog[i].shr) - 0);
    return prog;
}

static my_window_t *sub_complete_with_status(my_window_t *window, int i, int j,
    char **stat2)
{
    my_program_t *prog = window->all_program;

    if (j == 24 && stat2[0][0] == 'R'){
        prog[i].shr = strtok(stat2[1], "k");
        prog = cut_beggin(prog, i);
    } else if (j == 24 && stat2[0][0] != 'R')
        prog[i].shr = "0";
    return window;
}

static my_window_t *complete_with_status(my_window_t *window, int i, int j,
    char **stat2)
{
    my_program_t *prog = window->all_program;

    if (j == 18 && stat2[0][0] == 'V'){
        prog[i].virt = strtok(stat2[1], "k");
        memmove(&prog[i].virt[0], &prog[i].virt[0 + 1], strlen(prog[i].virt)
        - 0);
    } else if (j == 18 && stat2[0][0] != 'V')
        prog[i].virt = "0";
    if (j == 21 && stat2[0][0] == 'V'){
        prog[i].res = strtok(stat2[1], "k");
        memmove(&prog[i].res[0], &prog[i].res[0 + 1], strlen(prog[i].res) - 0);
        window->all_program[i].mem = atof(window->all_program[i].res) / (window
        ->my_line_four.total * 1024) * 100;
    } else if (j == 21 && stat2[0][0] != 'V'){
        prog[i].res = "0";
        window->all_program[i].mem = atof(window->all_program[i].res) / (window
        ->my_line_four.total * 1024) * 100;
    }
    return sub_complete_with_status(window, i, j, stat2);
}

static my_window_t *get_user(my_window_t *window, int i)
{
    my_program_t *prog = window->all_program;
    struct stat stats = {0};
    char new_path[20] = {0};

    sprintf(new_path, "/proc/%d/", prog[i].pid);
    if (stat(new_path, &stats) == -1)
        return window;
    prog[i].user = strdup(getpwuid(stats.st_uid)->pw_name);
    if (strlen(prog[i].user) > 7){
        prog[i].user[7] = '+';
        prog[i].user[8] = '\0';
    }
    return window;
}

static my_window_t *free_all(char **stat, char **stat2, my_window_t *window)
{
    free(stat);
    free(stat2);
    return window;
}

static my_window_t *open_status(my_window_t *window, int i, char *path)
{
    char new_path[20] = {0};
    char *buffer = malloc(sizeof(char) * 2048);
    char **stat = malloc(sizeof(char *) * 26);
    char **stat2 = malloc(sizeof(char *) * 3);

    sprintf(new_path, "%s/%s/status", "/proc", path);
    buffer = read_file(new_path);
    if (buffer == NULL || stat == NULL || stat2 == NULL)
        return window;
    stat = str_word_in_array(stat, buffer, "\n", 25);
    for (int j = 0; stat[j] != NULL; j++){
        stat2 = str_word_in_array(stat2, stat[j], ":", 2);
        if (strcmp(stat2[0], "State") == 0)
            window = update_line_two(window, stat2[1][1], i);
        window = complete_with_status(window, i, j, stat2);
        window = get_user(window, i);
    }
    return free_all(stat, stat2, window);
}

my_window_t *get_all_proc(char *path, my_window_t *window)
{
    DIR *dh = NULL;
    struct dirent *folder = NULL;
    int i = 0;

    dh = opendir(path);
    window->all_program = allocate_memory_program(window->all_program,
    &window->my_line_two.total);
    if (dh == NULL || window->all_program == NULL)
        return window;
    for (folder = readdir(dh); folder != NULL; folder = readdir(dh)){
        if (is_digit(folder->d_name[0])){
            window->all_program[i].pid = atoi(folder->d_name);
            window = open_stat(window, i, folder->d_name);
            window = open_status(window, i, folder->d_name);
            i++;
        }
    }
    closedir(dh);
    return window;
}
