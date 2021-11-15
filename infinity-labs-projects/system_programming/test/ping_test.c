#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif /* _POSIX_C_SOURCE */

#include <stdio.h>  /* printf  */
#include <unistd.h> /* fork    */
#include <signal.h> /* signals */
#include <sys/types.h>    /* pid_t */


void USRHandler(int sig, siginfo_t *info, void *ucontext);

pid_t pong = 0;

int main()
{
	struct sigaction action = {0};
	
	action.sa_sigaction = USRHandler;
	action.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGTRAP, &action, NULL);
	
	while (1)
	{
		sleep(1);
	}
	
	return 0;
}


void USRHandler(int sig, siginfo_t *info, void *ucontext)
{	
	if (SIGUSR1 == sig)
	{
		printf("ping.  ");
		fflush(stdout);
		
		pong = info->si_pid;
		kill(pong, SIGUSR2);
		sleep(1);
	}
	
	(void)ucontext;
}
