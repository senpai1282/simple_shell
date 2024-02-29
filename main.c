#define _GNU_SOURCE
#include "header.h"

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        display_prompt();

        read = getline(&line, &len, stdin);

        if (read != -1) {
            // Check if the command should run in the background
            int background = 0;
            if (line[read - 2] == '&') {
                background = 1;
                line[read - 2] = '\0';  // Remove the '&' from the command
            }

            execute_command(line, background);
        }
    }

    free(line);
    return 0;
}
