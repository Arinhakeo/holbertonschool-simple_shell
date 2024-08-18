#include "shell.h"

/**
 * create_fork - Creates a new process using fork.
 * 
 * Return: The PID of the child process.
 */
pid_t create_fork(void)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork failed");
exit(EXIT_FAILURE);
}
return pid;
}
