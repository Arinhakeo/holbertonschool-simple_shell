fndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void prompt(void);
void execute_command(char *command);
void handle_exit(void);
char **parse_command(char *command);

#endif

