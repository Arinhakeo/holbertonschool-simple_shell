#include "shell.h"

void execute_command(char **args)
{
pid_t pid = fork();
if (pid == 0)
{
if (args[0][0] != '/')
{
char *command_path = find_in_path(args[0]);
if (command_path != NULL)
{
if (execve(command_path, args, NULL) == -1)
{
perror("Error executing command");
}
free(command_path);
}
else
{
perror("Command not found");
}
}
else
{
if (execve(args[0], args, NULL) == -1)
{
perror("Error executing command");
}
}
exit(EXIT_FAILURE);
}
else if (pid > 0)
{
wait(NULL);
}
else
{
perror("fork failed");
}
}