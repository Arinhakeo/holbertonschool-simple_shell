#include "shell.h"

/**
 * check_file_stat - Checks if a file exists and is executable
 *
 * @path: The path to the file
 *
 * Return: 1 if the file exists and is executable, 0 otherwise
 */

int check_file_stat(const char *path)
{
struct stat st;
if (stat(path, &st) == 0)
{
return (st.st_mode & S_IXUSR);
}
return (0);
}
