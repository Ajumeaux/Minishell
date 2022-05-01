/*
** EPITECH PROJECT, 2021
** .h file for the minishell
** File description:
** minishell
*/

#define _unknown_cmd_ "Command not found.\n"

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

typedef struct
{
    char **current_args;
    char **parsed_args;
    char ***args;
} cmd_struct_t;

typedef struct
{
    bool exit;
    int exit_value;
    char *saved_path;
    int pipe;
    char **env;
    cmd_struct_t cmd;
} minishell_t;

int my_strlen(char const *str);
int my_arraylen(char **array);
int my_putstr(char *str);

//bool functions
bool dir_exists(char *path);
bool exe_exists(char *path);
bool is_execve(char *arg);
int my_strcmp(char const *str1, char const *str2);
int my_strncmp(char *str1, char *str2, int len);

//get_cmd_functions
void scanf_commands(minishell_t *shell);

//counting functions
char *retrieve_env_line(minishell_t *shell, char *line);
int get_env_line_nb(minishell_t *shell, char *str);

//execve
int my_execve_bin(minishell_t *shell);
void my_exec_path(minishell_t *shell);

//created_functions
void print_env(minishell_t *shell);
void my_cd(minishell_t *shell);
void my_pipe(minishell_t *shell, int i);
void redirect_right(minishell_t *shell, int i);
void redirect_left(minishell_t *shell, int i);
void update_env_pwd(minishell_t *shell, int i);

//frees
void free_shell(minishell_t *shell);
void free_array(char **array);

//error_tcheck
int setenv_error_tcheck(minishell_t *shell);
int unsetenv_error_tcheck(minishell_t *shell);
void pid_error_value(pid_t pid);

//central
void minishell(minishell_t *shell);
int created_commands(minishell_t *shell);
int check_pipe_redirect(minishell_t *shell);
char **line_cmd(char *str);

//env_related
void create_env(minishell_t *shell);
void my_setenv(minishell_t *shell);
void my_unsetenv(minishell_t *shell);

//my_execve
void forked_execve(minishell_t *shell, char *path);

//assets
int char_left(char *str, int i);
char **remove_str_from_array(char **tab, int i);
int my_get_nbr(char const *str);
char **my_arraycpy(char **array);
char **array_realloc(char **array, int lines);
char **my_str_to_word_array(char *str, char c);
char *my_strcat(char *dest, char *to_cat, int to_free);
char *my_strcpy(char const *src);
void pid_value_error(pid_t pid);
int tcheck_all_int(char *str);
char *my_scanf(void);
