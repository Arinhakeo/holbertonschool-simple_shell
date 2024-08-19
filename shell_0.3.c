#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Run a terminal and get user command
 * Description: Run an infinite loop, take the string entered by the user,
 * and then put it in a function to determine if it is a command or not.
 *
 * Return: 0 on exit succes or 1 on exit faillure
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf(":) ");
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
			/*ctrl + D = succes*/
		}

		/* replace last character by 0*/
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		command_checker(line);
	}
	free(line);

	return (0);
}
