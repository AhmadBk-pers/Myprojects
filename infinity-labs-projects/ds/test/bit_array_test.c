#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include "bit_array.h"
#include "testcolors.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE 256
#endif /* TABLE_SIZE */

void TestSetAll(void);
void TestResetAll(void);
void TestToString(void);
void TestSetOn(void);
void TestSetOff(void);
void TestSetBit(void);
void TestGetVal(void);
void TestFlip(void);
void TestMirror(void);
void TestRotR(void);
void TestRotL(void);
void TestCountOn(void);
void TestCountOff(void);
void TestMirrorLUT(void);
void TestCountOnLUT(void);


void TestSomeSetAll(bitsarr_t, bitsarr_t);
void TestSomeResetAll(bitsarr_t, bitsarr_t);
void TestSomeToString(bitsarr_t, char*);
void TestSomeSetOn(bitsarr_t, size_t, bitsarr_t);
void TestSomeSetOff(bitsarr_t, size_t, bitsarr_t);
void TestSomeSetBit(bitsarr_t, size_t, int, bitsarr_t);
void TestSomeGetVal(bitsarr_t, size_t, bitsarr_t);
void TestSomeFlip(bitsarr_t, size_t, bitsarr_t);
void TestSomeMirror(bitsarr_t, bitsarr_t);
void TestSomeRotR(bitsarr_t, size_t, bitsarr_t);
void TestSomeRotL(bitsarr_t, size_t, bitsarr_t);
void TestSomeCountOn(bitsarr_t, bitsarr_t);
void TestSomeCountOff(bitsarr_t, bitsarr_t);
void TestSomeMirrorLUT(bitsarr_t, bitsarr_t, unsigned char*);
void TestSomeCountOnLUT(bitsarr_t, bitsarr_t, size_t*);

void InitMirrorBitsTable(unsigned char*);
void InitCountOnBitsTable(size_t*);


void PrintResults (const char*, const char*);
void PrintResultsLong (bitsarr_t, bitsarr_t);
void PrintResultsInt (int, int);


int main()
{
	TestSetAll();
	TestResetAll();
	TestToString();
	TestSetOn();
	TestSetOff();
	TestSetBit();
	TestGetVal();
	TestFlip();
	TestMirror();
	TestRotR();
	TestRotL();
	TestCountOn();
	TestCountOff();
	
	TestMirrorLUT();
	TestCountOnLUT();
	
	printf("\n");
	return 0;
}



void TestSetAll()
{
	printf("\nTest Set All\n");
	
	TestSomeSetAll(0, -1);
	TestSomeSetAll(-1, -1);
	TestSomeSetAll(10, -1);
}


void TestSomeSetAll(bitsarr_t input, bitsarr_t expect)
{
	bitsarr_t result = BitsArrSetAll(input);
	PrintResultsLong(result, expect);
}


void TestResetAll()
{
	printf("\nTest Reset All\n");
	
	TestSomeResetAll(0, 0);
	TestSomeResetAll(-1, 0);
	TestSomeResetAll(10, 0);
}


void TestSomeResetAll(bitsarr_t input, bitsarr_t expect)
{
	bitsarr_t result = BitsArrResetAll(input);
	PrintResultsLong(result, expect);
}


void TestToString()
{
	printf("\nTest To String\n");
	
	TestSomeToString(0, "0000000000000000000000000000000000000000000000000000000000000000");
	TestSomeToString(1, "0000000000000000000000000000000000000000000000000000000000000001");
	TestSomeToString(12, "0000000000000000000000000000000000000000000000000000000000001100");
	TestSomeToString(-1, "1111111111111111111111111111111111111111111111111111111111111111");
}


void TestSomeToString(bitsarr_t input, char *expect)
{
	char result [65] = "";
	
	BitsArrToString(input, result);
	
	PrintResults(result, expect);
}


