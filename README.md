
# Mini Simple Shell

'A mini command interpreter, perfect for learning the basics of systems programming.'
## Implemented Features
-  The shell displays a prompt and waits for user input.
- Command Execution: Commands entered by the user are executed using the execve system call.
- Error Management: If a command does not exist, an error message is displayed.
- End of File (EOF) Handling: The shell handles EOF (Ctrl+D) to exit interactive mode.
- Argument Processing: Commands can now include arguments.
- PATH Management: The shell searches for executables in directories specified by the PATH environment variable.
- Built-in Commands: Implementation of built-in commands such as exit to quit the shell and env to display environment variables.
## Compilation

The shell is compiled with the following options:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
Ensure that all files end with a newline and that the coding style conforms to Betty.    
## Usage
### Interactive Mode

Launch the shell in interactive mode with:
```bash
  ./hsh
```
The prompt ($) will be displayed, and you can enter commands directly.

### Non-Interactive Mode
You can also execute commands in non-interactive mode using redirection:
~~~~bash
echo "/bin/ls" | ./hsh
~~~~
The shell will execute the ls command and display the results.


![Logo](http://www.image-heberg.fr/files/1724112230482249650.png)


With this mini shell, you can run several types of commands:

### System Commands:
- Full Path Executables: You can execute commands by specifying the full path, e.g., `/bin/ls`, `/usr/bin/env`.

- Commands Using PATH: You can execute commands without specifying the full path, e.g., `ls`, `grep`, `cat`, as long as the executable is located in one of the directories specified in the `PATH` environment variable.
### Commands with Arguments:
- Single Command with Arguments:You can execute commands with additional arguments, `e.g`., `ls -l /tmp`, `grep 'pattern' filename`.
## Built-in Commands:
- `exit`: Exits the shell.
- `env`: Displays the current environment variables.
- `cd` [directory]: Changes the current working directory.
- `setenv VARIABLE VALUE`: Sets or updates an environment variable.
- `unsetenv VARIABLE`: Removes an environment variable.
- `help`: Provides help on built-in commands.
### Control Commands:
- EOF (Ctrl+D): Exits the shell in interactive mode.
### Error Handling:
- If a command cannot be found, it displays an appropriate error message.
- This shell mimics basic functionalities found in typical Unix shells, allowing you to execute standard Unix commands and manage your environment.

## Concept Explanation

### Process Creation
The shell uses `fork` to create a new process. The child process executes the command using `execve`, while the parent process waits for the child to complete using `wait`.

### PATH Management
The shell uses the PATH environment variable to locate executables. When a command is entered, the `shell` searches for the executable file in the directories listed in `PATH`.

### System Calls
System calls like `execve`, `fork`, and `wait` are used to execute programs, create processes, and manage their execution.

### Future Development
Redirection and Pipes: Implement advanced features such as output redirection and piping.
Environment Variable Support: Manage environment variables and allow modification from the shell.

## Links and References

- [GNU GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [Linux man pages for fork](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Linux man pages for execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- [Linux man pages for waitpid](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/)

### Authors

Jonathan Blin < 9288@horlbertonstudents.com >
Arinhasvath Keophiphath < 9295@holbertonstudents.com >

## License
This project is licensed under the MIT License. See the LICENSE file for more information.
