#include <unistd.h>
#include <stdio.h>

/**
 * main - Entry point of the program.
 * Description: This function retrieves and prints the Process ID (PID)
 *              and Parent Process ID (PPID) of the current process.
 *
 * list_pid = lists the PID of the prossess.
 * list_ppid = lists the PPID of the prosess.
 * Return: 0
 */

int main(void)
{
	pid_t list_pid;

	list_pid = getpid();
	printf("The PID is: %u\n", list_pid);

	pid_t list_ppid;

	list_ppid = getppid();
	printf("The PPID is: %u\n", list_ppid);

	return (0);
}

