/**********************/
/*******Bitwise********/
/***Reviewed by Afik***/
/**********************/

#include <stdio.h>	
#include <math.h>


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


long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

/*******************************************************************/

void TestPow2(unsigned int x, unsigned int y, long real_result)
{
	long result = Pow2(x, y);
	
	if (real_result == result)
	{
		green();
		printf("The function Pow2 passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Pow2 failed the test\n");
		reset();
	}
}

void SuperTestPow2()
{
	TestPow2(1, 2, 4);
	TestPow2(0, 5, 0);
	TestPow2(5, 2, 20);
}

/*******************************************************************/

int Is2MupliplantLoop(unsigned int n)
{
	unsigned int x = 1;
	
	while (x <= n)
	{
		if (!(n ^ x))
		{
			return 1;
		}
		
		x <<= 1;
	}
	
	return 0;
}

void TestIs2MupliplantLoop(unsigned int n , long real_result)
{
	long result = Is2MupliplantLoop(n);
	
	if (real_result == result)
	{
		green();
		printf("The function Is2MupliplantLoop passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Is2MupliplantLoop failed the test\n");
		reset();
	}
}

void SuperTestIs2MupliplantLoop()
{
	TestIs2MupliplantLoop(1, 1);
	TestIs2MupliplantLoop(10, 0);
	TestIs2MupliplantLoop(8, 1);
	TestIs2MupliplantLoop(16, 1);
}

int Is2MupliplantWithoutLoop(unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
	return !(n & (n-1));
}

void TestIs2MupliplantWithoutLoop(unsigned int n , long real_result)
{
	long result = Is2MupliplantWithoutLoop(n);
	
	if (real_result == result)
	{
		green();
		printf("The function Is2MupliplantWithoutLoop passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Is2MupliplantWithoutLoop failed the test\n");
		reset();
	}
}

void SuperTestIs2MupliplantWithoutLoop()
{
	TestIs2MupliplantWithoutLoop(1, 1);
	TestIs2MupliplantWithoutLoop(10, 0);
	TestIs2MupliplantWithoutLoop(8, 1);
	TestIs2MupliplantWithoutLoop(16, 1);
	TestIs2MupliplantWithoutLoop(0, 0);
}

/*******************************************************************/

int AddOne(int n)
{
    int m = 1;
     
    while ( n & m )
    {
        n = n ^ m;
        m <<= 1;
    }
     
    n = n ^ m;
    
    return n;
}

void TestAddOne(int n, int real_result)
{
	int result = AddOne(n);
	
	if (real_result == result)
	{
		green();
		printf("The function AddOne passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function AddOne failed the test\n");
		reset();
	}
}

void SuperTestAddOne()
{
	TestAddOne(1,2);
	TestAddOne(10,11);
	TestAddOne(8, 9);
	TestAddOne(-16, -15);

}

/*******************************************************************/

void Is3BitsSet(unsigned int arr[], int size)
{
	int count = 0, i = 0, original = 0;
	
	for (i = 0; i < size; i++)
	{
		count = 0;
		original = arr[i];
		
		while ( arr[i] > 0 )
		{
			if ( arr[i] & 1 )
			{
		    	count ++;
		    }
		    
		    arr[i] >>= 1;
		}
		 
		if (count == 3)
		{
			printf("%d\n",original);
		}
    }
}

void TestIs3BitsSet()
{
	int size = 6;
	unsigned int arr[] = {0, 3, 5,7,14,13};
	
	Is3BitsSet(arr,size);
}

/*******************************************************************/

int Is2And6On(unsigned char chr)
{
    return ((chr & 2) && (chr & 32));
}

void TestIs2And6On(unsigned char chr, int real_result)
{
	int result = Is2And6On(chr);
	
	if (real_result == result)
	{
		green();
		printf("The function Is2And6On passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Is2And6On failed the test\n");
		reset();
	}
}

void SuperTestIs2And6On()
{
	TestIs2And6On(34, 1);
	TestIs2And6On(54, 1);
	TestIs2And6On(52, 0);
	TestIs2And6On(0, 0);
}

/*******************************************************************/

int Is2Or6On(unsigned char chr)
{
	return ((chr & 2) || (chr & 32));
}

