#!/bin/bash

# Test for valid commands
echo "Testing valid commands"
echo "ls" | ./simple_shell
echo "/bin/ls" | ./simple_sshell
echo "echo 'Hello World'" | ./simple_shell

# Test for invalid commands
echo "Testing invalid commands"
echo "invalid_command" | ./simple_shell
echo "/bin/invalid_command" | ./simple_shell

# Test for EOF
echo "Testing EOF (Ctrl+D)"
echo "exit" | ./simple_shell

# Clean up or additional tests
echo "Performing cleanup or additional tests"