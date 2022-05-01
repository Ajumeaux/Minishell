/*
** EPITECH PROJECT, 2021
** central functions
** File description:
** central
*/

#include "minishell.h"

int created_commands(minishell_t *shell)
{
    if (my_strcmp(shell->cmd.current_args[0], "cd") == 0) {
        my_cd(shell);
        return 1;
    }
    if (my_strcmp(shell->cmd.current_args[0], "env") == 0) {
        print_env(shell);
        return 1;
    }
    if (my_strcmp(shell->cmd.current_args[0], "setenv") == 0) {
        (setenv_error_tcheck(shell) == 0) ? my_setenv(shell) : 0;
        return 1;
    }
    if (my_strcmp(shell->cmd.current_args[0], "unsetenv") == 0) {
        my_unsetenv(shell);
        return 1;
    }
    return 0;
}

int check_pipe_redirect(minishell_t *shell)
{
    int i = my_arraylen(shell->cmd.current_args) - 1;

    for (; i > -1; --i) {
        if (shell->cmd.current_args[i][0] == '|'
        && shell->cmd.current_args[i][1] == '\0') {
            my_pipe(shell, i);
            return 1;
        }
        if (shell->cmd.current_args[i][0] == '>'
        && shell->cmd.current_args[i][1] == '\0') {
            redirect_right(shell, i);
            return 1;
        }
        if (shell->cmd.current_args[i][0] == '<'
        && shell->cmd.current_args[i][1] == '\0') {
            redirect_left(shell, i);
            return 1;
        }
    }
    return 0;
}

void minishell(minishell_t *shell)
{
    int i = 0;

    scanf_commands(shell);
    if (shell->exit)
        return;
    while (shell->cmd.args[i]) {
        shell->pipe = 0;
        shell->cmd.parsed_args = shell->cmd.args[i];
        shell->cmd.current_args = shell->cmd.args[i];
        (check_pipe_redirect(shell) == 0 && created_commands(shell) == 0 &&
        my_execve_bin(shell) == 0) ? my_exec_path(shell) : 0;
        ++i;
    }
}