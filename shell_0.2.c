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

/**
 * split_string - transform string on list of arguments
 * @line: the string to split
 * Description: count the numbers of delimiters (spaces), do an allocation
 * for a list of arguments (tokens) copy every arguments in it
 * Return: the list of arguments
 */
char **split_string(char *line)
{
	int i;
	char **tokens;
	char *token;
	int count = 0;

	for (i = 0; line[i]; i++)
	{
		if (line[i] == ' ')
			count++;
	}

	/* add 2 for counting the first argument and the '\0' char*/
	tokens = malloc((count + 2) * sizeof(char *));
	if (tokens == NULL)
	{
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	for (i = 0; token != NULL; i++)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free_arg_list(tokens);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	return (tokens);
}


/**
 * execute_command - execute command in a child process
 * @line: The command line to execute
 * Return: nothing
 */
void execute_command(char *line)
{
	char **tokens = split_string(line);
	pid_t pid;
	int status;
	int execve_check;

	if (tokens == NULL)
	{
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
		execve_check = execve(tokens[0], tokens, environ);

		if (execve_check == -1)
		{
			/*display ./shell: No such file or directory */
			perror("./shell");
			/*close child process in case of faillure*/
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
			free(line);
			exit(EXIT_SUCCESS);
			/*ctrl + D = succes*/
		}

		/* replace last character by 0*/
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		execute_command(line);
	}
	free(line);

	return (0);
}
