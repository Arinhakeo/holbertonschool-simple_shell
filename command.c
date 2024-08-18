#include "shell.h"

/**
 * prompt - Display the shell prompt.
 */
void prompt(void)
{
write(STDOUT_FILENO, "$ ", 2);
}

/**
 * parse_command - Parse the command into an array of arguments.
 * @command: The command string.
 * Return: An array of argument strings.
 */
char **parse_command(char *command)
{
char **args = malloc(64 * sizeof(char *));
char *arg;
int i = 0;

arg = strtok(command, " ");
while (arg != NULL)
{
args[i] = arg;
i++;
arg = strtok(NULL, " ");
}
args[i] = NULL;
return (args);
}

/**
 * execute_command - Execute a command.
 * @command: Command to execute.
 */
void execute_command(char *command)
{
pid_t pid = fork();
char **args;

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
args = parse_command(command);
execvp(args[0], args);
perror(command);
free(args);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}

/**
 * handle_exit - Handle the exit command.
 */
void handle_exit(void)
{
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_SUCCESS);
}

