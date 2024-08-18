#ifndef SHELL_H
#define SHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

char **parse_line(char *line);
char *find_in_path(char *command);
void execute_command(char **args);
pid_t create_fork(void);
void wait_for_child(pid_t pid);
void display_prompt(void);
void print_pid(void);
void print_ppid(void);
void print_env(void);
int check_file_stat(const char *path);

#endif