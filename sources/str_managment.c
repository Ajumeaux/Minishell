/*
** EPITECH PROJECT, 2021
** str managment
** File description:
** str_managment
*/

#include "minishell.h"

void free_shell(minishell_t *shell)
{
    for (int i = 0; shell->env[i]; ++i)
        free(shell->env[i]);
    free(shell->env);
    return;
}

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return (i);
}

int my_putstr(char *str)
{
    write(1, str, my_strlen(str));
    return (0);
}

bool dir_exists(char *path)
{
    struct stat verif;
    return (stat(path, &verif) == 0);
}

char **remove_str_from_array(char **tab, int i)
{
    int j = my_arraylen(tab);

    if (j < i) {
        return (tab);
    } else {
        free(tab[i]);
    }
    while (i < j && tab[i + 1]) {
        tab[i] = tab[i + 1];
        ++i;
    }
    tab[i] = NULL;
    return (tab);
}