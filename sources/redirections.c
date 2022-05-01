/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** redirections
*/

#include "minishell.h"

void redirect_left_end(minishell_t *shell, int fd_file, int keep_fd)
{
    if (dup2(fd_file, STDIN_FILENO) == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    (check_pipe_redirect(shell) == 0 && created_commands(shell) == 0 &&
    my_execve_bin(shell) == 0) ? my_exec_path(shell) : 0;
    close(fd_file);
    if (dup2(keep_fd, STDIN_FILENO) == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    close(keep_fd);
}

void redirect_left(minishell_t *shell, int i)
{
    int fd_file = 0;
    int keep_fd = 0;

    if (shell->cmd.current_args[i + 1] == NULL)
        return;
    keep_fd = dup(STDIN_FILENO);
    if (keep_fd == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    fd_file = open(shell->cmd.current_args[i + 1], O_RDONLY);
    if (fd_file == -1 ) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    remove_str_from_array(shell->cmd.current_args, i);
    remove_str_from_array(shell->cmd.current_args, i);
    redirect_left_end(shell, fd_file, keep_fd);
}

void redirect_right_end(minishell_t *shell, int fd_file, int keep_fd)
{
    if (dup2(fd_file, STDOUT_FILENO) == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    (check_pipe_redirect(shell) == 0 && created_commands(shell) == 0 &&
    my_execve_bin(shell) == 0) ? my_exec_path(shell) : 0;
    close(fd_file);
    if (dup2(keep_fd, STDOUT_FILENO) == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    close(keep_fd);
}

void redirect_right(minishell_t *shell, int i)
{
    int fd_file = 0;
    int keep_fd = 0;

    if (shell->cmd.current_args[i + 1] == NULL)
        return;
    keep_fd = dup(STDOUT_FILENO);
    if (keep_fd == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    fd_file = open(shell->cmd.current_args[i + 1],
    O_CREAT | O_RDWR | O_TRUNC, 00664);
    if (fd_file == -1) {
        write(2, strerror(errno), my_strlen(strerror(errno)));
        return;
    }
    remove_str_from_array(shell->cmd.current_args, i);
    remove_str_from_array(shell->cmd.current_args, i);
    redirect_right_end(shell, fd_file, keep_fd);
}