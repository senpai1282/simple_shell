#include "main.h"

void display_dollar_sign(void) {
    char *prompt = "$ ";
    write(STDOUT_FILENO, prompt, 2);
    fflush(stdout);
}

void check_state(int is_complete, char **argv, int cnt, char *file, char **env) {
    char *pathname = NULL;

    is_complete = check_the_slash(argv[0]);
    if (!is_complete) {
        pathname = compare_and_set_env(env, argv);
        check_if_true(pathname, argv, cnt, file);
        free(pathname);
    } else {
        check_if_true(argv[0], argv, cnt, file);
    }
    free_grid(argv);
}

void display_prompt(char **env, char **envp, char **arg, int count) {
    char *filename = arg[0];
    char *buff = NULL;
    size_t t = 0;
    size_t n = 10000;
    int is_complete = 0;
    char **argv = NULL;

    while (isatty(STDIN_FILENO)) {
        count++;
        display_dollar_sign();
        t = _getline(&buff, &n, stdin);
        if (strcmp(buff, "\n") == 0 || check_the_spaces(buff) == 0) {
            free(buff);
            continue;
        } else if ((int)t == -1 || isExit(buff) == 1) {
            free_grid(env);
            free(buff);
            exit(0);
        } else if ((t > 0) && (buff[t - 1] == '\n'))
            buff[t - 1] = '\0';
        if (strcmp(buff, "env") == 0) {
            print_env(envp);
            free(buff);
            continue;
        }
        argv = split_string(" ", buff);
        if (argv == NULL) {
            perror
