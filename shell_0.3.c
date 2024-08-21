#include "shell.h"

/**
 * main - Run a terminal and get user command
 * @ac: parametter no taked in charge
 * @av:	parametter no taked in charge
 * @env: array of environment variables
 * Description: Run an infinite loop, take the string entered by the user
 * and then put it in functions who will execute the command if it is a
 * command enterred
 *
 * Return: 0 on exit succes or 1 on exit faillure
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)ac;
	(void)av;

	while (1)
	{
		/*check if mode non_interactive*/
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
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

		command_checker(line, env);
	}
	free(line);
	return (0);
}
