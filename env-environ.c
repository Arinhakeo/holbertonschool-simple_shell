#include "shell.h"

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