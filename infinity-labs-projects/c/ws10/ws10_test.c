/****************************************************************************/
/**********************Word boundries optimization p2************************/
/****************************Author: Ahmad Bakri*****************************/
/*******************************Reviewer: david******************************/
/****************************************************************************/

#define _OPEN_SYS_ITOA_EXT

#include <math.h>
#include <stdio.h>	/*printf(), sprintf()*/
#include <string.h>	/*strcat strcpy*/
#include <stdlib.h> /*malloc free()*/

#include "ws10_functions.h" 
#include "TestColors.h"



void TestIToA(int value, int base, char *str_original)
{
	char str_implemented[32] = {0};
	
	IToA(value, str_implemented, base);
	
	if (!strcmp(str_implemented, str_original))
	{
		green();
		printf("The function IToA passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function IToA failed the test\n");
		printf("%s \t %s\n",str_implemented, str_original);
		reset();
	}

}

void SuperTestIToA()
{
	TestIToA(2147483647, 10, "2147483647");
	TestIToA(-2147483647, 10, "-2147483647");
	TestIToA(2147483647, 2, "1111111111111111111111111111111");
	TestIToA(0, 7, "0");
	TestIToA(15, 9, "16");
	TestIToA(51, 32, "1j");
}

void TestAToI(int real_result, char *str_implemented)
{
	int result = AToI(str_implemented);
	
	if (result == real_result)
	{
		green();
		printf("The function AToI passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function AToI failed the test\n");
		reset();
	}

}

void SuperTestAToI()
{
	TestAToI(2147483647, "2147483647");
	TestAToI(-2147483647, "-2147483647");
	TestAToI(0, "0");
	TestAToI(15, "15");
	TestAToI(-15, "-15");
	
}

void TestintIsSystemLittleEndian()
{
	if (IsSystemLittleEndian())
	{    
       printf("Little endian\n");
   	}
	else
    {
       printf("Big endian\n");
	}
}

void TestPrintSelectedValues()
{
	
	PrintSelectedValues("ahmad", 5, "ahmad", 5 ,"ad", 2);
	PrintSelectedValues("ahmad", 5,"damha", 5,"ad", 2);
	PrintSelectedValues("", 0, "", 0, "", 0);
	PrintSelectedValues("ahmad", 5,"isssssssqqqqql", 14, "", 0);
	PrintSelectedValues("ahmad123", 8,"bakri123", 8,"a", 1);
	PrintSelectedValues("ahmad", 5, "bakri", 5, "ad", 2);

}


int main()
{
	SuperTestIToA();
	SuperTestAToI();
	TestintIsSystemLittleEndian();
	TestPrintSelectedValues();
	
	return 0;
}
