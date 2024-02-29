#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int isExit(char *c);
char **split_string(char *delim, char *str);
void free_grid(char **grid);
void execute_command(char **argv);

#endif /* HEADER_H */
