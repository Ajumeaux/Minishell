/*
** EPITECH PROJECT, 2021
** assets
** File description:
** assets
*/

#include "minishell.h"

int char_left(char *str, int i)
{
    int count = 0;

    for (; str[i] != '\0'; i++)
        count += (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') ?
        1 : 0;
    return count;
}

char **array_realloc(char **array, int lines)
{
    int i = 0;
    char **cpy = NULL;

    if (!array) {
        return (NULL);
    }
    i = my_arraylen(array);
    cpy = malloc(sizeof(char *) * (i + 1 + lines));
    if (!cpy)
        return NULL;
    for (i = 0; array[i]; i++) {
        cpy[i] = my_strcpy(array[i]);
    }
    for (int j = 0; j <= lines; j++) {
        cpy[i + j] = NULL;
    }
    free_array(array);
    return (cpy);
}

int char_count(char const *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        count += (str[i] == c) ? 1 : 0;
    return count;
}

char **my_str_to_word_array(char *str, char c)
{
    int j = 0;
    int count = char_count(str, c);
    char **array = malloc(sizeof(char *) * (count + 2));

    if (!array)
        return NULL;
    for (int i = 0, k = 0; str[i]; ++j) {
        for (; str[i] == c && str[i]; ++i);
        if (!str[i] || !array)
            break;
        for (k = i; str[k] != c && str[k]; ++k);
        array[j] = malloc(sizeof(char) * (k - i + 2));
        if (!array[j])
            return NULL;
        for (k = 0; str[i] != c && str[i]; ++i, ++k)
            array[j][k] = str[i];
        array[j][k] = '\0';
    }
    array[j] = NULL;
    return array;
}

void pid_value_error(pid_t pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (!WIFEXITED(status)) {
        (WTERMSIG(status) != 8) ? write(2, strsignal(WTERMSIG(status)),
        my_strlen(strsignal(WTERMSIG(status)))) : 0;
        (WTERMSIG(status) == 8) ? write(2, "Floating exception", 18) : 0;
        (WCOREDUMP(status) == 128) ? write(2, " (core dumped)", 14) : 0;
        write(2, "\n", 1);
    }
}