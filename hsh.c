#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

char **parse_line(char *line)
{
char *token;
char **tokens = malloc(64 * sizeof(char *));
int position = 0;

token = strtok(line, " \n");
while(token != NULL)
{
tokens[position] = token;
position++;
token = strtok(NULL, " \n");
}
tokens[position] = NULL;
return tokens;
}

char *find_in_path(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");
char *full_path = malloc(1024);
struct stat st;

while(dir != NULL)
{
strcpy(full_path, dir);
strcat(full_path, "/");
strcat(full_path, command);

if(stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(path_copy);
return full_path;
}
dir = strtok(NULL, ":");
}

free(path_copy);
free(full_path);
return NULL;
}

void execute_command(char **args)
{
pid_t pid = fork();
if(pid == 0)
{
if(args[0][0] != '/')
{
char *command_path = find_in_path(args[0]);
if(command_path != NULL)
{
execve(command_path, args, NULL);
free(command_path);
}
else
{
perror("Command not found");
}
}
else
{
execve(args[0], args, NULL);
}
perror("execve failed");
exit(EXIT_FAILURE);
}
else if(pid > 0)
{
wait(NULL);
}
else
{
perror("fork failed");
}
}

int main(void)
{
char *line = NULL;
size_t len = 0;
char **args;

while(1)
{
printf("$ ");
if(getline(&line, &len, stdin) == -1)
{
perror("getline failed");
free(line);
exit(EXIT_FAILURE);
}

args = parse_line(line);

if(args[0] != NULL)
{
execute_command(args);
}

free(args);
}

free(line);
return 0;
}