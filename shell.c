#include "shell.h"

/**
 * parse_line - Parses a line into an array of tokens
 *
 * @line: The line to be parsed
 *
 * Return: An array of tokens, or NULL on failure
 */

char **parse_line(char *line)
{
char *token;
char **tokens = malloc(64 * sizeof(char *));
int position = 0;

token = strtok(line, " \n");
while (token != NULL)
{
tokens[position] = token;
position++;
token = strtok(NULL, " \n");
}
tokens[position] = NULL;
return (tokens);
}

char *find_in_path(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");
char *full_path = malloc(1024);
struct stat st;

while (dir != NULL)
{
strcpy(full_path, dir);
strcat(full_path, "/");
strcat(full_path, command);

if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(path_copy);
return (full_path);
}
dir = strtok(NULL, ":");
}

free(path_copy);
free(full_path);
return (NULL);
}
