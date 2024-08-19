#include <stdlib.h>

/**
 * free_arg_list - free a list of arguments
 * @arg_list: list to free
 * Return: nothing
 */
void free_arg_list(char **arg_list)
{
	int i;

	for (i = 0; arg_list[i]; i++)
	{
		free(arg_list[i]);
	}
	free(arg_list);
}
