/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "include/my.h"

static my_window_t *init_window(int argc, char **argv)
{
    my_window_t *window = malloc(sizeof(my_window_t));
    struct winsize size_window = {0};

    if (window == NULL || ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_window) == -1)
        return NULL;
    window->is_display = 1;
    window->window = NULL;
    window->width = size_window.ws_col;
    window->height = size_window.ws_row;
    window->frames = -1;
    window->delay_refresh = 3.0;
    window->username = NULL;
    window = find_flag(argc, argv, window);
    window->window = initscr();
    window->all_program = allocate_memory_program(window->all_program,
    &window->my_line_two.total);
    if (window->window == NULL || window->all_program == NULL)
        return NULL;
    keypad(window->window, TRUE);
    return window;
}

void refresh_data(my_window_t *window, time_t *clock)
{
    my_getuptime(&window);
    my_getload_avg(window->loadavg);
    window->time = localtime(clock);
    count_user(&window->users);
    window->my_line_two.running = 0;
    window->my_line_two.sleeping = 0;
    window->my_line_two.stopped = 0;
    window->my_line_two.zombie = 0;
    window = get_mem_info("/proc/meminfo", window);
    window = get_all_proc("/proc/", window);
}

static int free_all(my_window_t *window)
{
    endwin();
    delwin(window->window);
    free(window->all_program);
    free(window);
    return 0;
}

static int manage_input(my_window_t **window, int *start_column)
{
    int input = getch();

    if (input == 'q'){
        (*window)->is_display = 0;
        return free_all(*window);
    }
    if (input == KEY_DOWN)
        if ((*window)->all_program[*start_column + 49].command != NULL)
            (*start_column)++;
    if (input == KEY_UP)
        if (*start_column - 1 >= 0)
            (*start_column)--;
    return -1;
}

int main(int argc, char **argv)
{
    my_window_t *window = init_window(argc, argv);
    time_t clock = window->delay_refresh;
    int start_column = 0;

    if (window == NULL)
        return 84;
    while (window->is_display){
        nodelay(window->window, 1);
        noecho();
        if (manage_input(&window, &start_column) == 0)
            return 0;
        if (time(NULL) - clock >= window->delay_refresh){
            clear();
            clock = time(NULL);
            refresh_data(window, &clock);
        }
        main_display(window, start_column);
        refresh();
    }
    return free_all(window);
}
