#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif /* _POSIX_C_SOURCE */

#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi */
#include <unistd.h> /* fork    */
#include <signal.h> /* signals */
#include <sys/types.h> /* pid_t */


void USRHandler(int sig);


pid_t ping = 0;


int main(int argc, char **argv)
{
	struct sigaction action = {0};
	action.sa_handler = USRHandler;
	
	sigaction(SIGUSR2, &action, NULL);
	sigaction(SIGTRAP, &action, NULL);
	
	if (argc <= 1)
	{
		printf("\nmissing ping pid\n");
		return 1;
	}
	
	ping = atoi(argv[1]);
	kill(ping, SIGUSR1);
	
	while (1)
	{
		sleep(1);
	}
	
	return 0;
}


void USRHandler(int sig)
{
	if (SIGUSR2 == sig)
	{
		printf("pong.  ");
		fflush(stdout);
		
		kill(ping, SIGUSR1);
		sleep(1);
	}
}

