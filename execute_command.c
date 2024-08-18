#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * execute_command - execute a command enterred find in path
 * @full_path:
 * @argv: 
 */
void execute_command(char *full_path, char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		free(full_path);
		return;
	}

	if (pid == 0)
	{
		execve(full_path, argv, NULL);
		perror("Error:");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}

	free(full_path);
}

