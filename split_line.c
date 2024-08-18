#include "shell.h"

/**
 * split_line - Splits a line of input into an array of arguments
 * @line: The line of input
 *
 * Return: An array of strings (arguments), or NULL on failure
 */
char **split_line(char *line)
{
int bufsize = 64, position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens) {
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}

token = strtok(line, " \t\r\n\a");
while (token != NULL) {
tokens[position++] = token;

if (position >= bufsize) {
bufsize += 64;
tokens = realloc(tokens, bufsize * sizeof(char *));
if (!tokens) {
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, " \t\r\n\a");
}
tokens[position] = NULL;
return (tokens);
}
