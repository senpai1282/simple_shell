#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for write

void ls() {
    struct dirent *entry;
    DIR *dir = opendir("."); // Open the current directory

    if (dir == NULL) {
        perror("No such file or directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        write(STDOUT_FILENO, entry->d_name, 13);
    }

    closedir(dir);
}

int main(){
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while(true){
        write(STDOUT_FILENO, "#cisfun$  ", 16);
        read = getline(&line, &len, stdin);
        if (read != -1) {
            switch (line)
            {
            case "ls":

            break;
            
            default:
                break;
            }    
        }
    free(line);
    }
    return 0;
}
