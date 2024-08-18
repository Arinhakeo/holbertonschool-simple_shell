#include "shell.h"

/**
 * print_pid - Prints the current process ID
 *
 * Description: This function gets the process ID using getpid()
 * and prints it to the standard output.
 */

void print_pid(void)
{
pid_t pid = getpid();
printf("Current PID: %d\n", pid);
}
