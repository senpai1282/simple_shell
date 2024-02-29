#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

void ls(void)
{
	struct dirent *entry;
	DIR *dir = opendir("."); /* Open the current directory */

	if (dir == NULL)
	{
	perror("No such file or directory");
	exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
	write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
	write(STDOUT_FILENO, " ", 1);
	}

	write(STDOUT_FILENO, "\n", 1);

	closedir(dir);
}

void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
	/* Child process */
	execlp(command, command, (char *)NULL);
	perror("Error");
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
	perror("Fork failed");
	exit(EXIT_FAILURE);
	}
	else
	{
	    /* Parent process */
	waitpid(pid, &status, 0);
	}
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
	write(STDOUT_FILENO, "#cisfun$  ", 16);
	read = getline(&line, &len, stdin);

	if (read != -1)
	{
		/* Remove newline character */
		line[strcspn(line, "\n")] = 0;

	if (strcmp(line, "ls") == 0)
	{
		ls();
			}
			else if (strcmp(line, "exit") == 0)
			{
			free(line);
			exit(EXIT_SUCCESS);
			}
			else
			{
			execute_command(line);
			}
		}
	}
	free(line);
	return (0);
}

