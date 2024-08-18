#include "shell.h"

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