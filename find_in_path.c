#include "shell.h"


/**
 * find_command_path - Finds the full path of a command using the PATH env var
 * @command: The command to find
 * @env: array of environment variables
 *
 * Return: The full path of the command if found and executable or NULL if not
 */
char *find_command_path(const char *command, char **env)
{
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];

	/*search for an absolute path*/
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv(env);
	if (path == NULL)
		return (NULL);

	/* Copy the PATH variable for tokenization */
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	/* Tokenize PATH and check each directory */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/*copy command at the end of the absolute path*/
		if (strlen(dir) + strlen(command) + 2 < sizeof(full_path))
			sprintf(full_path, "%s/%s", dir, command);
		/*search if it is executable*/
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
			/* Return the full path of the command */
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL); /* Command not found */
}

/**
 * _strncmp - compare two string
 * @s1: first string
 * @s2: second string.
 * @n: maximum numbers of characters to compare
 *
 * Return: < 0 si s1 < s2, 0 si s1 == s2, > 0 si s1 > s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
		return (0);

	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * _getenv - copy get path environment function
 * @env: array of environment variables
 * Description : iterates the environement arg list until find a
 * PATH argument, return copy of pointer on this argument
 * Return: the pointer on PATH
 */
char *_getenv(char **env)
	{
		int i;
		char *path = NULL;

		/*copy path in path variable*/
		for (i = 0; env[i]; ++env)
		{
			if (_strncmp(env[i], "PATH=", 5) == 0)
			{
				path = (env[i] + 5);
				break;
			}
		}
		return (path);
	}
