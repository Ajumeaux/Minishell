/*
** EPITECH PROJECT, 2021
** command_conditions
** File description:
** commands_cond
*/

#include "minishell.h"

int fill_cmd_array(minishell_t *shell, char **array, int i, int index)
{
    int nb_words = 0;

    while (array[i + nb_words] && array[i + nb_words][0] != ';')
        ++nb_words;
    shell->cmd.args[index] = malloc(sizeof(char *) * (nb_words + 1));
    for (int j = 0; j < nb_words; j++) {
        shell->cmd.args[index][j] = my_strcpy(array[i + j]);
    }
    shell->cmd.args[index][nb_words] = NULL;
    return (i + nb_words + 1);
}

int tcheck_exit(char **command, minishell_t *shell)
{
    if (my_strcmp(command[0], "exit") == 0 &&
    (command[1] || tcheck_all_int(command[1]))) {
        shell->exit = true;
        shell->exit_value = (command[1]) ? my_get_nbr(command[1]) : 0;
        free_array(command);
        free_shell(shell);
        return 1;
    }
    return 0;
}

void scanf_commands(minishell_t *shell)
{
    char **command = line_cmd(my_scanf());
    int j = 0;
    int i = 0;
    int cmd_nb = 1;

    if (tcheck_exit(command, shell) == 1)
        return;
    for (;command[i]; ++i)
        cmd_nb += (command[i][0] == ';') ? 1 : 0;
    i = 0;
    shell->cmd.args = malloc(sizeof(char **) * (cmd_nb + 1));
    if (!shell->cmd.args)
        return;
    while (i < cmd_nb) {
        j = fill_cmd_array(shell, command, j, i);
        ++i;
    }
    shell->cmd.args[cmd_nb] = NULL;
}

bool exe_exists(char *path)
{
    struct stat verif;

    return (stat(path, &verif) == 0 && verif.st_mode & S_IXUSR);
}