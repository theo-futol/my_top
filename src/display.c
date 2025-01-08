/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** project my_top
*/

#include "../include/my.h"

static int display_time_day(my_window_t *window)
{
    int hour = (int)window->hour;
    int minutes = (int)window->minutes;

    if (window->days == 1 && window->hour == 0){
        mvprintw(0, 18, "%d day,  %02d min,", window->days, minutes);
        return len_int(window->days) + 14;
    }
    if (window->days > 1 && window->hour == 0){
        mvprintw(0, 18, "%d days,  %02d min,", window->days, minutes);
        return len_int(window->days) + 15;
    }
    if (window->days == 1){
        mvprintw(0, 18, "%d day, %d:%02d,", window->days, hour, minutes);
        return len_int(window->days) + len_int(window->hour) + 10;
    } else {
        mvprintw(0, 18, "%d days,  %d:%02d,", window->days, hour, minutes);
        return len_int(window->days) + len_int(window->hour) + 12;
    }
}

static int display_time_header(my_window_t *window)
{
    int hour = (int)window->hour;
    int minutes = (int)window->minutes;

    while (window->hour >= 24){
        window->hour -= 24;
        window->days++;
    }
    if (window->days > 0)
        return display_time_day(window);
    else if (window->hour > 1.0){
        mvprintw(0, 19, "%d:%02d,", hour, minutes);
        return len_int(hour) + 5;
    }
    mvprintw(0, 18, "%d min,", minutes);
    return len_int(minutes) + 5;
}

static void display_virt(char *virt, int j)
{
    double d_virt = atof(virt);

    if (d_virt > 9999999)
        mvprintw(7 + j, 35 - len_int((int)d_virt), "%.1fg", d_virt /
        1048576.0);
    else
        mvprintw(7 + j, 32 - len_int((int)d_virt), "%.0f", d_virt);
}

static void display_all_proc_sub(my_window_t *window, int i, int j)
{
    char buffer[20] = {0};

    sprintf(buffer, "%f", window->all_program[i].cpu);
    if (window->all_program[i].res[0] == '0')
        mvprintw(7 + j, 38, "%s", window->all_program[i].res);
    else
        mvprintw(7 + j, 31, "%s", window->all_program[i].res);
    if (window->all_program[i].virt[0] == '0')
        mvprintw(7 + j, 31, "%s", window->all_program[i].virt);
    else
        display_virt(window->all_program[i].virt, j);
    if (window->all_program[i].shr[0] == '0')
        mvprintw(7 + j, 45, "%s", window->all_program[i].shr);
    else
        mvprintw(7 + j, 47 - strlen(window->all_program[i].shr), "%s", window->
        all_program[i].shr);
    mvprintw(7 + j, 59 - strlen(buffer), "%.1f", window->all_program[i].cpu);
    mvprintw(7 + j, 57, "%.1f", window->all_program[i].mem);
}

static void display_all_proc(my_window_t *window, int start_column)
{
    int j = 0;

    for (int i = start_column; i != window->my_line_two.total; i++){
        mvprintw(7 + j, 6 - (len_int(window->all_program[i].pid) - 1), "%d",
        window->all_program[i].pid);
        mvprintw(7 + j, 8, "%s", window->all_program[i].user);
        if (window->all_program[i].pr == -100)
            mvprintw(7 + j, 18, "rt");
        else
            mvprintw(7 + j, 20 - (len_int(window->all_program[i].pr)), "%d",
            window->all_program[i].pr);
        mvprintw(7 + j, 24 - (len_int(window->all_program[i].ni)), "%d",
        window->all_program[i].ni);
        display_all_proc_sub(window, i, j);
        mvprintw(7 + j, 71, "%s", window->all_program[i].command);
        mvprintw(7 + j, 47, "%c", window->all_program[i].s);
        j++;
    }
}

static void display_line_one(my_window_t *window)
{
    int i = 20;

    mvprintw(0, 0, "top - %02d:%02d:%02d up", window->time->tm_hour, window->
    time->tm_min, window->time->tm_sec);
    i += display_time_header(window);
    if (window->users <= 1){
        mvprintw(0, i, "%d user, ", window->users);
        i += len_int(window->users) + 7;
    } else {
        mvprintw(0, i, "%d users, ", window->users);
        i += len_int(window->users) + 8;
    }
    mvprintw(0, i + 1, "load average: %.2f, %.2f, %.2f", window->loadavg[0],
    window->loadavg[1], window->loadavg[2]);
}

static void display_line_two(my_window_t *window)
{
    int i = 0;

    mvprintw(1, i, "Tasks: %d total,", window->my_line_two.total);
    i += 18;
    mvprintw(1, i + (3 - len_int(window->my_line_two.running)), "%d running,",
    window->my_line_two.running);
    i += 13;
    mvprintw(1, i + (3 - len_int(window->my_line_two.sleeping)), "%d sleeping,"
    , window->my_line_two.sleeping);
    i += 14;
    mvprintw(1, i + (3 - len_int(window->my_line_two.stopped)), "%d stopped,",
    window->my_line_two.stopped);
    i += 13;
    mvprintw(1, i + (3 - len_int(window->my_line_two.zombie)), "%d zombie",
    window->my_line_two.zombie);
}

static void display_line_four(my_window_t *window)
{
    line_four_t l_four = window->my_line_four;

    mvprintw(3, 0, "MiB Mem :  %.1f total,", l_four.total);
    mvprintw(3, 28, "%.1f free,", l_four.free);
    mvprintw(3, 43, "%.1f used,", l_four.used);
    mvprintw(3, 58, "%.1f buff/cache", l_four.buffer + l_four.cache +
    l_four.SReclaimable);
}

static void display_line_five(my_window_t *window)
{
    line_five_t l_five = window->my_line_five;
    double used = l_five.total - l_five.free;

    mvprintw(4, 0, "MiB Swap:   %.1f total,", l_five.total);
    mvprintw(4, 28
    , "%.1f free,", l_five.free);
    mvprintw(4, 46, "%.1f used.", used);
    mvprintw(4, 57, "%.1f avail Mem", window->my_line_four.avail);
}

void main_display(my_window_t *window, int start_column)
{
    struct winsize size_window = {0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_window) != -1){
        attron(A_REVERSE);
        mvprintw(6, 0, "    PID USER      PR  NI    VIRT    RES    SHR S  ");
        mvprintw(6, 49, " %%CPU  %%MEM     TIME+ COMMAND");
        for (int i = 78; i < size_window.ws_col; i++)
            mvprintw(6, i, " ");
        attroff(A_REVERSE);
        window->width = size_window.ws_col;
        window->height = size_window.ws_row;
    }
    display_line_one(window);
    display_line_two(window);
    display_line_four(window);
    display_line_five(window);
    display_all_proc(window, start_column);
}
