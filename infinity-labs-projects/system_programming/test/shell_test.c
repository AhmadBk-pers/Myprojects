/******************************************************************************
* Author        Ahmad Bakri
* Reviewer      Tuzia
* Description   simple shell
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define _RED_    "\033[1;31m"
#define _GREEN_  "\033[1;32m"
#define _YELLOW_ "\033[1;33m"
#define _BLUE_   "\033[1;34m"
#define _PURPLE_ "\033[1;35m"
#define _CYAN_   "\033[1;36m"
#define _WHITE_  "\033[0m"

static void ForkImpl();
static void SystemImp();
static void ParseCommand(char *command, char **arg);

int main(int argc, char **argv)
{
    if (argv[1] == NULL)
    {
        printf(_RED_"ERROR: Invalid argument\n"_WHITE_);
    }
    else
    {
        if (!strcmp(argv[1], "fork"))
        {
            printf(_GREEN_"Running using fork\n"_WHITE_);
            ForkImpl();
        }
        else if (!strcmp(argv[1], "system"))
        {
            printf(_GREEN_"Running using system\n"_WHITE_);
            SystemImp();
        }
    }
    
    (void)argc;

    return 0;
}

static void ForkImpl()
{
    char command[100];
    char *arg[100];
    pid_t child_pid = 0;

    while (1)
    {
        printf("Please type a command\n");
        scanf("%[^\n]%*c", command);

        if (!strncmp(command, "exit", 4))
        {
            break;
        }

        ParseCommand(command, arg);

        child_pid = fork();

        if (child_pid == 0)
        {
            execvp(arg[0], arg);

            printf(_RED_"Unknown command\n"_WHITE_);
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
}

static void SystemImp()
{
    char command[100] ;

    while (1)
    {
        printf("Please type a command\n");
        fgets(command, 100, stdin);

        if (!strncmp(command, "exit", 4))
        {
            break;
        }

        system(command);
    }
    
}

static void ParseCommand(char *command, char **arg)
{
    char splitter[2] = " ", *token = "";
    size_t i = 0;
    
    arg[0] = strtok(command, splitter);

    for (i = 1; NULL != token; i++)
    {
        token = strtok(NULL, splitter);
        arg[i] = token;
    }

}