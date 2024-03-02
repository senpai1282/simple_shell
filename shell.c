#define _GNU_SOURCE
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

/**
 * ls : Lists files and directories in the current directory.
 */
void ls(void)
{
	struct dirent *entry;
	DIR *dir = opendir(".");

	if (dir == NULL)
	{
	perror("opendir");
	exit(EXIT_FAILURE);
	}
	while ((entry = readdir(dir)) != NULL)
	{
	write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
	write(STDOUT_FILENO, "\n", 1);
	}

	closedir(dir);
}

/**
 * echo : Prints the given arguments to the standard output.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 */
void echo(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; i++)
	{
		write(STDOUT_FILENO, argv[i], strlen(argv[i]));
		if (i < argc - 1)
		{
			write(STDOUT_FILENO, " ", 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * Main : function to read user input and execute corresponding commands.
 * @return 0 on successful execution.
 */
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
		line[strcspn(line, "\n")] = '\0';

			if (strcmp(line, "ls") == 0)
			{
				ls();
			}
			else if (strcmp(line, "echo") == 0)
			{
				echo(line);

				char *token = strtok(line, " ");
				int argc = 0;
				char *argv[10];

					while (token != NULL && argc < 10)
					{
						argv[argc++] = token;
						token = strtok(NULL, " ");
					}
				echo(argc, argv);
			}
		}
	}

	free(line);
	return (0);
}
