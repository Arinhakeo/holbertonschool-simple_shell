#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *find_command_path(const char *command)
{
	char *path_env = getenv("PATH");
	char *path_copy, *token;
	size_t len;
	char *full_path;


	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			return strdup(command);
		}
		return NULL;
	}

	if (path_env == NULL)
	{
		printf("PATH not defined\n");
		return NULL;
	}

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return NULL;

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		len = strlen(token) + strlen(command) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return NULL;
		}
		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
