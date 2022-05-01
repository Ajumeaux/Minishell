/*
** EPITECH PROJECT, 2021
** main for minishell
** File description:
** main
*/

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    minishell_t shell;

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        write(1, "Look at the tcsh shell, mine is about the same.\n", 49);
        return (0);
    }
    else if (ac >= 2 && av[1][0] != '-')
        return 84;
    shell.exit = false;
    shell.exit_value = 0;
    if (!env[0])
        create_env(&shell);
    else shell.env = my_arraycpy(env);
    shell.saved_path = retrieve_env_line(&shell, "PATH");
    while (!shell.exit) {
        minishell(&shell);
    }
    return (shell.exit_value);
}