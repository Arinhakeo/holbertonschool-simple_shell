#include "shell.h"

/**
 * parse_line - Splits a line into an array of arguments.
 * @line: The input line to parse.
 * 
 * Return: An array of strings containing the arguments.
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
return tokens;
}
