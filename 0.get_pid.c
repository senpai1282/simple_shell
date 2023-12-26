#include <unistd.h>
#include <stdio.h>
/**
 * getpid - function returns the process ID of the current process.
 * getppid - function returns the process ID of the parent of the current process.
 * list_pid = lists the PID of the prossess.
 * list_ppid = lists the PPID of the prosess.
 * return = (0)
 */

int main(void)
{
	pid_t list_pid;
		list_pid = getpid();
	       	printf("The PID is: %u\n", list_pid);
	pid_t list_ppid;
		list_ppid = getppid();
		printf("The PID is: %u\n", list_ppid);	
    return (0);
}
