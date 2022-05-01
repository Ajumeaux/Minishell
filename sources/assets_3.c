/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** assets_3
*/

#include "minishell.h"

int my_get_nbr(char const *str)
{
    int res = 0;
    int neg = 1;
    unsigned int j = 0;
    unsigned int i = 1;

    if (!str)
        return (0);
    for (;str[j] == '-' || str[j] == '+'; ++j)
        neg *= (str[j] == '-') ? -1 : 1;
    while (str[j] >= '0' && str[j] <= '9') {
        if (i == 10)
            return (0);
        res *= 10;
        res += str[j] - 48;
        ++j;
        ++i;
    }
    return (res * neg);
}

void create_env(minishell_t *shell)
{
    shell->env = malloc(sizeof(char *) * 12);
    shell->env[0] = my_strcpy("HOSTTYPE=x86_64-linux");
    shell->env[1] = my_strcpy("VENDOR=unknow");
    shell->env[2] = my_strcpy("OSTYPE=linux");
    shell->env[3] = my_strcpy("MATCHTYPE=x86_64");
    shell->env[4] = my_strcpy("LOGNAME=antoine");
    shell->env[5] = my_strcpy("USER=antoine");
    shell->env[6] = my_strcpy("GROUP=antoine");
    shell->env[7] = my_strcpy("HOST=localdomain");
    shell->env[8] = my_strcpy("HOME=/home/antoine");
    shell->env[9] =
        my_strcpy("PATH=/home/antoine/bin:/usr/local/bin:/usr/bin:/bin");
    update_env_pwd(shell, 10);
    shell->env[11] = NULL;
}

char *my_strcpy(char const *src)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * (my_strlen(src)));

    if (!dest)
        return NULL;
    for (; src[i]; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}

char **my_arraycpy(char **array)
{
    int i = 0;
    int j = 0;
    char **cpy = NULL;

    for (; array[i]; ++i);
    cpy = malloc(sizeof(char *) * (i + 1));
    if (!cpy)
        return NULL;
    while (array[j]) {
        cpy[j] = my_strcpy(array[j]);
        ++j;
    }
    cpy[i] = NULL;
    return (cpy);
}