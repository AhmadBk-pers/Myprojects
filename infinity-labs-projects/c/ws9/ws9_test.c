/****************************************************************************/
/************************Word boundries optimization*************************/
/****************************Author: Ahmad Bakri*****************************/
/*******************************Reviewer: Ron********************************/
/****************************************************************************/



/****************************************************************************/
/******************************** Libraries *********************************/
/****************************************************************************/

#include <stdio.h>	/*printf(), sprintf()*/
#include <string.h>	/*strcat strcpy*/
#include <stdlib.h> /*malloc free()*/
#include "ws9_functions.h" 
#include "TestColors.h"


/****************************************************************************/
/********************************** Macros **********************************/
/****************************************************************************/

#define BYTE_SIZE 8
#define WORD_SIZE sizeof(size_t)


/****************************************************************************/
/******************************* Declerations *******************************/
/****************************************************************************/

void MemsetTest(int c, size_t n, int alignment_offset);
void SuperMemsetTest();

void MemcpyTest(void *src, size_t n, int alignment_offset);
void SuperMemcpyTest();

void MemmoveTest(int position, size_t n);
void SuperMemmoveTest();


int main()
{
	SuperMemsetTest();
	
	SuperMemcpyTest();
	
	SuperMemmoveTest();
	
	return 0;
}


/****************************************************************************/
/******************************* Definitions* *******************************/
/****************************************************************************/

void MemsetTest(int c, size_t n, int alignment_offset)
{
	char test_1[] = "****************************************";
	char test_2[] = "****************************************";
	
	Memset(test_1 + WORD_SIZE + alignment_offset, c, n);
	memset(test_2 + WORD_SIZE + alignment_offset, c, n);
	
	if (!memcmp(test_1, test_2, 40))
	{
		green();
		printf("The function Memset passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function Memset failed the test\n");
		reset();
	}
}

void SuperMemsetTest()
{
	MemsetTest('h', 10, 0);
	MemsetTest('z', 5, 0);
	MemsetTest('d', 26, 1);
	MemsetTest('d', 5, 3);
	MemsetTest('5', 6, 3);
	MemsetTest('5', 0, 3);
}

/***************************************************************************/

void MemcpyTest(void *src, size_t n, int alignment_offset)
{
	char test_1[] = "****************************************";
	char test_2[] = "****************************************";
	
	Memcpy(test_1 + WORD_SIZE + alignment_offset, src, n);
	Memcpy(test_2 + WORD_SIZE + alignment_offset, src, n);
	
	if (!memcmp(test_1, test_2, 40))
	{
		green();
		printf("The function Memcpy passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function Memcpy failed the test\n");
		reset();
	}
}

void SuperMemcpyTest()
{
	char *test_text = "Ahmad Bakri wrote this code so be carefull of the bulshit that he wrote";
	
	MemcpyTest(test_text, 10, 0);
	MemcpyTest(test_text, 5, 0);
	MemcpyTest(test_text, 26, 1);
	MemcpyTest(test_text, 5, 3);
	MemcpyTest(test_text, 6, 3);
	MemcpyTest(test_text, 0, 3);
}

/***************************************************************************/

void MemmoveTest(int dest_offset, size_t n)
{
	char test_1[] = "0123456789!@#$%^&*_+=-087654323456417963";
	char test_2[] = "0123456789!@#$%^&*_+=-087654323456417963";
	
	Memmove(test_1 + BYTE_SIZE + dest_offset, test_1 + BYTE_SIZE, n);
	memmove(test_2 + BYTE_SIZE + dest_offset, test_2 + BYTE_SIZE, n);
	
	if (!memcmp(test_1, test_2, 40))
	{
		green();
		printf("The function Memmove passed the test\n");
		reset();
	}
	else 
	{
		red();
		printf("The function Memmove failed the test\n");
		reset();
	}
}

void SuperMemmoveTest()
{
	
	MemmoveTest(0, 0);
	MemmoveTest(5, 10);
	MemmoveTest(-5, 10);
	MemmoveTest(5, 3);
	MemmoveTest(-6, 3);
	MemmoveTest(0, 3);
}




