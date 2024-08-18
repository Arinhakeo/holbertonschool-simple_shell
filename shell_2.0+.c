#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

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
 * Return: The list of arguments.
 */
char **split_string(char *line)
{
int i, count = 0;
char **tokens;
char *token;

if (!line)
return (NULL);

for (i = 0; line[i]; i++)
{
if (line[i] == ' ')
count++;
}

tokens = malloc((count + 2) * sizeof(char *));
if (tokens == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(line, " ");
for (i = 0; token != NULL; i++)
{
tokens[i] = strdup(token);
if (tokens[i] == NULL)
{
perror("strdup");
free_arg_list(tokens);
exit(EXIT_FAILURE);
}
token = strtok(NULL, " ");
}
tokens[i] = NULL;
return (tokens);
}

/**
 * find_command_path - Finds the full path of a command.
 * @command: The command to find.
 * Return: The full path of the command, or NULL if not found.
 */
char *find_command_path(char *command)
{
char *path_env = getenv("PATH");
char *path;
char path_buffer[1024];
struct stat st;

if (!command)
return (NULL);

if (command[0] == '/' || command[0] == '.')
{
if (stat(command, &st) == 0)
{
return (strdup(command));
}
return (NULL);
}

path_env = strdup(path_env);
path = strtok(path_env, ":");
while (path != NULL)
{
snprintf(path_buffer, sizeof(path_buffer), "%s/%s", path, command);
if (stat(path_buffer, &st) == 0)
{
free(path_env);
return (strdup(path_buffer));
}
path = strtok(NULL, ":");
}
free(path_env);
return (NULL);
}

/**
 * execute_command - Executes a command in a child process.
 * @line: The command line to execute.
 */
void execute_command(char *line)
{
char **tokens = split_string(line);
char *command_path;
pid_t pid;
int status;

if (tokens == NULL || tokens[0] == NULL)
{
free_arg_list(tokens);
return;
}

if (strcmp(tokens[0], "exit") == 0)
{
free_arg_list(tokens);
exit(EXIT_SUCCESS);
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
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execve(command_path, tokens, environ) == -1)
{
perror(command_path);
free(command_path);
free_arg_list(tokens);
exit(EXIT_FAILURE);
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
 * Description: Runs an infinite loop, reads user input,
 * and executes the corresponding command.
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
exit(EXIT_SUCCESS);
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
