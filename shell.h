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

/*path*/
char *find_command_path(const char *command, char **env);

/*free*/
void free_arg_list(char **arg_list);

int _strncmp(const char *s1, const char *s2, size_t n);

#endif