void TestIs2Or6On(unsigned char chr, int real_result)
{
	int result = Is2Or6On(chr);
	
	if (real_result == result)
	{
		green();
		printf("The function Is2Or6On passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Is2Or6On failed the test\n");
		reset();
	}
}

void SuperTestIs2Or6On()
{
	TestIs2Or6On(32, 1);
	TestIs2Or6On(54, 1);
	TestIs2Or6On(52, 1);
	TestIs2Or6On(204, 0);
	TestIs2Or6On(0, 0);
}

/*******************************************************************/

unsigned char Swap3And5(unsigned char chr)
{
	unsigned char bit5 = chr & 16;
	unsigned char bit3 = chr & 4;
	
	chr &= ~(1 << 4);
	chr &= ~(1 << 2);
	
	bit5 >>= 2;
	bit3 <<= 2;
	
	return (chr | bit5 | bit3);
}

void TestSwap3And5(unsigned char chr, unsigned char real_result)
{
	unsigned char result = Swap3And5(chr);
	
	if (real_result == result)
	{
		green();
		printf("The function Swap3And5 passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function Swap3And5 failed the test\n");
		reset();
	}
}

void SuperTestSwap2And6On()
{
	TestSwap3And5(204, 216);
	TestSwap3And5(200, 200);
	TestSwap3And5(88, 76);
	TestSwap3And5(0, 0);
}

/*******************************************************************/

unsigned char MirrorWithoutLoop(unsigned char chr)
{
	chr = ((chr & 0xF0) >> 4) | ((chr & 0x0F) << 4);
	chr = ((chr & 0xCC) >> 2) | ((chr & 0x33) << 2);
	chr = ((chr & 0xAA) >> 1) | ((chr & 0x55) << 1);
		
	return chr;
}

void TestMirrorWithoutLoop(unsigned char chr, unsigned char real_result)
{
	unsigned char result = MirrorWithoutLoop(chr);
	
	if (real_result == result)
	{
		green();
		printf("The function MirrorWithoutLoop passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function MirrorWithoutLoop failed the test\n");
		reset();
	}
}

void SuperTestMirrorWithoutLoop()
{
	TestMirrorWithoutLoop(105, 150);
	TestMirrorWithoutLoop(10, 80);
	TestMirrorWithoutLoop(7, 224);
	TestMirrorWithoutLoop(0, 0);
	TestMirrorWithoutLoop(6, 96);
}

unsigned char MirrorWithtLoop(unsigned char chr)
{
	unsigned char mirrored_chr = 0;
	int byte_size = 8, i = 0;
	for (i = 0; i < byte_size - 1; i++)
	{
		mirrored_chr = mirrored_chr | (chr & 1);
		mirrored_chr <<= 1;
		chr >>= 1;
	}
	
	return mirrored_chr;
}

void TestMirrorWithtLoop(unsigned char chr, unsigned char real_result)
{
	unsigned char result = MirrorWithtLoop(chr);
	
	if (real_result == result)
	{
		green();
		printf("The function MirrorWithtLoop passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function MirrorWithtLoop failed the test\n");
		reset();
	}
}

void SuperTestMirrorWithtLoop()
{
	TestMirrorWithtLoop(105, 150);
	TestMirrorWithtLoop(10, 80);
	TestMirrorWithtLoop(7, 224);
	TestMirrorWithtLoop(0, 0);
	TestMirrorWithtLoop(6, 96);
	
}

/*******************************************************************/

unsigned int CountOnes(int x)
{
	int count = 0, mask = 1;
	
	while (0 != mask)
	{
		if (x & mask)
		{
			count ++;
	    }
	    mask <<= 1;
	}
	
	return count;
}

void TestCountOnes(unsigned int x, unsigned int real_result)
{
	unsigned int result = CountOnes(x);
	
	if (real_result == result)
	{
		green();
		printf("The function CountOnes passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function CountOnes failed the test\n");
		printf("%d %d\n",real_result, result);
		reset();
	}
}

void SuperTestCountOnes()
{
	TestCountOnes(128, 1);
	TestCountOnes(155, 5);
	TestCountOnes(20, 2);
	TestCountOnes(0, 0);
	TestCountOnes(6, 2);
	TestCountOnes(-1, 32);
}
/*******************************************************************/

