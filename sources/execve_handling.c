/*
** EPITECH PROJECT, 2021
** minishell2final
** File description:
** exeve_handling
*/

#include "minishell.h"

char *retrieve_path(char *path, char *cmd)
{
    char *str = malloc(sizeof(char) *
    (my_strlen(path) + my_strlen(cmd) + 2));

    if (!str)
        return NULL;
    str = my_strcpy(path);
    str[my_strlen(path)] = (str[my_strlen(path) - 1] != '/') ?
    '/' : str[my_strlen(path)];
    str[my_strlen(path) + 1] = (str[my_strlen(path) - 1] != '/') ?
    '\0' : str[my_strlen(path) + 1];
    str = my_strcat(str, cmd, 0);
    return (str);
}

void put_command_not_fount(char *cmd)
{
    write(2, cmd, my_strlen(cmd));
    write(2, ": Command not found.\n", 21);
}

void my_exec_path(minishell_t *shell)
{
    int i = 0;
    char *str = NULL;
    char *path = shell->saved_path + 5;
    char **path_array = my_str_to_word_array(path, ':');

    (!access(shell->cmd.current_args[0], X_OK)) ?
    forked_execve(shell, shell->cmd.current_args[0]) : 0;
    if (!access(shell->cmd.current_args[0], X_OK))
        return;
    while (path_array[i]) {
        str = retrieve_path(path_array[i], shell->cmd.current_args[0]);
        if (!access(str, X_OK)) {
            forked_execve(shell, str);
            free(str);
            return;
        }
        ++i;
    }
    put_command_not_fount(shell->cmd.current_args[0]);
}

void forked_execve(minishell_t *shell, char *path)
{
    pid_t pid;

    pid = fork();
    (pid == -1) ? write(2, "error with fork\n", 16) : 0;
    if (!pid) {
        if (execve(path, shell->cmd.current_args, shell->env) == -1) {
            write(2, shell->cmd.current_args[0],
            my_strlen(shell->cmd.current_args[0]));
            write(2, ": Exec format error.\n", 21);
            exit(1);
        }
    } else pid_error_value(pid);
}

int my_execve_bin(minishell_t *shell)
{
    if (shell->cmd.current_args[0][0] == '.' &&
    shell->cmd.current_args[0][1] == '/' &&
    !access(shell->cmd.current_args[0], X_OK)) {
        forked_execve(shell, shell->cmd.current_args[0]);
        return 1;
    }
    else if ((opendir(shell->cmd.current_args[0]) != 0) ||
    (shell->cmd.current_args[0][0] == '.'
    && shell->cmd.current_args[0][1] == '/')) {
        write(2, shell->cmd.current_args[0],
        my_strlen(shell->cmd.current_args[0]));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    return 0;
}