/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** my_setenv
*/

#include "minishell.h"

char *get_env_arg(minishell_t *shell)
{
    int len = my_strlen(shell->cmd.current_args[1]);
    char *line =  malloc(sizeof(char) * (len
                + my_strlen(shell->cmd.current_args[2]) + 3));

    if (!line)
        return NULL;
    line = my_strcpy(shell->cmd.current_args[1]);
    line[len] = '=';
    line[len + 1] = '\0';
    line = my_strcat(line, shell->cmd.current_args[2], 0);
    return (line);
}

void my_setenv(minishell_t *shell)
{
    int i = 0;
    char *line = get_env_arg(shell);
    int len = my_strlen(shell->cmd.current_args[1]);

    while (shell->env[i]) {
        if (my_strncmp(shell->env[i], shell->cmd.current_args[1],
        len) == 0 && shell->env[i][len] == '=') {
            free(shell->env[i]);
            shell->env[i] = line;
            return;
        }
        ++i;
    }
    shell->env = array_realloc(shell->env, 1);
    shell->env[i] = line;
    return;
}

int check_setenv_arg(minishell_t *shell, int i)
{
    if ((shell->cmd.current_args[1][i] < 'A' ||
    shell->cmd.current_args[1][i] > 'Z') &&
    (shell->cmd.current_args[1][i] < 'a' ||
    shell->cmd.current_args[1][i] < 'z') &&
    (shell->cmd.current_args[1][i] < '0' ||
    shell->cmd.current_args[1][i] > '9')) {
        if (i == 0) {
            write(2, "setenv: Variable name must begin with a letter.\n", 48);
            return 1;
        } else {
            write(2, "setenv: Variable name must ", 27);
            write(2, "contain alphanumeric characters.\n", 33);
            return 1;
        }
    }
    return 0;
}

int setenv_error_tcheck(minishell_t *shell)
{
    int i = 0;

    if (shell->cmd.current_args[2] != NULL
    && shell->cmd.current_args[3] != NULL) {
        write(2, "setenv: Too many arguments.\n", 28);
        return 1;
    }
    if (!shell->cmd.current_args[1]) {
        print_env(shell);
        return 1;
    }
    while (shell->cmd.current_args[1][i] != '\0') {
        if (check_setenv_arg(shell, i) != 0) {
            return 1;
        }
        ++i;
    }
    return 0;
}