#include "shell.h"

/**
 * prompt - Displays the shell prompt
 *
 * Return: void
 */
void prompt(void)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
