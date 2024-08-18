#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * execute_command - Executes a command.
 * @args: An array of strings representing the command and arguments.
 */
void execute_command(char **args);

/**
 * parse_line - Splits a line into an array of arguments.
 * @line: The input line to parse.
 * 
 * Return: An array of strings containing the arguments.
 */
char **parse_line(char *line);

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void);

/**
 * create_fork - Creates a new process using fork.
 * 
 * Return: The PID of the child process.
 */
pid_t create_fork(void);

/**
 * wait_for_child - Waits for a child process to finish.
 * @pid: The PID of the child process to wait for.
 */
void wait_for_child(pid_t pid);

/**
 * print_pid - Prints the PID of the current process.
 */
void print_pid(void);

/**
 * print_ppid - Prints the PPID of the current process.
 */
void print_ppid(void);

/**
 * check_file_stat - Checks if a file exists and is executable.
 * @path: The path to the file.
 * 
 * Return: 1 if the file is executable, 0 otherwise.
 */
int check_file_stat(const char *path);

#endif
