#include "shell.h"

int check_file_stat(const char *path)
{
struct stat st;
if (stat(path, &st) == 0)
{
return (st.st_mode & S_IXUSR);
}
return 0;
}