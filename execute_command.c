#include "shell.h"

/**
 * execute_command - execute command in a child process
 * @full_path: take an absolute path of a function or NULL
 * @tokens: arguments list
 * @env : actual environement
 * Return: nothing
 */
void execute_command(char *full_path, char **tokens, char **env)
{
	pid_t pid;
	int status;
	int execve_check;

	if (!tokens)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*child process*/
		execve_check = execve(full_path, tokens, env);
		if (execve_check == -1)
		{
			/*print error on first argument*/
			perror(tokens[0]);
			/*close child process in case of faillure*/
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	free(full_path);
	free_arg_list(tokens);
}
