#include "shell.h"

/**
* print_env - Prints all environment variables
*
* Return: void
*/
void print_env(void)
{
char **env;

env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
}
