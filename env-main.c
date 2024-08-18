#include "shell.h"

/**
* main - Entry point of the shell program
*
* Description: This function is the main entry point of the shell program.
* It reads user input, parses it into arguments, and executes commands.
*
* Return: Always 0 on success.
*/

int main(void)
{
char *line = NULL;
size_t len = 0;
char **args;

while (1)
{
printf("$ ");
if (getline(&line, &len, stdin) == -1)
{
perror("getline failed");
free(line);
exit(EXIT_FAILURE);
}

args = parse_line(line);

if (args[0] != NULL)
{
execute_command(args);
}

free(args);
}

free(line);
return 0;
}