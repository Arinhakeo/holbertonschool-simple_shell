#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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
char *path, *dup_path;
char path_buffer[1024];
struct stat st;

if (!command)
return (NULL);

if (command[0] == '/' || command[0] == '.')
{
if (stat(command, &st) == 0)
return (strdup(command));
return (NULL);
}

dup_path = strdup(path_env);
path = strtok(dup_path, ":");
while (path != NULL)
{
snprintf(path_buffer, sizeof(path_buffer), "%s/%s", path, command);
if (stat(path_buffer, &st) == 0)
{
free(dup_path);
return (strdup(path_buffer));
}
path = strtok(NULL, ":");
}
free(dup_path);
return (NULL);
}

/**
* execute_command - Executes a command in a child process.
* @tokens: The tokenized command line arguments.
*/
void execute_command(char **tokens)
{
char *command_path;
pid_t pid;
int status;

command_path = find_command_path(tokens[0]);
if (command_path == NULL)
{
fprintf(stderr, "./shell: %s: Command not found\n", tokens[0]);
return;
}

pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
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
}

/**
* main - Entry point of the shell program.
* Return: Always 0.
*/
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
char **tokens;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, ":) ", 3);

nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
exit(EXIT_SUCCESS);
}

if (line[nread - 1] == '\n')
line[nread - 1] = '\0';

tokens = split_string(line);
if (tokens[0] != NULL)
{
if (strcmp(tokens[0], "exit") == 0)
{
free_arg_list(tokens);
free(line);
exit(EXIT_SUCCESS);
}

execute_command(tokens);
}

free_arg_list(tokens);
}

free(line);
return (0);
}
