#include "shell.h"

/**
 * execute_command - Executes a given command
 *
 * @args: An array of arguments for the command
 *
 * Description: This function forks a child process, executes the command
 * using execve, and waits for the child process to finish.
 */

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
