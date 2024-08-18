#include "shell.h"

/**
 * execute - Executes a command by forking a child process
 * @args: Array of strings representing the command and arguments
 * @argv: The name of the shell program
 *
 * Return: void
 */
void execute(char **args, char *argv)
{
pid_t pid;

if (strcmp(args[0], "exit") == 0)
{
exit(0);
}

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror(argv);
}
exit(EXIT_FAILURE);
}
else
{
wait(NULL); /* Wait for the child process to finish */
}
}
