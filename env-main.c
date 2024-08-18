#include "shell.h"

/**
 * main - Entry point of the shell.
 * Return: 0 on success.
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
char **args;

while (1)
{
display_prompt();
if (getline(&line, &len, stdin) == -1)
{
if (feof(stdin))
{
free(line);
exit(EXIT_SUCCESS);
}
else
{
perror("getline failed");
free(line);
exit(EXIT_FAILURE);
}
}

args = parse_line(line);

if (args[0] != NULL)
{
execute_command(args);
}

free(args);
}

free(line);
return (0);
}
