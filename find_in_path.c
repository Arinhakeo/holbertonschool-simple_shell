#include "shell.h"


/**
 * find_command_path - Finds the full path of a command using the PATH env var.
 * @command: The command to find.
 *
 * Return: The full path of the command if found and executable, NULL otherwise.
 */
char *find_command_path(const char *command)
{
	char *path_env_ptr, *path_copy;

	if (strchr(command, '/') != NULL)
	{
		if (is_executable(command))
			return (strdup(command));
		return (NULL);
	}

	path_env_ptr = read_env_path();
	if (path_env_ptr == NULL)
		return (NULL);

	path_copy = strdup(path_env_ptr);
	if (path_copy == NULL)
		return (NULL);

	return (check_command_in_path(path_copy, command));
}

/**
 * read_env_path - Reads the PATH environment variable from /proc/self/environ.
 *
 * Return: Pointer to the PATH string or NULL if not found or on error.
 */
char *read_env_path(void)
{
	static char path_env[PATH_ENV_SIZE];
	int fd;
	ssize_t bytes_read;
	char *env_ptr, *path_start;

	fd = open("/proc/self/environ", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return NULL;
	}

	bytes_read = read(fd, path_env, sizeof(path_env) - 1);
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		return NULL;
	}

	close(fd);
	path_env[bytes_read] = '\0';

	for (env_ptr = path_env; env_ptr < path_env + bytes_read; env_ptr += strlen(env_ptr) + 1)
	{
		if (strncmp(env_ptr, "PATH=", 5) == 0)
		{
			path_start = env_ptr + 5;
			return path_start;
		}
	}

	fprintf(stderr, "PATH not found\n");
	return NULL;
}
/**
 * check_command_in_path - Searches for a command in the given PATH directories.
 * @path_copy: A copy of the PATH variable to search through.
 * @command: The command to find.
 *
 * Return: The full path of the command if found and executable, NULL otherwise.
 */
char *check_command_in_path(char *path_copy, const char *command)
{
	char *token, *full_path;

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = build_full_path(token, command);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		if (is_executable(full_path))
		{
			free(path_copy);
			free(full_path);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * build_full_path - Constructs the full path for a command in a directory.
 * @token: The directory from PATH.
 * @command: The command to append to the directory.
 *
 * Return: A pointer to the newly allocated string containing the full path.
 */
char *build_full_path(char *token, const char *command)
{
	size_t len;
	char *full_path;

	len = strlen(token) + strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);

	sprintf(full_path, "%s/%s", token, command);
	return (full_path);
}

/**
 * is_executable - Checks if a file at the given path is executable.
 * @command: The path to the file.
 *
 * Return: 1 if executable, 0 otherwise.
 */
int is_executable(const char *command)
{
	return (access(command, X_OK) == 0);
}
