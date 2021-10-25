#include <stdio.h>	/*printf(), getchar()*/
#include <stdlib.h> /*exit()*/

#define SIZE 256
#define Escape 27 

void Exit()
{
	system("stty icanon echo");
	printf("The program ended\n");
	exit(0);
}

void PrintA()
{
	printf("A pressed\n");
}

void PrintT()
{
	printf("T pressed\n");
}

void Empty()
{
	/*empty function*/
}

void InitArr(void (*fun_ptr_arr[SIZE])())
{
	int i = 0;
	
	for (i = 0; i < SIZE; i++)
	{
		fun_ptr_arr[i] = &Empty;
	}
}

void EchoIf()
{
	unsigned char c = 0;
	
	system("stty -icanon -echo");
	
	while(1)
	{
		c = getchar();
		if ('A' == c)
		{
			PrintA();
		}
		else if ('T' == c)
		{
			PrintT();
		}
		else if (Escape == c)
		{
			Exit();
		}
	}
}

void EchoSwitchCase()
{
	unsigned char c = 0;
	
	system("stty -icanon -echo");
	
	while(1)
	{
		c = getchar();
		switch (c)
		{
			case 'A':
				PrintA();
				break;
			case 'T':
				PrintT();
				break;
			case Escape:
				Exit();
		}
	}
}

void EchoLUT()
{
	void (*fun_ptr_arr[SIZE])() = {0};
	unsigned char c = 0;
	
	InitArr(fun_ptr_arr);
	
	system("stty -icanon -echo");
	
	fun_ptr_arr['A'] = &PrintA;
	fun_ptr_arr['T'] = &PrintT;
	fun_ptr_arr[Escape] = &Exit;
	
	while (1)
	{
		c = getchar();
		
		(*fun_ptr_arr[c])();
	}
}

int main()
{
	EchoIf();
	EchoSwitchCase();
	EchoLUT();
	
	return 1;
}
