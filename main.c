#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
{
char *line;
char **args;

(void)argc;

while (1)
{
prompt();
line = read_line();
args = split_line(line);
if (args[0])
execute(args, argv[0]);
free(line);
free(args);
}
return (0);
}
