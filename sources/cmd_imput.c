/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** cmd_imput
*/

#include "minishell.h"

char *my_scanf(void)
{
    size_t size = 0;
    int nb_scan;
    char *buffer;

    my_putstr("$> ");
    nb_scan = getline(&buffer, &size, stdin);
    if (buffer[my_strlen(buffer) - 1] == '\n')
        buffer[my_strlen(buffer) - 1] = '\0';
    if (nb_scan == -1) {
        write(1, "exit\n", 5);
        return "exit";
    }
    return (buffer);
}

int new_cmd(char *str, int j)
{
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        ++i;
    while (str[i] != '\0') {
        if (char_left(str, i) != 0 && (str[i] == ' ' || str[i] == '\t')
        && i == j && str[i + 1] != ' ' && str[i + 1] != '\t') {
            return 1;
        }
        ++i;
    }
    return 0;
}

int count_words(char *str)
{
    int count = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        ++i;
    while (str[i] != '\0') {
        count += ((str[i] == ' ' || str[i] == '\t')
        && str[i + 1] != ' ' && str[i + 1] != '\t'
        && str[i + 1] != '\0') ? 1 : 0;
        ++i;
    }
    return count;
}

char **fill_line_tab(char **tab, char *str, int line, int column)
{
    for (int i = 0; i < 200 && str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
        && new_cmd(str, i) == 0) {
            tab[line][column] = str[i];
            ++column;
        } else if (new_cmd(str, i) == 1) {
            tab[line][column] = '\0';
            ++line;
            column = 0;
            tab[line] = malloc(sizeof(char) * (my_strlen(str) + 1));
            if (!tab[line])
                return NULL;
        }
    }
    tab[line][column] = '\0';
    tab[line + 1] = NULL;
    return tab;
}

char **line_cmd(char *str)
{
    int line = 0;
    int column = 0;
    char **tab = malloc(sizeof(char *) * (count_words(str) + 1));

    if (!tab)
        return NULL;
    tab[0] = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (!tab[0])
        return NULL;
    tab = fill_line_tab(tab, str, line, column);
    return (tab);
}