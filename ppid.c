#include "shell.h"

/**
 * print_ppid - Prints the parent process ID
 *
 * Description: This function gets the parent process ID using getppid()
 * and prints it to the standard output.
 */

void print_ppid(void)
{
pid_t ppid = getppid();
printf("Parent PID: %d\n", ppid);
}
