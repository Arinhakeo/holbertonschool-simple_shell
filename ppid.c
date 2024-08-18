#include "shell.h"

void print_ppid(void)
{
pid_t ppid = getppid();
printf("Parent PID: %d\n", ppid);
}