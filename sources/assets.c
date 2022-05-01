/*
** EPITECH PROJECT, 2021
** assets
** File description:
** assets
*/

#include "minishell.h"

int my_strcmp(char const *str1, char const *str2)
{
    if (my_strlen(str1) != my_strlen(str2))
        return 1;
    for (int i = 0; str1[i] != '\0'; ++i)
        if (str1[i] != str2[i])
            return 1;
    return 0;
}

int my_strncmp(char *str1, char *str2, int len)
{
    for (int i = 0; str1[i] != '\0' && i < len; ++i)
        if (str1[i] != str2[i]) {
            return (1);
        }
    return (0);
}

char *my_strcat(char *dest, char *to_cat, int to_free)
{
    int i = my_strlen(dest);
    char *str = malloc(sizeof(char) *
    (my_strlen(dest) + my_strlen(to_cat) + 2));

    if (dest)
        for (int i = 0; dest[i]; ++i)
            str[i] = dest[i];
    if (to_cat)
        for (int j = 0; to_cat[j]; ++j, ++i)
            str[i] = to_cat[j];
    str[i] = '\0';
    if (to_free != 0) {
        (to_free == 1 || to_free == 3) ? free(dest) : 0;
        (to_free == 2 || to_free == 3) ? free(to_cat) : 0;
    }
    return (str);
}

char **array_malloc(char **array, char *str, int ac)
{
    array = malloc(sizeof(char *) * ac + 1);
    if (!array)
        return NULL;
    for (int i = 0; i != ac + 1; i++) {
        array[i] = malloc(sizeof(char) * my_strlen(str));
        if (!array[i])
            return NULL;
    }
    return array;
}

char **array_remove_str(char **array, int i)
{
    if (my_arraylen(array) < i)
        return array;
    else free(array[i]);
    for (; i < my_arraylen(array); ++i)
        array[i] = array[i + 1];
    array[i] = NULL;
    return array;
}