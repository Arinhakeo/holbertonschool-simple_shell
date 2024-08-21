#include "shell.h"

/**
 * is_env - if command env entered, print current env
 * @tokens: arguments list
 * @env: array of environment variables
 * Return: 1 if env enterred, 0 otherwise
 */
int is_env(char **tokens, char **env)
{
	unsigned int i = 0;

	/*check if size corespond*/
	if (strlen(tokens[i]) != 3)
		return (0);


	if (_strncmp(tokens[0], "env", 3) == 0 && !tokens[1])
	{
		i = 0;
		/*printf environement*/
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
		free_arg_list(tokens);
		return (1);
	}
	return (0);
}
