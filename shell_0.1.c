#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * execute_command - execute command in a child process
 * @line: The command line to execute
 * Return: nothing
 */
void execute_command(char *line)
{
	char *tokens[2];
	pid_t pid;
	int status;
	int execve_check;

	/* create an argument list with only one argument */
	tokens[0] = line;
	tokens[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
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
