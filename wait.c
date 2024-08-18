#include "shell.h"

/**
 * wait_for_child - Waits for a child process to finish.
 * @pid: The PID of the child process to wait for.
 */
void wait_for_child(pid_t pid)
{
int status;
waitpid(pid, &status, 0);
}
