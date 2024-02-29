#include "header.h"
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * split_string - Splits a string into tokens
 * @delim: Pointer to the string containing the delimiter characters.
 * @str: Pointer to the input string to be split.
 * Return: An array of strings representing tokens.
 */
char **split_string(char *delim, char *str) {
    int i = 0;
    char *tmp2 = NULL;
    char **tmp = NULL;
    char *tokn = NULL;
    int token_len = 0;

    if (str == NULL)
        return NULL;

    tmp2 = strdup(str);
    if (tmp2 == NULL)
        return NULL;

    tmp = malloc(sizeof(char *) * 10); // Adjust the size as needed
    if (tmp == NULL) {
        free(tmp2);
        return NULL;
    }

    tokn = strtok(tmp2, delim);
    while (tokn != NULL && i < 10) {
        if (tokn != NULL)
            token_len = strlen(tokn);

        tmp[i] = malloc(sizeof(char) * (token_len + 1));
        if (tmp[i] == NULL) {
            free_grid(tmp);
            free(tmp2);
            return NULL;
        }

        strcpy(tmp[i], tokn);
        tmp[i][token_len] = '\0';
        i++;
        tokn = strtok(NULL, delim);
    }

    free(tmp2);
    tmp[i] = NULL;
    return tmp;
}

/**
 * free_grid - Frees the memory allocated
 * for a 2D array of strings.
 * @grid: Pointer to the 2D array of strings.
 */
void free_grid(char **grid) {
    int count = 0;

    while (grid[count] != NULL) {
        free(grid[count]);
        count++;
    }
    free(grid);
}

/**
 * execute_command - Executes a given command
 * @argv: Pointer to the array of command-line arguments.
 */
void execute_command(char **argv) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        wait(NULL);
    }
}