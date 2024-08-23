#include "shell.h"

/**
 * command_checker - check if there is a command enterred
 * @line: copy of stdin
 * @env: array of environment variables
 * Description: search in the PATH file if the texte enterred
 * is a command
 * Return: nothing
 */
void command_checker(char *line, char **env)
{
	char *full_path;
	char **tokens;
	char *line_copy = line;
	int is_builtin_func = 0;

	/*handle string with only spaces*/
	while (*line_copy == ' ')
		line_copy++;

	if (*line_copy)
	{
		while (*line == ' ')
			line++;
	}
	else
	{
		perror("no command found");
		return;
	}

	tokens = split_string(line);
	if (!tokens)
		return;

	is_exit(tokens, 0, line);
	is_builtin_func = is_env(tokens, env);

	if (is_builtin_func == 0)
	{
		/*check if there is a command*/
		full_path = find_command_path(tokens[0], env);
		if (full_path == NULL)
		{
			/* command not found*/
			fprintf(stderr, "%s: command not found\n", tokens[0]);
			free_arg_list(tokens);
			return;
		}
		execute_command(full_path, tokens, env);
	}
}


/**
 * split_string - transform string on list of arguments
 * @line: the string to split
 * Description: count the numbers of delimiters (spaces), do an allocation
 * for a list of arguments (tokens) copy every arguments in it
 * Return: the list of arguments
 */
char **split_string(char *line)
{
	int i;
	char **tokens;
	char *token;
	int count = 0;

	/*count number of spaces*/
	for (i = 0; line[i]; i++)
	{
		if (line[i] == ' ')
			count++;
	}

	/* add 2 for counting the first argument and the '\0' char*/
	tokens = malloc((count + 2) * sizeof(char *));
	if (tokens == NULL)
	{
		exit(EXIT_FAILURE);
	}

	/*change line in argument list*/
	token = strtok(line, " ");
	for (i = 0; token != NULL; i++)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free_arg_list(tokens);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	return (tokens);
}
