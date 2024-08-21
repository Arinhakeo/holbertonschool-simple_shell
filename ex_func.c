#include "shell.h"

/**
 * is_exit - exit the programme with succes or a error code
 * @tokens: list of arguments
 * @exit_parameter: exit value
 * @line: copy of stdin
 * Description : check if the value in the list of argument is exit,
 * if yes, convert the error code and take him has parametter of the exit
 * function
 */
void is_exit(char **tokens, int exit_parameter, char *line)
{
	if (tokens[0] == NULL)
		return;

	/*check if first argument is exit*/
	if (strlen(tokens[0]) == strlen("exit"))
	{
		if (strcmp(tokens[0], "exit") == 0)
		{
			/*check if second argument is numbers*/
			if (tokens[1] != NULL)
			{
				exit_parameter = _atoi(tokens[1]);

				if (exit_parameter != 0)
				{
					free(line);
					free_arg_list(tokens);
					exit(exit_parameter);
				}
			}
			else
			{
				free(line);
				free_arg_list(tokens);
				exit(EXIT_SUCCESS);
			}
		}
	}
}


/**
 * _atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted integer.
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int in_number = 0;


	/* Skip whitespace characters */
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
	|| *str == '\f' || *str == '\v')
	{
		str++;
	}

	/* Check for optional sign */
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}

	/* Convert characters to integer */
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		in_number = 1;
	}

	if (!in_number)
		return (0);	/* Return 0 if no digits were found */

	return (sign * result);
}