void TestSetOn()
{
	printf("\nTest Set On\n");
	
	TestSomeSetOn(0, 0, 1);
	TestSomeSetOn(0, 1, 2);
	TestSomeSetOn(0, 3, 8);
	TestSomeSetOn(3, 2, 7);
	TestSomeSetOn(4, 0, 5);
	TestSomeSetOn(4, 2, 4);
	TestSomeSetOn(-1, 63, -1);
}


void TestSomeSetOn(bitsarr_t input, size_t index, bitsarr_t expect)
{
	bitsarr_t result = BitsArrSetOn(input, index);
	PrintResultsLong(result, expect);
}


void TestSetOff()
{
	printf("\nTest Set Off\n");
	
	TestSomeSetOff(0, 0, 0);
	TestSomeSetOff(7, 0, 6);
	TestSomeSetOff(15, 2, 11);
	TestSomeSetOff(10, 1, 8);
	TestSomeSetOff(8, 2, 8);
	TestSomeSetOff(-1, 0, -2);
}


void TestSomeSetOff(bitsarr_t input, size_t index, bitsarr_t expect)
{
	bitsarr_t result = BitsArrSetOff(input, index);
	PrintResultsLong(result, expect);
}


void TestSetBit()
{
	printf("\nTest Set Bit\n");
	
	TestSomeSetBit(0, 0, 0, 0);
	TestSomeSetBit(0, 0, 1, 1);
	TestSomeSetBit(15, 2, 0, 11);
	TestSomeSetBit(12, 1, 1, 14);
	TestSomeSetBit(10, 1, 1, 10);
}


void TestSomeSetBit(bitsarr_t input, size_t index, int value, bitsarr_t expect)
{
	bitsarr_t result = BitsArrSetBit(input, index, value);
	PrintResultsLong(result, expect);
}


void TestGetVal()
{
	printf("\nTest Get Val\n");
	
	TestSomeGetVal(0, 0, 0);
	TestSomeGetVal(10, 2, 0);
	TestSomeGetVal(10, 1, 1);
	TestSomeGetVal(-1, 63, 1);
}


void TestSomeGetVal(bitsarr_t input, size_t index, bitsarr_t expect)
{
	int result = BitsArrGetVal(input, index);
	PrintResultsInt(result, expect);
}


void TestFlip()
{
	printf("\nTest Flip\n");
	
	TestSomeFlip(0, 0, 1);
	TestSomeFlip(1, 0, 0);
	TestSomeFlip(7, 1, 5);
	TestSomeFlip(5, 1, 7);
}


void TestSomeFlip(bitsarr_t input, size_t index, bitsarr_t expect)
{
	bitsarr_t result = BitsArrFlip(input, index);
	PrintResultsLong(result, expect);
}


void TestMirror()
{
	printf("\nTest Mirror\n");
	
	TestSomeMirror(0, 0);
	TestSomeMirror(4899916394579099648, 34);
	TestSomeMirror(4611686018427387904, 2);
	TestSomeMirror(-1, -1);
	TestSomeMirror(9223372036854775807, -2);
}


void TestSomeMirror(bitsarr_t input, bitsarr_t expect)
{
	bitsarr_t result = BitsArrMirror(input);
	PrintResultsLong(result, expect);
}


void TestRotR()
{
	printf("\nTest Rot_R\n");
	
	TestSomeRotR(0, 0, 0);
	TestSomeRotR(0, 1, 0);
	TestSomeRotR(-1, 2, -1);
	TestSomeRotR(2, 1, 1);
	TestSomeRotR(-3, 1, -2);
	TestSomeRotR(64, 4, 4);
}


void TestSomeRotR(bitsarr_t input, size_t rotations, bitsarr_t expect)
{
	bitsarr_t result = BitsArrRotR(input, rotations);
	PrintResultsLong(result, expect);
}


void TestRotL()
{
	printf("\nTest Rot_L\n");
	
	TestSomeRotL(0, 0, 0);
	TestSomeRotL(0, 1, 0);
	TestSomeRotL(-1, 2, -1);
	TestSomeRotL(2, 1, 4);
	TestSomeRotL(-2, 1, -3);
	TestSomeRotL(4, 4, 64);
}


