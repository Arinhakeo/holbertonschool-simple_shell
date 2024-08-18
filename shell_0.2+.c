#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * free_arg_list - Frees a list of arguments.
 * @arg_list: List to free.
 */
void free_arg_list(char **arg_list)
{
int i;
for (i = 0; arg_list[i] != NULL; i++)
{
free(arg_list[i]);
}
free(arg_list);
}

/**
 * split_string - Splits a string into a list of arguments.
 * @line: The string to split.
 * @tokens: The array to store the arguments.
 * @max_tokens: Maximum number of tokens that can be stored.
 * Return: The number of tokens.
 */
int split_string(char *line, char **tokens, int max_tokens)
{
int i = 0;
int j = 0;
int start = 0;

while (line[i] != '\0' && j < max_tokens - 1)
{
if (line[i] == ' ' || line[i] == '\t')
{
if (i > start)
{
tokens[j] = malloc(i - start + 1);
if (tokens[j] == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
memcpy(tokens[j], line + start, i - start);
tokens[j][i - start] = '\0';
j++;
}
start = i + 1;
}
i++;
}
if (i > start)
{
tokens[j] = malloc(i - start + 1);
if (tokens[j] == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
memcpy(tokens[j], line + start, i - start);
tokens[j][i - start] = '\0';
j++;
}
tokens[j] = NULL;
return j;
}

/**
 * find_command_path - Finds the full path of a command.
 * @command: The command to find.
 * Return: The full path of the command, or NULL if not found.
 */
char *find_command_path(char *command)
{
char *path_env = getenv("PATH");
char path_buffer[1024];
struct stat st;
char *path_start;
char *path_end;

if (!command)
return NULL;

if (command[0] == '/' || command[0] == '.')
{
if (stat(command, &st) == 0)
{
return strdup(command);
}
return NULL;
}

path_start = path_env;
while (path_start != NULL)
{
path_end = strchr(path_start, ':');
if (path_end != NULL)
{
*path_end = '\0';
path_end++;
}
snprintf(path_buffer, sizeof(path_buffer), "%s/%s", path_start, command);
if (stat(path_buffer, &st) == 0)
{
if (path_end != NULL)
{
*path_end = ':';
}
return strdup(path_buffer);
}
if (path_end == NULL)
{
break;
}
path_start = path_end;
}
return NULL;
}

/**
 * execute_command - Executes a command in a child process.
 * @line: The command line to execute.
 */
void execute_command(char *line)
{
char *tokens[64];
char *command_path;
pid_t pid;
int status;
int num_tokens;

num_tokens = split_string(line, tokens, 64);
if (num_tokens == 0 || tokens[0] == NULL)
{
return;
}

if (strcmp(tokens[0], "exit") == 0)
{
free_arg_list(tokens);
_exit(EXIT_SUCCESS);
}

command_path = find_command_path(tokens[0]);
if (command_path == NULL)
{
fprintf(stderr, "./shell: %s: Command not found\n", tokens[0]);
free_arg_list(tokens);
return;
}

pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
free_arg_list(tokens);
_exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execve(command_path, tokens, environ) == -1)
{
perror(command_path);
free(command_path);
free_arg_list(tokens);
_exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}

free(command_path);
free_arg_list(tokens);
}

/**
 * prompt - Displays the shell prompt.
 */
void prompt(void)
{
write(STDOUT_FILENO, ":) ", 3);
}

/**
 * main - Runs the shell and processes user commands.
 * Return: 0 on success.
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

while (1)
{
if (isatty(STDIN_FILENO))
{
prompt();
}

nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
_exit(EXIT_SUCCESS);
}

if (line[nread - 1] == '\n')
line[nread - 1] = '\0';

if (line[0] != '\0')
{
execute_command(line);
}
}

free(line);
return (0);
}
