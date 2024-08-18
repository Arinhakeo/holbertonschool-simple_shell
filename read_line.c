#include "shell.h"

/**
 * read_line - Reads a line of input from stdin
 *
 * Return: The input line as a string
 */
char *read_line(void)
{
char *line = malloc(1024);
int i = 0;

if (!line)
exit(EXIT_FAILURE);

while (1)
{
int c = getchar();
if (c == EOF || c == '\n')
{
line[i] = '\0';
return (line);
}
line[i++] = c;
}
}