void TestSomeRotL(bitsarr_t input, size_t rotations, bitsarr_t expect)
{
	bitsarr_t result = BitsArrRotL(input, rotations);
	PrintResultsLong(result, expect);
}


void TestCountOn()
{
	printf("\nTest Count On\n");
	
	TestSomeCountOn(0, 0);
	TestSomeCountOn(1, 1);
	TestSomeCountOn(73, 3);
	TestSomeCountOn(12, 2);
	TestSomeCountOn(-1, 64);
}


void TestSomeCountOn(bitsarr_t input, bitsarr_t expect)
{
	bitsarr_t result = BitsArrCountOn(input);
	PrintResultsLong(result, expect);
}


void TestCountOff()
{
	printf("\nTest Count Off\n");
	
	TestSomeCountOff(0, 64);
	TestSomeCountOff(1, 63);
	TestSomeCountOff(7, 61);
	TestSomeCountOff(-2, 1);
	TestSomeCountOff(-1, 0);
}


void TestSomeCountOff(bitsarr_t input, bitsarr_t expect)
{
	bitsarr_t result = BitsArrCountOff(input);
	PrintResultsLong(result, expect);
}


void TestMirrorLUT()
{
	static unsigned char table [TABLE_SIZE] = {0};
	InitMirrorBitsTable(table);
	
	printf("\nTest Mirror - LUT\n");
	
	TestSomeMirrorLUT(0, 0, table);
	TestSomeMirrorLUT(4899916394579099648, 34, table);
	TestSomeMirrorLUT(4611686018427387904, 2, table);
	TestSomeMirrorLUT(-1, -1, table);
	TestSomeMirrorLUT(9223372036854775807, -2, table);
}


void TestSomeMirrorLUT(bitsarr_t input, bitsarr_t expect, unsigned char *table)
{
	bitsarr_t result = BitsArrMirrorLUT(input, table);
	PrintResultsLong(result, expect);
}


void TestCountOnLUT()
{
	static size_t table [TABLE_SIZE] = {0};
	InitCountOnBitsTable(table);
	
	printf("\nTest Count On - LUT\n");
	
	TestSomeCountOnLUT(0, 0, table);
	TestSomeCountOnLUT(1, 1, table);
	TestSomeCountOnLUT(73, 3, table);
	TestSomeCountOnLUT(12, 2, table);
	TestSomeCountOnLUT(-1, 64, table);
}


void TestSomeCountOnLUT(bitsarr_t input, bitsarr_t expect, size_t *table)
{
	bitsarr_t result = BitsArrCountOnLUT(input, table);
	PrintResultsLong(result, expect);
}






void PrintResults (const char *res_string, const char *expect_string)
{
	if (!res_string && !expect_string)
	{
		green();
		printf("result_string: NULL , expect_string: NULL\n");
	}
	else if (!res_string)
	{
		red();
		printf ("result_string: NULL , expect_string: %s\n", expect_string);
	}
	else if (!expect_string)
	{
		red();
		printf ("result_string: %s , expect_string: NULL\n", res_string);
	}
	else
	{
		if (!strcmp(res_string, expect_string))
		{
			green();
		}
		else
		{
			red();
		}
		printf ("result: %s\nexpect: %s\n", res_string, expect_string);
	}
	reset();
}


void PrintResultsLong (bitsarr_t res, bitsarr_t expect)
{
	if (res == expect)
	{
		green();
	}
	else
	{
		red();
	}
	printf ("result: %ld , expect: %ld\n", (unsigned long)res, (unsigned long)expect);
	
	reset();
}


void PrintResultsInt (int res, int expect)
{
	if (res == expect)
	{
		green();
	}
	else
	{
		red();
	}
	printf ("result: %d , expect: %d\n", res, expect);
	
	reset();
}









