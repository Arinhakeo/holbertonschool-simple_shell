#include "shell.h"

/**
 * execute_command - Executes a command.
 * @args: An array of strings representing the command and arguments.
 */
void execute_command(char **args)
{
if (check_file_stat(args[0]))
{
pid_t pid = create_fork();
if (pid == 0)
{
if (execve(args[0], args, NULL) == -1)
{
perror("./shell");
exit(EXIT_FAILURE);
}
}
else
{
wait_for_child(pid);
}
}
else
{
fprintf(stderr, "./shell: No such file or directory\n");
}
}
