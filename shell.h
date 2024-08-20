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
char *find_command_path(const char *command);
char *read_env_path(void);
char *check_command_in_path(char *path_copy, const char *command);
char *build_full_path(char *token, const char *command);
int is_executable(const char *command);

/*free*/
void free_arg_list(char **arg_list);

#endif
