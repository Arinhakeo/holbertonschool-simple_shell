#include "shell.h"

void wait_for_child(pid_t pid)
{
int status;
waitpid(pid, &status, 0);
}