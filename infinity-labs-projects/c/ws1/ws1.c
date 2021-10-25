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

/*Prints hello world using ascii table values*/
void AsciiHelloWorld()
{
	char hello_world[] ={0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6F, 0x20, 0x77,
	 0x6F, 0x72, 0x6c, 0x64, 0X21, 0x22}; 
		
	int i = 0;
	int length = sizeof(hello_world) / sizeof(hello_world[0]);
	
	for (i = 0; i < length; i++)
	{
		printf("%c", hello_world[i]);
	}
	printf("\n");

}

/*10 Pow n function*/
double Pow10(int n)
{
	int i = 0;
	double result = 1, base = 10;
	
	/*inverting base and exp because - sign*/
	if (n < 0)
	{
		base = 1.0 / base;
		n *= -1;
	}
	for (i = 0; i < n ; i++)
	{
		result *= base;
	}

	return result;
}

/*testing the pow10 funct*/
void testPow10(int input)
{
	double result = Pow10(input),correct_result = pow(10.0,input);
	
	if ( fabs(correct_result - result) < 0.00000001)
	{
		green();
		printf("The function passed the test\n");
		printf("%f = %f\n",correct_result , result);
		reset();
	}
	else
	{
		red();
		printf("The function failed the test\n");
		printf("%f != %f\n",correct_result , result);
		reset();
	}
	
}

void TestAllInputsPow()
{
	int min = (-5), max = 5,i;
	
	for (i = min; i < max ; i++)
	{
		testPow10(i);
	}

}

int Flipp(int num)
{
	int flipped = 0;
	
	while (num != 0)
	{
		flipped *= 10;
		flipped += num%10;
		num /= 10;
	}
	return flipped;
}

void TestFlipp(int input, int expected_value)
{
	int flipped_input = Flipp(input);
	
	if (flipped_input == expected_value)
	{
		green();
		printf("The function passed the test\n");
		printf("%d is the reverse of %d\n",flipped_input , input);
		printf("%d is the expected value\n", expected_value);
		reset();
	}
	else 
	{
		red();
		printf("The function failed the test\n");
		printf("%d is not the reverse of %d\n",flipped_input , input);
		printf("%d is the expected value\n", expected_value);
		reset();
	}
	
} 

void Swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void TestSwap(int a, int b)
{
	int old_a = a,old_b = b;
	
	Swap(&a,&b);
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

int main()
 {
	/*Q4*/
	AsciiHelloWorld();
   	/*Q5*/
	TestAllInputsPow();
   	/*Q6*/
   	TestFlipp(123,321);
   	TestFlipp(-123,-321);
   	TestFlipp(12340,4321);
   	TestFlipp(-7253,-3527);
   	/*Q7*/
   	TestSwap(1,2);
   	
	return 0;
}





