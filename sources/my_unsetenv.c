/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** my_unsetenv
*/

#include "minishell.h"

int unsetenv_error_tcheck(minishell_t *shell)
{
    if (!shell->cmd.current_args[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }
    if (shell->cmd.current_args[2] != NULL
    && shell->cmd.current_args[3] != NULL) {
        write(2, "unsetenv: Too many arguments.\n", 30);
        return 1;
    }
    return 0;
}

void my_unsetenv(minishell_t *shell)
{
    int len = (shell->cmd.current_args[1]) ?
    my_strlen(shell->cmd.current_args[1]) : 0;
    int i = 0;

    if (unsetenv_error_tcheck(shell) != 0)
        return;
    while (shell->env[i]) {
        if (my_strncmp(shell->env[i], shell->cmd.current_args[1], len) == 0
            && shell->env[i][len] == '=') {
            free(shell->env[i]);
            break;
        }
        ++i;
    }
    for (int j = i; shell->env[j] != NULL || j == i; ++j)
        shell->env[j] = (shell->env[j + 1]) ? shell->env[j + 1] : NULL;
}