#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define PATH_ENV_SIZE 4096

void command_checker(char *line, char **env);
char **split_string(char *line);
void execute_command(char *full_path, char **tokens, char **env);

/*path finder*/
char *find_command_path(const char *command, char **env);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(char **env);

/*free*/
void free_arg_list(char **arg_list);

/*env function*/
int is_env(char **tokens, char **env);

/*exit function*/
void is_exit(char **tokens, int exit_parameter, char *line);
int _atoi(const char *str);



#endif
