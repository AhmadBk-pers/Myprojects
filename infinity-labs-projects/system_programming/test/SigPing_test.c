/******************************************************************************
* Author        Ahmad Bakri
* Reviewer      ----
* Description   simple shell
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/


#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif /* _POSIX_C_SOURCE */

#include <stdio.h>  /* printf  */
#include <stdlib.h> /* exit    */
#include <unistd.h> /* fork    */
#include <signal.h> /* signals */
#include <errno.h>  /* perror  */
#include <sys/wait.h>  /* wait */
#include <sys/types.h> /* pid_t */


typedef enum {
	PARENT_TURN,
	CHILD_TURN
} turn_t;

typedef enum {
	SUCCESS,
	ERROR
} status_t;


static void USRChildHandler(int sig);
static void USRParentHandler(int sig);
static int TestSigPingStage1(void);
static int TestSigPingStage2(void);


static pid_t g_Child = 0;

int main()
{
	status_t status = SUCCESS;
	
	/*status = TestSigPingStage1();*/
	status = TestSigPingStage2();
	
	printf("\nstatus: %s\n", (0 == status) ? "SUCCESS" : "ERROR");
	perror("log");
	
	return status;
}

static int TestSigPingStage1(void)
{
	pid_t pid = 0;
	
	pid = fork();
	
	if (pid < 0)
	{
		return ERROR;
	}
	else if (pid > 0) /* parent */
	{
		struct sigaction action = {0};
		action.sa_handler = USRParentHandler;
		
		g_Child = pid;
		sigaction(SIGUSR2, &action, NULL);
		sleep(1);
		
		kill(g_Child, SIGUSR1);
		
		while (1);;
	}
	else /* child */
	{
		struct sigaction action = {0};
		action.sa_handler = USRChildHandler;
		
		sigaction(SIGUSR1, &action, NULL);
		
		while (1);;
	}
	
	return SUCCESS;
}

static int TestSigPingStage2()
{
	pid_t pid = 0;
	
	pid = fork();
	g_Child = pid;
	
	if (pid < 0)
	{
		return ERROR;
	}
	else if (pid > 0) /* parent */
	{
		struct sigaction action = {0};
		action.sa_handler = USRParentHandler;
		
		g_Child = pid;
		sigaction(SIGUSR2, &action, NULL);
		sleep(1);
		
		kill(g_Child, SIGUSR1);
		
		sleep(1);
		while (1);;
	}
	else /* g_Child */
	{
		char *args[] = {"./loop", NULL};
		execvp("./loop", args);
	}
	
	return SUCCESS;
}



static void USRParentHandler(int sig)
{
	printf("parent.  ");
	fflush(stdout);
	
	kill(g_Child, SIGUSR1);
	sleep(1);
	(void)sig;
}

static void USRChildHandler(int sig)
{
	printf("Child.  ");
	fflush(stdout);
	
	kill(getppid(), SIGUSR2);
	sleep(1);
	(void)sig;
}
