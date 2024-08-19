#ifndef MAIN_H
#define MAIN_H


int command_checker(char *line);
char *find_command_path(const char *command);
void free_arg_list(char **arg_list);
void execute_command(char *full_path, char **argv);

/* create a list of arguments */
char **split_string(char *line);
/* free a list of argument */
void free_arg_list(char **arg_list);

#endif
