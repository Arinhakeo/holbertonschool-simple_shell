#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * free_arg_list - free a list of arguments
 * @arg_list: list to free
 * Return: nothing
 */
void free_arg_list(char **arg_list)
{
	int i;

	for (i = 0; arg_list[i]; i++)
	{
		free(arg_list[i]);
	}
	free(arg_list);
}

void execute_command(char *line, char **env)
{
	char *tokens[2];
	pid_t pid;
	int status;

	tokens[0] = line;
	tokens[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(tokens[0], tokens, env) == -1)
		{
			perror(tokens[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Run a terminal and get user command
 * Description: Run an infinite loop, take the string entered by the user,
 * and then put it in a function to determine if it is a command or not.
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
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			break;
			/*ctrl + D = succes*/
		}

		/* replace last character by 0*/
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
		{
			fprintf(stderr, "no command found\n");
			continue;
		}
		execute_command(line, env);
	}
	free(line);

	return (0);
}
