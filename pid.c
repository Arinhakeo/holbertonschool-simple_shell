#include "shell.h"

void print_pid(void)
{
pid_t pid = getpid();
printf("Current PID: %d\n", pid);
}