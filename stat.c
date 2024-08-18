#include "shell.h"

/**
 * check_file_stat - Checks if a file exists and is executable.
 * @path: The path to the file.
 * Return: 1 if the file is executable, 0 otherwise.
 */
int check_file_stat(const char *path)
{
struct stat st;
return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR));
}
