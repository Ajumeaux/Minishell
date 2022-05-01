/*
** EPITECH PROJECT, 2021
** array
** File description:
** heavy str managment
*/

#include "minishell.h"

int find_line(char *str, char **env)
{
    int i = 0;

    for (; my_strncmp(str, env[i], my_strlen(str)) != 0 && env[i] != NULL; i++);
    if (i == my_arraylen(env))
        return (-1);
    return i;
}

char *my_cp_str(char *str1, char *str2)
{
    char *res = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2)));
    int i = 0;

    if (!res)
        return NULL;
    for (; str1[i] != '\0'; i++)
        res[i] = str1[i];
    res[i] = '/';
    i++;
    for (int j = 0; str2[j] != '\0'; j++) {
        res[i] = str2[j];
        i++;
    }
    free(str1);
    free(str2);
    return res;
}

int my_arraylen(char **array)
{
    int i = 0;

    while (array[i]) {
        i++;
    }
    return (i);
}

void free_array(char **array)
{
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}