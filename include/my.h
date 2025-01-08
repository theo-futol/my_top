/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#ifndef MY_H
    #define MY_H
// include
    #include <ncurses.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <time.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/ioctl.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <pwd.h>

// struct
typedef struct my_program {
    int pid;
    char *user;
    int pr;
    int ni;
    char *virt;
    char *res;
    char *shr;
    char s;
    float cpu;
    float mem;
    char *time;
    char *command;
    double utime;
    double stime;
    double starttime;
    double cutime;
    double cstime;
} my_program_t;
typedef struct line_two {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} line_two_t;
typedef struct line_four {
    double total;
    double free;
    double used;
    double SReclaimable;
    double cache;
    double buffer;
    double avail;
} line_four_t;
typedef struct line_five {
    double total;
    double free;
} line_five_t;
typedef struct my_window {
    WINDOW *window;
    int is_display;
    int width;
    int height;
    int frames;
    float delay_refresh;
    char *username;
    double loadavg[4];
    struct tm *time;
    double uptime;
    int days;
    double hour;
    double minutes;
    int users;
    my_program_t *all_program;
    line_two_t my_line_two;
    line_four_t my_line_four;
    line_five_t my_line_five;
} my_window_t;

// prototype
my_window_t *find_flag(int argc, char **argv, my_window_t *window);
void my_getload_avg(double loadavg[]);
char **my_str_to_word_array(char const *str);
void my_getuptime(my_window_t **window);
char *read_file(char *path);
void count_user(int *users);
my_window_t *get_all_proc(char *path, my_window_t *window);
void main_display(my_window_t *window, int start_column);
my_program_t *allocate_memory_program(my_program_t *all_program,
    int *all_proc);
int len_int(long int x);
char **str_word_in_array(char **array, char *str, char *delim, int lim);
int is_digit(int c);
my_window_t *get_mem_info(char *path, my_window_t *window);
#endif
