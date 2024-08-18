#include "shell.h"

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
extern char **environ;
char **env = environ;

while (*env)
{
printf("%s\n", *env);
env++;
}
}
