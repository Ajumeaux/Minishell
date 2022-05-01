/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** my_pipe
*/

#include "minishell.h"

void my_pipe_next(minishell_t *shell, int *save, int *fd, int i)
{
    int j = 0;

    i += 1;
    while (shell->cmd.current_args[i]) {
        shell->cmd.current_args[j] = shell->cmd.current_args[i];
        ++j;
        ++i;
    }
    shell->cmd.current_args[j] = NULL;
    dup2(fd[0], STDIN_FILENO);
    (check_pipe_redirect(shell) == 0 && created_commands(shell) == 0 &&
    my_execve_bin(shell) == 0) ? my_exec_path(shell) : 0;
    close(fd[0]);
    dup2(save[0], STDIN_FILENO);
    close(save[0]);
    free(save);
    free(fd);
}

void my_pipe(minishell_t *shell, int i)
{
    int *save = malloc(sizeof(int) * 2);
    int *fd = malloc(sizeof(int) * 2);

    if (!save || !fd)
        return;
    save[1] = dup(STDOUT_FILENO);
    save[0] = dup(STDIN_FILENO);
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    shell->cmd.current_args[i] = NULL;
    (check_pipe_redirect(shell) == 0 && created_commands(shell) == 0 &&
    my_execve_bin(shell) == 0) ? my_exec_path(shell) : 0;
    close(fd[1]);
    dup2(save[1], STDOUT_FILENO);
    close(save[1]);
    my_pipe_next(shell, save, fd, i);
}