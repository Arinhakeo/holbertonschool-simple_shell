#include "shell.h"

/**
 * create_fork - Creates a child process
 *
 * Return: The PID of the child process on success,
 *         -1 on failure.
 */

pid_t create_fork(void)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork failed");
exit(EXIT_FAILURE);
}
return (pid);
}