void SwapInt(unsigned int *x, unsigned int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

void TestSwapInt(unsigned int x, unsigned int y)
{
	unsigned int old_x = x, old_y = y;
	SwapInt(&x,&y);
	
	if ((old_x == y) && (old_y == x))
	{
		green();
		printf("The function SwapInt passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function SwapInt failed the test\n");
		reset();
	}
}

void SuperTestSwapInt()
{
	TestSwapInt(128, 1);
	TestSwapInt(155, 5);
	TestSwapInt(20, 2);
	TestSwapInt(0, 0);
	TestSwapInt(6, 2);
}
/*******************************************************************/

unsigned int GetMaxDivasble16(unsigned int x)
{
	unsigned int closest_max_div = 0, div = 16;
	
	while (x >= div)
	{
		if (x & div)
		{
			closest_max_div = div;
		}
		
		div <<= 1;
	}
	
	return closest_max_div;
}

void TestGetMaxDivasble16(unsigned int x, unsigned int real_result)
{
	unsigned int result = GetMaxDivasble16(x);
	
	if (real_result == result)
	{
		green();
		printf("The function GetMaxDivasble16 passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function GetMaxDivasble16 failed the test\n");
		reset();
	}
}

void SuperTestGetMaxDivasble16()
{
	TestGetMaxDivasble16(33,32);
	TestGetMaxDivasble16(17,16);
	TestGetMaxDivasble16(22, 16);
	TestGetMaxDivasble16(0, 0);
}

/*******************************************************************/

void InitLUT(int LUT_ones[])
{
	int i = 0;
	for (i = 0; i < 256; i++)
  {
    LUT_ones[i] = CountOnes(i);
  }
}

unsigned int CountOnesLUT(unsigned int x)
{
	int count = 0, mask = 255;
	int LUT_ones[256] = {0};
	
	InitLUT(LUT_ones);
	
	count += LUT_ones[x & mask];
	count += LUT_ones[x >> 8 & mask];
	count += LUT_ones[x >> 8 & mask];
	count += LUT_ones[x >> 8 & mask]; 	
	
	return count;
}

void TestCountOnesLUT(unsigned int x, unsigned int real_result)
{
	unsigned int result = CountOnesLUT(x);
	
	if (real_result == result)
	{
		green();
		printf("The function CountOnesLUT passed the test\n");
		reset();
	}
	else
	{
		red();
		printf("The function CountOnesLUT failed the test\n");
		printf("%d %d\n",real_result, result);
		reset();
	}
}

void SuperTestCountOnesLUT()
{
	TestCountOnesLUT(128, 1);
	TestCountOnesLUT(155, 5);
	TestCountOnesLUT(20, 2);
	TestCountOnesLUT(0, 0);
	TestCountOnesLUT(6, 2);
	TestCountOnesLUT(-1, 32);
}

/*******************************************************************/

void PrintRawFloatBinary(float f)
{
	unsigned int *float_as_int = (unsigned int *)&f;
	int i = 0;

	for (i = 0; i <= 31; i++)
	{
		if (i % 8 == 0)
		{
		  printf(" ");
		} 
		
		printf("%d", (*float_as_int >> (31 - i)) & 1);
	}
	
	printf("\n");
}

void TestPrintRawFloatBinary()
{
	PrintRawFloatBinary(2.5);
	PrintRawFloatBinary(0);
	PrintRawFloatBinary(5.32);
	PrintRawFloatBinary(.21);
}

/*******************************************************************/

int main()
{
	SuperTestIs2MupliplantLoop();
	SuperTestIs2MupliplantWithoutLoop();
	SuperTestPow2();
	SuperTestAddOne();
	TestIs3BitsSet();
	
	SuperTestIs2And6On();
	SuperTestIs2Or6On();
	SuperTestSwap2And6On();
	
	SuperTestMirrorWithoutLoop();
	SuperTestMirrorWithtLoop();
	
	SuperTestCountOnes();
	SuperTestCountOnesLUT();
	
	SuperTestSwapInt();
	
	SuperTestGetMaxDivasble16();
	
	TestPrintRawFloatBinary();
	
	
	
	return 0;
}











