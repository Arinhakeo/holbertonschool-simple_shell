#include "shell.h"

/**
 * command_checker - check if there is a command enterred
 * @line: texte entered in terminal
 * Description: search in the PATH file if the texte enterred
 * is a command
 */
void command_checker(char *line, char **env)
{
	char *full_path;
	char **tokens = split_string(line);

	if (!tokens)
		return;

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
