#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif /* _POSIX_C_SOURCE */

#include <stdio.h> /* printf */
#include <unistd.h> /* fork    */
#include <signal.h> /* signals */


void USRExecHandler(int sig);


int main()
{
	struct sigaction action = {0};
	action.sa_handler = USRExecHandler;
	
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGTRAP, &action, NULL);
	
	while (1);;
	return 0;
}


void USRExecHandler(int sig)
{
	if (SIGUSR1 == sig)
	{
		printf("son.  ");
		fflush(stdout);
		
		kill(getppid(), SIGUSR2);
		sleep(1);
	}
	else if (SIGTRAP == sig)
	{
		sleep(2);
	}
}
