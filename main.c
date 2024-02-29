#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command, int run_in_background) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Execute the command

        // Example using execlp:
        execlp(command, command, NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        if (!run_in_background) {
            // Wait for the child to complete if not a background command
            wait(NULL);
        } else {
            // If it's a background command, don't wait
            printf("[%d] %s\n", pid, command);
        }
    }
}

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("#cisfun$ ");
        read = getline(&line, &len, stdin);

        if (read != -1) {
            // Check if the command runs in the background
            int run_in_background = 0;
            if (line[read - 2] == '&') {
                run_in_background = 1;
                // Remove the '&' from the command
                line[read - 2] = '\0';
            }

            // Execute the command
            execute_command(line, run_in_background);
        }
    }

    free(line);
    return 0;
}
