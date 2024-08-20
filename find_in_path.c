#include "shell.h"


/**
 * find_command_path - Finds the full path of a command using the PATH env var.
 * @command: The command to find.
 * @env: Array of environment variables.
 *
 * Return: The full path of the command if found and executable, NULL otherwise.
 */
char *find_command_path(const char *command, char **env)
{
	char *path = NULL;
	char *path_copy;
	char *dir;
	char full_path[1024];

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	for (; *env; ++env)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			break;
		}
	}

	if (path == NULL)
	{
		return NULL;
	}

	/* Copy the PATH variable for tokenization */
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		return NULL;
	}

	/* Tokenize PATH and check each directory */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return strdup(full_path); /* Return the full path of the command */
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL; /* Command not found */
}

/**
 * _strncmp - Compare les premiers n caractères de deux chaînes.
 * @s1: Première chaîne.
 * @s2: Deuxième chaîne.
 * @n: Nombre maximum de caractères à comparer.
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
        return 0;

    return ((unsigned char)*s1 - (unsigned char)*s2);
}
