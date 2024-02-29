#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void change_directory(char *arguments[]) {
    if (arguments[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else {
        if (chdir(arguments[1]) != 0) {
            perror("cd");
        }
    }
}

void print_current_directory(char *arguments[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void ls_command(char *arguments[]) {
    // Implementation of ls command
    // ...
}

void echo_command(char *arguments[]) {
    for (int i = 1; arguments[i] != NULL; i++) {
        write(STDOUT_FILENO, arguments[i], strlen(arguments[i]));
        if (arguments[i + 1] != NULL) {
            // Write a space between arguments
            write(STDOUT_FILENO, " ", 1);
        }
    }
    // Write a newline at the end
    write(STDOUT_FILENO, "\n", 1);
}

// Function to execute a command with input/output redirection and piping
void execute_command(char *command, char *arguments[]) {
    int pid, status;
    int input_fd, output_fd;

    // Check for input/output redirection
    for (int i = 0; arguments[i] != NULL; i++) {
        if (strcmp(arguments[i], "<") == 0) {
            input_fd = open(arguments[i + 1], O_RDONLY);
            if (input_fd == -1) {
                perror("open");
                return;
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
            arguments[i] = NULL; // Remove '<' and the input file from arguments
        } else if (strcmp(arguments[i], ">") == 0) {
            output_fd = open(arguments[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (output_fd == -1) {
                perror("open");
                return;
            }
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
            arguments[i] = NULL; // Remove '>' and the output file from arguments
        }
    }

    // Check for piping
    for (int i = 0; arguments[i] != NULL; i++) {
        if (strcmp(arguments[i], "|") == 0) {
            char **second_command = &arguments[i + 1];
            arguments[i] = NULL; // Terminate the first command

            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe");
                return;
            }

            pid = fork();
            if (pid == -1) {
                perror("fork");
                return;
            }

            if (pid == 0) {
                // Child process: set up output redirection
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                execvp(command, arguments);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else {
                // Parent process: set up input redirection for the next command
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                execvp(second_command[0], second_command);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    // No piping, execute the command
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Child process
        execvp(command, arguments);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
}
