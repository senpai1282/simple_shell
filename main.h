#ifndef START_H
#define START_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int isExit(char *c);
int countwords(char *str, char *delim);
char **split_string(char *delim, char *str);
char *make_path_arr(char **str);
int check_the_slash(char *str);
char *compare_and_set_env(char **env, char **argv);
void free_grid(char **grid);
int execute_command(char **argv, char *str, char *filename);
void print_env(char **envp);
void display_dollar_sign(void);
void display_prompt(char **env, char **envp, char **arg, int count);
void non_interactive_mode(char **env, char **arg, char **envp, int count);
void check_if_true(char *pathname, char **argv, int count, char *filename);
int _getline(char **line_ptr, size_t *n, FILE *stream);
char *_strtok(char *str, char *delim);
int check_the_spaces(char *buff);
void free_function(char **tmp, int i, char *tmp2);
void check_state(int is_complete, char **argv, int cnt, char *file, char **env);

#endif /* START_H */
