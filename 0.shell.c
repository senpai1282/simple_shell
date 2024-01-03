#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

void display_prompt(void) 
{
	if (isatty(STDIN_FILENO))
		printf("($) ");
}

int main(void)
{
	char input[MAX_INPUT];
	char *args[MAX_INPUT / 2 + 1];

	while (1)
	display_prompt();
	if (fgets(input, sizeof(input), stdin) == NULL) 
	{
		printf("\n");
		break;
	}
	input[strcspn(input, "\n")] = '\0';
	pid_t pid = fork();
	if (pid < 0)
       	{
		perror("fork");
		exit(EXIT_FAILURE);
	} 
	else if (pid == 0) 
	{
	args[0] = strtok(input, " ");
	if (args[0] == NULL) 
	{
		continue;
	}
	args[1] = NULL;
	if (execve(args[0], args, NULL) == -1) 
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	} else 
	{
		int status;
		waitpid(pid, &status, 0);
	}
	}
return EXIT_SUCCESS;
}

