#include <stdio.h>	
#include <stdlib.h>	/*malloc*/
#include <string.h>	/*strncpy, strlen*/
#include <strings.h>	/*strcasecmp*/
#include <math.h>	/*fabs*/
#include <ctype.h>	/*tolower*/

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





char* StrDup(const char *str)
{
	char *head = (char *)malloc(sizeof(char) * strlen(str) + 1);
	char *temp = head;
	
	while (*str != '\0')
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return head;
}


void StrDupTest (const char *str)
{
	char *result = StrDup(str);
	int temp = 5;
	int arr[10];
	int *temparr = (int *)malloc(50);
/*	temp = arr[11];*/
	arr[11] = 5;
	
	if (!strcmp(str,result))
	{
		green();
		printf("The function StrDup passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrDup failed the test\n");
		reset();
	}
	
	free(result);
/*	temp = *result;*/
	if (*temparr)
	{
		1;
	}
	free(temparr);
}


int main()
{
	StrDupTest("Ahmad");

	return 9;
}
