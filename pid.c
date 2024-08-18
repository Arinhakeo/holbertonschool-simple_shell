#include "shell.h"

/**
 * print_pid - Prints the PID of the current process.
 */
void print_pid(void)
{
pid_t pid = getpid();
printf("Current PID: %d\n", pid);
}
