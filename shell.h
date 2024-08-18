#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
 * parse_line - Parses a line into an array of tokens
 * @line: The line to be parsed
 * Return: An array of tokens
 */
char **parse_line(char *line);

/**
 * find_in_path - Finds a command in the PATH environment variable
 * @command: The command to find
 * Return: The full path to the command, or NULL if not found
 */
char *find_in_path(char *command);

/**
 * execute_command - Executes a command
 * @args: An array of arguments
 * Return: Void
 */
void execute_command(char **args);

/**
 * create_fork - Creates a child process
 * Return: The PID of the child process
 */
pid_t create_fork(void);

/**
 * wait_for_child - Waits for a child process to terminate
 * @pid: The PID of the child process
 * Return: Void
 */
void wait_for_child(pid_t pid);

/**
 * display_prompt - Displays the shell prompt
 * Return: Void
 */
void display_prompt(void);

/**
 * print_pid - Prints the current process ID
 * Return: Void
 */
void print_pid(void);

/**
 * print_ppid - Prints the parent process ID
 * Return: Void
 */
void print_ppid(void);

/**
 * print_env - Prints the environment variables
 * Return: Void
 */
void print_env(void);

/**
 * check_file_stat - Checks the file status
 * @path: The path to the file
 * Return: 1 if successful, 0 otherwise
 */
int check_file_stat(const char *path);

#endif /* SHELL_H */
