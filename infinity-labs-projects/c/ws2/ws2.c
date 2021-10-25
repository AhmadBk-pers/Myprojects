#include <stdio.h>	
#include <stdlib.h>	/*malloc*/
#include <string.h>	/*strncpy, strlen*/
#include <math.h>	/*fabs*/


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


void Swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void TestSwap(int a, int b)
{
	int old_a = a, old_b = b;
	
	Swap(&a, &b);
	if (old_a == b && old_b == a)
	{
		green();
		printf("The function passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function failed the test\n");
		reset();
	}
	
}


char *CopyArray(char arr[], int length)
{
	char *copied_arr = malloc(sizeof(arr[length]));
	
	strncpy(copied_arr, arr, length);
	
	return copied_arr;	
}


void TestCopyArray(char actual_string[],int length)
{
	char *tested_string = CopyArray(actual_string,length);
	
	 if (!strcmp(actual_string,tested_string))
	{
		green();
		printf("The function passed the test\n");
		printf("%s \n",actual_string);
		reset();
	}
	else 
	{
		red();
		printf("The function failed the test\n");
		reset();
	}
	
}


void SwapSizeT(size_t *a, size_t *b)
{
	size_t temp = *a;
	*a = *b;
	*b = temp;
}


void TestSwapSizeT(size_t a, size_t b)
{
	size_t old_a = a,old_b = b;
	
	SwapSizeT(&a,&b);
	if (old_a == b && old_b == a)
	{
		green();
		printf("The function passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function failed the test\n");
		reset();
	}
	
}


void SwapSizeTP(size_t **a_ptr_ptr, size_t **b_ptr_ptr)
{
	size_t *temp = *a_ptr_ptr;
	*a_ptr_ptr = *b_ptr_ptr;
	*b_ptr_ptr = temp;
}


void TestSwapSizeTP(size_t a, size_t b)
{
	size_t *old_a_p = &a, *old_b_p = &b, *a_ptr = &a, *b_ptr=&b;
	
	SwapSizeTP((&a_ptr),(&b_ptr));
	if (old_a_p == b_ptr && old_b_p == a_ptr)
	{
		green();
		
		printf("The function passed the test\n");
		printf("%p = %p\n",(void*)b_ptr,(void*)old_a_p);
		printf("%p = %p\n",(void*)a_ptr,(void*)old_b_p);
		
		reset();
	}
	else 
	{
		red();
		
		printf("The function failed the test\n");
		printf("%p != %p\n",(void*)b_ptr,(void*)old_a_p);
		printf("%p != %p\n",(void*)a_ptr,(void*)old_b_p);
		
		reset();
	}
	
}


void SwapSizeTPImpl(size_t **a_ptr_ptr, size_t **b_ptr_ptr)
{
	SwapSizeT(*a_ptr_ptr, *b_ptr_ptr);
}


void TestSwapSizeTPImpl(size_t a, size_t b)
{
	size_t *old_a_p = &a, *old_b_p = &b, *a_ptr = &a, *b_ptr=&b;
	
	SwapSizeTPImpl((&a_ptr),(&b_ptr));
	if (old_a_p == b_ptr && old_b_p == a_ptr)
	{
		green();
		
		printf("The function passed the test\n");
		printf("%p = %p\n",(void*)b_ptr,(void*)old_a_p);
		printf("%p = %p\n",(void*)a_ptr,(void*)old_b_p);
		
		reset();
	}
	else 
	{
		red();
		
		printf("The function failed the test\n");
		printf("%p != %p\n",(void*)b_ptr,(void*)old_a_p);
		printf("%p != %p\n",(void*)a_ptr,(void*)old_b_p);
		
		reset();
	}
	
}


size_t StrLen(const char *str)
{
	size_t length = 0;
	while ('\0' != *str)
	{
		length ++;
		str++;
	}	
	return length;
}


void StrLenTest(const char *str)
{
	size_t result = StrLen(str), real_length = strlen(str);
	
	if (result == real_length)
	{
		green();
		printf("The function strlen passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function strlen failed the test\n");
		reset();
	}
	
}


int StrCmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if ((*str1 - *str2) != 0)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return 0;
	
}

void StrCmpTest(const char *str1, const char *str2)
{
	int result = StrCmp(str1, str2)/fabs(StrCmp(str1, str2) + 0.001);
	int real_result = strcmp(str1, str2)/fabs(strcmp(str1, str2) + 0.001);
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
		printf("%d , %d \n",result,real_result);
		reset();
	}
}





int main()
 {
	/*Q1*/
	TestSwap(1,2);
	/*Q2*/
   	TestCopyArray("Ahmad",5);
   	/*Q4.a*/
   	TestSwapSizeT(1,2);
   	/*Q4.b*/
   	TestSwapSizeTP(1,2);
   	/*Q4.c*/
   	TestSwapSizeTPImpl(1,2);
   	
   	/*Functions implimintation strlen()*/
   	StrLenTest("Ahmad");
   	/*Functions implimintation strcmp()*/
   	StrCmpTest("Ahmad","Ahmad");
   	StrCmpTest("Ahmad","Ahmad1");
   	StrCmpTest("Ahmad","Ahma");
   	StrCmpTest("Ahmad","Ahmac");
   	
   	
   	
	return 0;
}
