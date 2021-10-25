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

char* StrCpy(char *dest, const char *src)
{
	char *dest_ptr = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return dest_ptr;
}

void StrCpyTest (const char *str)
{
	char *dest = (char *) malloc(strlen(str) + 1);
	dest = StrCpy(dest,str);
	if (!strcmp(str,dest))
	{
		green();
		printf("The function StrCpy passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrCpy failed the test\n");
		reset();
	}
	
	free(dest);
}


char* StrNCpy(char *dest, const char *src, size_t n)
{
	char *dest_ptr = dest;
	int i = 0;
	
	for (i = 0; i < (int)n; i++)
	{
		if (*src != 0)
		{
			*dest = *src;
			dest++;
			src++;
		}
		else
		{
			*dest = '\0';
			src++;
		}
	}

	return dest_ptr;
}

void StrNCpyTest (const char *str,size_t n)
{
	char *dest = (char *)malloc(strlen(str)+ 1);
	char *real_result = strncpy(dest,str, n);
	
	dest = StrNCpy(dest,str, n);
	
	if (real_result == dest)
	{
		green();
		printf("The function StrNCpy passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrNCpy failed the test\n");
		reset();
	}
	
	free(dest);
}

int StrCaseCmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if ((tolower(*str1) - tolower(*str2)) != 0)
		{
			return (*str1 - *str2);
		}
		
		str1++;
		str2++;
	}
	return 0;
}

void StrCaseCmpTest(const char *str1, const char *str2)
{
	int result = StrCaseCmp(str1, str2)/fabs(StrCaseCmp(str1, str2) + 0.001);
	int real_result = strcasecmp(str1, str2)/fabs(strcasecmp(str1, str2) + 0.001);
	if (result == real_result)
	{
		green();
		printf("The function strcmp passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function strcmp failed the test\n");
		reset();
	}
}

char *StrChr( char *str,int ch)
{
	char *temp = NULL;
	
	while (*str != '\0')
	{
		if (*str == (char)ch)
		{
			temp = str;
			return temp;
		}
		str++;
	}
	return temp;
}

void StrChrTest( char *str,int ch)
{
	char *result = StrChr(str,ch);
	char *real_result = strchr(str,ch);
	
	if (result == real_result)
	{
		green();
		printf("The function StrChr passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function StrChr failed the test\n");
		reset();
	}
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
}

char *StrCat(char *dest, const char *src)
{
	char *dest_ptr = dest + strlen(dest);
	
	while (*src != '\0')
	{
		*dest_ptr = *src;
		dest_ptr++;
		src++;
	}
	*dest_ptr = '\0';
	
	return dest;
}

void StrCatTest(char *dest, const char *src)
{
	char *test_dest = dest;
	char *result;
	char *real_value;
	
	result = StrCat(test_dest,src);
	real_value = strcat(test_dest,src);
	
	if (!strcmp(result,real_value))
	{
		green();
		printf("The function StrCat passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrCat failed the test\n");
		reset();
	}
	
}

char* StrNCat(char *dest, const char *src,size_t n)
{
	char *dest_ptr = dest + strlen(dest);
	int i = 0;
	
	for (i = 0; i < (int)n; i++)
	{
		*dest_ptr = *src;
		dest_ptr++;
		src++;
	}
	*dest_ptr = '\0';
	
	return dest;
}

void StrNCatTest (char *dest, const char *src,size_t n)
{
	char *test_dest = dest;
	char *result ;
	char *real_value ;
	
	result = StrNCat(test_dest,src, n);
	real_value = strncat(test_dest,src, n);
	
	if (!strcmp(result,real_value))
	{
		green();
		printf("The function StrNCat passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrNCat failed the test\n");
		reset();
	}
	
}

const char *StrStr (const char *string, const char *substring)
{
	const char *string_ptr = string;
	const char *substring_ptr = substring;
	
	if (!strlen(substring))
	{
		return string;
	}
	
	while (*string != '\0')
	{
		string_ptr = string;
		substring_ptr = substring;
		
		while (*substring_ptr != '\0' && *substring_ptr == *string_ptr)
		{
			substring_ptr ++; string_ptr ++;
		}
		
		if (*substring_ptr != '\0')
		{
			return string;
		}
	}
	return NULL;	
}

void StrStrTest(const char *string, const char *substring)
{
	const char *result = StrStr(string, substring);
	const char *real_value = StrStr(string, substring);
	
	if (!strcmp(result,real_value))
	{
		green();
		printf("The function StrStr passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function StrStr failed the test\n");
		reset();
	}
}

int StrSpn(const char *s1, const char *s2)
{
	int count = 0;
	
	while (*s1 && strchr(s2,*s1++))
	{
		count ++;
	}
		
	return count;
}

void StrSpnTest(const char *s1, const char *s2)
{
	int result = StrSpn(s1,s2);
	int real_result = strspn(s1,s2);
	
	if (result == real_result)
	{
		green();
		printf("The function StrSpn passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function StrSpn failed the test\n");
		printf("%d %d \n",result,real_result);
		reset();
	}
}

int IsPolCheck(const char *str)
{
	int length = strlen(str), i = 0;
	const char *str_end = str + length -1;
	
	for (i = 0; i < length / 2; i++)
	{
		if (*str != *str_end)
		{
			return 0;
		}
		
		str++;
		str_end--;
	}
	
	return 1;
}

void IsPolCheckTest(const char *str, int real_result)
{
	int result = IsPolCheck(str);
	
	if (result == real_result)
	{
		green();
		printf("The function IsPolCheck passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function IsPolCheck failed the test\n");
		reset();
	}
}

int main()
{
	char *test_dest = (char *)calloc(100,1);
	StrCpyTest("Ahmad");
	StrNCpyTest("Ahmad",4);
	StrNCpyTest("Ahmad",5);
	StrNCpyTest("Ahmad",6);
	
	StrCaseCmpTest("AHMAD","ahmad");
	
	StrChrTest("Ahmad",'A');
	
	StrDupTest("Ahmad");
	
	StrCatTest(test_dest,"Ahmad");
	StrCatTest(test_dest,"Bakri");
	
	StrNCatTest(test_dest,"Ahmad",3);
	StrNCatTest(test_dest,"Bakri",5);
	
	StrStrTest("Ahmad","hm");
	StrStrTest("Ahmad","a");
	
	StrSpnTest("Ahmad","ah");
	StrSpnTest("cabbage", "abc");
	StrSpnTest("cabbage", "");
	
	IsPolCheckTest("ahmha",1);
	IsPolCheckTest("ahmad",0);
	IsPolCheckTest("ahha",1);

	free(test_dest);
	
	return 0;
}
