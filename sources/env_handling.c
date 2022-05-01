/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** env_handling
*/

#include "minishell.h"

void print_env(minishell_t *shell)
{
    for (int i = 0; shell->env[i]; ++i) {
        write(1, shell->env[i], my_strlen(shell->env[i]));
        write(1, "\n", 1);
    }
}

int get_env_line_nb(minishell_t *shell, char *str)
{
    int i = 0;

    for (;shell->env[i] &&
    my_strncmp(shell->env[i], str, my_strlen(str)) != 0;
    ++i);
    return i;
}

char *retrieve_env_line(minishell_t *shell, char *line)
{
    int i = get_env_line_nb(shell, line);
    char *dest = NULL;

    if (!shell->env[i])
        return (NULL);
    dest = my_strcpy(shell->env[i]);
    while (*dest != '=')
        ++dest;
    return (dest + 1);
}