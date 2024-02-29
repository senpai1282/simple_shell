#include "main.h"

void ls() {
    struct dirent *entry;
    DIR *dir = opendir("."); // Open the current directory

    if (dir == NULL) {
        perror("No such file or directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
    }

    closedir(dir);
}

void echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if (i < argc - 1) {
            // Write a space between arguments
            write(STDOUT_FILENO, " ", 1);
        }
    }
    // Write a newline at the end
    write(STDOUT_FILENO, "\n", 1);
}

int main(int ac, char **arg, char **envp) {
    char *en = NULL;
    char **env = NULL;
    int count = 0;

    (void)ac;
    en = make_path_arr(envp);

    env = split_string(":", en);

    if (isatty(STDIN_FILENO))
        display_prompt(env, envp, arg, count);
    else
        non_interactive_mode(env, arg, envp, count);

    return (0);
}
#include "main.h"

void ls() {
    struct dirent *entry;
    DIR *dir = opendir("."); // Open the current directory

    if (dir == NULL) {
        perror("No such file or directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
    }

    closedir(dir);
}

void echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if (i < argc - 1) {
            // Write a space between arguments
            write(STDOUT_FILENO, " ", 1);
        }
    }
    // Write a newline at the end
    write(STDOUT_FILENO, "\n", 1);
}

int main(int ac, char **arg, char **envp) {
    char *en = NULL;
    char **env = NULL;
    int count = 0;

    (void)ac;
    en = make_path_arr(envp);

    env = split_string(":", en);

    if (isatty(STDIN_FILENO))
        display_prompt(env, envp, arg, count);
    else
        non_interactive_mode(env, arg, envp, count);

    return (0);
}