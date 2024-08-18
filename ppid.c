#include "shell.h"

/**
 * print_ppid - Prints the PPID of the current process.
 */
void print_ppid(void)
{
pid_t ppid = getppid();
printf("Parent PID: %d\n", ppid);
}
