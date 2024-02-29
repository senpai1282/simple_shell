#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

/**
 * Executes an external command.
 * @param argv An array of strings representing the command and its arguments.
 * @param filename The name of the executable file.
 * @return Returns the exit status of the command.
 */
int execute_external_command(char **argv, char *filename) {
    pid_t pid = fork();
    int status;

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execvp(filename, argv);

        // If execvp fails
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}
/**
 * Handles the "cd" command.
 * @param directory The directory to change to.
 */
int handle_builtin_commands(char **argv) {
    if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            handle_cd_command(argv[1]);
        }
        return 1;  // Indicate that a built-in command was handled
    } else if (strcmp(argv[0], "pwd") == 0) {
        handle_pwd_command();
        return 1;  // Indicate that a built-in command was handled
    }

    return 0;  // Return 0 if no built-in command was handled
}
/**
 * Splits a string into an array of strings based on a delimiter.
 * @param delimiter The delimiter to split the string.
 * @param line The string to split.
 * @return An array of strings.
 */
char **split_string(const char *delimiter, const char *line) {
    char *copy = strdup(line);
    char **tokens = malloc(sizeof(char *) * 64);  // Assuming a maximum of 64 tokens

    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token = strtok(copy, delimiter);

    while (token != NULL) {
        tokens[i++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    tokens[i] = NULL;  // Null-terminate the array
    free(copy);

    return tokens;
}

/**
 * Frees the memory allocated for an array of strings.
 * @param tokens The array of strings.
 */
void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

/**
 * Executes a command in the background.
 * @param line The command line.
 */
void execute_command(char *line, int run_in_background) {
    // Parse the command
    char **argv = split_string(" ", line);

    if (argv == NULL || argv[0] == NULL) {
        // Handle empty command or parsing failure
        fprintf(stderr, "Error: Empty command or parsing failure\n");
        return;
    }

    // Check if the command is a builtin command
    if (handle_builtin_commands(argv)) {
        // Builtin command handled successfully
        free_tokens(argv);  // Free memory
        return;
    }

    // Not a builtin command, execute it
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        int status = execute_external_command(argv, NULL);

        // Handle status if needed

        free_tokens(argv);  // Free memory
        exit(status);
    } else {
        // Parent process
        if (!run_in_background) {
            // If not a background command, wait for the child process to finish
            int status;
            waitpid(pid, &status, 0);

            // Handle status if needed
        } else {
            // If it's a background command, print its process ID
            printf("[%d] %s\n", pid, line);
        }
    }

    free_tokens(argv); // Free memory
}
