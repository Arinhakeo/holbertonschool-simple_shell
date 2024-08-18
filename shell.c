#include "shell.h"

/**
 * main - Simple shell main function.
 * Return: Always 0.
 */
int main(void)
{
char c;
char command[1024];
int i = 0;

while (1)
{
prompt();
while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n')
{
if (i < 1023)
{
command[i++] = c;
}
}
command[i] = '\0';
if (i == 0)
{
i = 0;
continue;
}
if (command[0] == 'e' && command[1] == 'x' && command[2] == 'i'
&& command[3] == 't' && (command[4] == '\0' || command[4] == ' '))
{
handle_exit();
}
else
{
execute_command(command);
}
i = 0;
}
return (0);
}

