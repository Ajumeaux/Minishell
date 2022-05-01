/*
** EPITECH PROJECT, 2021
** central functions
** File description:
** central
*/

#include "minishell.h"

void update_env_pwd(minishell_t *shell, int i)
{
    char *buffer = malloc(sizeof(char) * FILENAME_MAX);

    if (!buffer || !getcwd(buffer, FILENAME_MAX))
        return;
    if (shell->env[i])
        shell->env = array_realloc(shell->env, 1);
    shell->env[i] = malloc(sizeof(char) * (my_strlen(buffer) + 5));
    if (!shell->env[i])
        return;
    shell->env[i] = my_strcpy("PWD=");
    shell->env[i] = my_strcat(shell->env[i], buffer, 2);
}

void update_env_oldpwd(minishell_t *shell)
{
    int i = get_env_line_nb(shell, "PWD");
    int j = get_env_line_nb(shell, "OLDPWD");

    if (!shell->env[i]) {
        update_env_pwd(shell, i);
        return;
    }
    if (shell->env[j] != NULL)
        free(shell->env[j]);
    else shell->env = array_realloc(shell->env, 1);
    shell->env[j] = malloc(sizeof(char) * (my_strlen(shell->env[i]) + 4));
    if (!shell->env[j])
        return;
    shell->env[j] = my_strcpy("OLD");
    shell->env[j] = my_strcat(shell->env[j], shell->env[i], 0);
    update_env_pwd(shell, i);
}

void check_dir(minishell_t *shell)
{
    struct stat st;

    if (chdir(shell->cmd.current_args[1]) != -1)
        return;
    write(2, shell->cmd.current_args[1], my_strlen(shell->cmd.current_args[1]));
    if (lstat(shell->cmd.current_args[1], &st) != -1
        && (st.st_mode & S_IFMT) != S_IFDIR) {
        write(2, ": Not a directory.\n", 19);
    } else {
        write(2, ": No such file or directory.\n", 29);
    }
}

void my_cd(minishell_t *shell)
{
    if (shell->cmd.current_args[2] != NULL) {
        write(2, "cd: Too many arguments.\n", 24);
        return;
    }
    if (!shell->cmd.current_args[1] || (shell->cmd.current_args[1][0] == '~' &&
    shell->cmd.current_args[1][1] == '\0')) {
        if (chdir(retrieve_env_line(shell, "HOME")) == -1)
            write(2, "cd: No HOME in env.\n", 20);
    } else if ((shell->cmd.current_args[1][0] == '-' &&
    shell->cmd.current_args[1][1] == '\0')) {
        if (chdir(retrieve_env_line(shell, "OLDPWD")) == -1)
            write(2, ": No such file or directory.\n", 29);
    } else {
        check_dir(shell);
    }
    update_env_oldpwd(shell);
}