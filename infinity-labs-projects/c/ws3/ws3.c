#include <stdio.h>	
#include <stdlib.h>	/*malloc*/
#include <string.h>	/*strncpy, strlen*/
#include <strings.h>	/*strcasecmp*/
#include <math.h>	/*fabs*/
#include <ctype.h>	/*tolower*/

#define SOLDIERSNUM 100
#define DEAD 1


/*making the prints red */
void red() 
{
	printf("\033[1;31m");
}

/*making the prints green */
void green() 
{
	printf("\033[0;32m");
}

/*making the prints reseted */
void reset() 
{
 	printf("\033[0m");
}


int *FindNextAlive(int *soldiers_head, int *soldier)
{

	if ((soldier - soldiers_head ) == SOLDIERSNUM)
	{
		soldier = soldiers_head;
	}
	
	while (*soldier)
	{
		printf("Soldier %ld is dead\n", (soldier - soldiers_head) );
		soldier++;
		
		if ((soldier - soldiers_head ) == SOLDIERSNUM)
		{
			soldier = soldiers_head;
		}
	}
	
	return soldier;
}

void Kill(int *soldiers_head, int *soldier)
{
	*soldier = DEAD;
	printf("Soldier %ld were killed\n", (soldier - soldiers_head) + 1);
	
	return;
}

int JosephusProblem()
{
	int soldiers[SOLDIERSNUM] = {0}, i = 0;						/*1 is dead*/
	int *soldiers_head = soldiers, *sword_carrier = soldiers, *next_alive = NULL;
	
	for (i = 0; i < SOLDIERSNUM - 1; i++)
	{
		next_alive = FindNextAlive(soldiers_head, sword_carrier + 1);
		Kill(soldiers_head, next_alive);
		sword_carrier = FindNextAlive(soldiers_head, next_alive + 1);
	}
	
	return (sword_carrier - soldiers_head) + 1;
}

int TestJosephus(int size)
{
	int max_pow = 1;
	int diff = 0;
	int winner = 0;
	
	while (max_pow * 2 <= size)
	{
		max_pow *= 2;
	}
	
	diff = size - max_pow;
	winner = 2 * diff + 1;
	
	return winner;
}

void JosephusProblemTest()
{
	int result = JosephusProblem();
	int real_result = TestJosephus(SOLDIERSNUM);
	if (real_result == result)
	{
		green();
		printf("The function JosephusProblem passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function JosephusProblem failed the test\n");
		printf("The real result: %d \nThe received result: %d\n",real_result,result);
		reset();
	}

}


int count_members_of_PP(char **envp)
{
	int length = 0;
	
	while (*envp != NULL)
	{
		length ++;
		envp ++;
		
	}
	return length;
}

int count_members_of_P(char *envp)
{
	int length = 0;
	
	while (*envp)
	{
		length ++;
		envp ++;
	}
	return length;
}

void StrLowerDup(char *new_envp, char *envp)
{
	while (*envp)
	{
		*new_envp = tolower(*envp);
		envp++;
		new_envp++;
	}
		
	return;
}

char **CopyEnvp(char **envp)
{
	int length = count_members_of_PP(envp);
	char **new_envp = (char **)calloc(length + 1, sizeof(char *));
	char **new_envp_head = new_envp;
	
	while (*envp)
	{
		*new_envp = (char *)calloc(strlen(*envp) + 1, sizeof(char));
		StrLowerDup(*new_envp, *envp);
		new_envp++;
		envp++;
	}
	
	return new_envp_head;
}

void FreeEnvp(char **new_envp)
{
	char **temp = new_envp;
	while (*temp)
	{
		free(*temp);
		*temp = NULL;
		temp++;
	}
	
	free(new_envp);
	new_envp = NULL;
}

void PrintEnvp(char **new_envp)
{
	while (*new_envp != NULL)
	{
		printf("%s\n", *new_envp);
		new_envp++;
	}
	
	return;
}

void TestCopyEnvp(char **envp)
{
	char **new_envp = CopyEnvp(envp);
	PrintEnvp(new_envp);
	FreeEnvp(new_envp);

	return;
}


void PrintDataTypes()
{
	int i = 0, size = 13;
	
	const char *data_types[] = {"short int", "unsigned short int", "unsigned int", "int", "long int", "unsigned Long int", "long long int", "unsigned long int", "unsigned long long int", "signed char", "unsigned char", "float", "double", "long double"};
	
	int data_sizes[] = {2, 2, 4, 4, 4, 4, 8, 8, 1, 1, 4, 8, 16};
	
	for (i = 0; i < size; i++)
	{
		printf("%s data type is: %d bytes\n",data_types[i], data_sizes[i]);
	}
	
	return;
}


int main( int argc, char *argv[], char **envp)
{
	JosephusProblemTest();
	TestCopyEnvp(envp);
	PrintDataTypes();
	(void)argc;
	(void)argv;
	(void)envp;
	return 0;
}
