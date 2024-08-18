#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

/* Function Prototypes */
void prompt(void);
void execute(char **args, char *argv);
char *read_line(void);
char **split_line(char *line);

#endif /* SHELL_H */
