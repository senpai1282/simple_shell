#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

extern char **environ;

void print_env(char **envp);
int _getline(char **line_ptr, size_t *n, FILE *stream);
char *_strtok(char *str, char *delim);
int countwords(char *str, char *d);
void free_fun(char **tmp, int i, char *tmp2);
char **spilt_string(char *delim, char *str);
void free_grid(char **grid);

char *make_path_arr(char **str);
char *compare_and_set_env(char **env, char **argv);

void execute_command(char *line, int run_in_background);
int execute_external_command(char **argv, char *filename);
int handle_builtin_commands(char **argv, char **env);

/* Declarations for new functions */
void handle_cd_command(char *directory);
void handle_pwd_command();

#endif /* HEADER_H */
