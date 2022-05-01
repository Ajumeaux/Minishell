/*
** EPITECH PROJECT, 2021
** array
** File description:
** heavy str managment
*/

#include "minishell.h"

int tcheck_all_int(char *str)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if ((str[i] < '0' || str[i] > '9')
        && str[i] != '-')
            return 1;
    }
    return 0;
}

void pid_error_value(pid_t pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (!WIFEXITED(status)) {
        if (WTERMSIG(status) != 8)
            write(2, strsignal(WTERMSIG(status)),
            my_strlen(strsignal(WTERMSIG(status))));
        if (WTERMSIG(status) == 8)
            write(2, "Floating exception", 19);
        if (WCOREDUMP(status) == 128)
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
}