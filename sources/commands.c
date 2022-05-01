/*
** EPITECH PROJECT, 2021
** commands
** File description:
** functions rzlatives to commands
*/

#include "minishell.h"

char *my_pwd(void)
{
    char *buffer = malloc(sizeof(char) * FILENAME_MAX);

    if (!buffer)
        return NULL;
    getcwd(buffer, FILENAME_MAX);
    return buffer;
}

void my_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        write(1, env[i], my_strlen(env[i]));
        write(1, "\n", 1);
    }
}