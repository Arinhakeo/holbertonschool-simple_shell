#include "shell.h"

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