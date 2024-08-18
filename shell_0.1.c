#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * free_arg_list - free a list of arguments
 * @arg_list: list to free
 * Return: nothing
 */
void free_arg_list(char **arg_list)
{
	int i;

	for (i = 0; arg_list[i] != NULL; i++)
	{
		free(arg_list[i]);
	}
	free(arg_list);
}

char **split_string(char *line)
{
	char **tokens = malloc(2 * sizeof(char *));
	if (tokens == NULL)
	{
		exit(EXIT_FAILURE);
	}

	tokens[0] = strdup(line);
	if (tokens[0] == NULL)
	{
		free(tokens);
		exit(EXIT_FAILURE);
	}

	tokens[1] = NULL;
	return (tokens);
}

void execute_command(char *line)
{
	char **tokens = split_string(line);
	pid_t pid;
	int status;

	if (tokens == NULL || tokens[0] == NULL)
	{
		free_arg_list(tokens);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(tokens[0], tokens, environ) == -1)
		{
			perror(tokens[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	free_arg_list(tokens);
}

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
			printf("#cisfun$ ");
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
			/*ctrl + D = succes*/
		}

		/* replace last character by 0*/
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] != '\0')
			execute_command(line);

	}
	free(line);

	return (0);
}
