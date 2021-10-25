

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>


void USART2_init(void);



int main (void)
{
	int n;
	char str[100];
	USART2_init();
	
	stdin ("Hello from the other side\r\n");
	fprintf(stdout, " test for stdout\r\n");
	fprintf(stderr, " test for stderr\r\n");
	while (1)
	{
		printf("How old are you?");
		scanf("%d",&n);
		printf("Your age is : %d\r\n",n);
		printf("Enter yout first name :");
		gets(str);
		printf("I like your style: ");
		puts(str);
		printf("\r\n");
	}
}

void USART2_init(void)
{
	RCC->AHB1ENR	|= 0x1;						//ENABLE portA
	RCC->APB1ENR	|= 0x20000;				//ENABLE USART
	
	
	GPIOA->AFR[0]	=  0x7700;				//using usart code alternate function on PA2 
	GPIOA->MODER	|= 0xA0; 					//setting the GPIO PA2 and PA3 to alternate mode
	
	USART2->BRR		|= 0x0683;				//Buad rate 9600 @16MHZ
	USART2->CR1		|= 0x000C;				//ENABLE TX and RX
	USART2->CR1		|= 0x2000;				//ENABLE Uart    (it is advicable that this is the last thing to do
}

int USART2_write(int ch)
{
	while(!(USART2->SR & 0x0080)){}	//wait tx buffer to empty
	USART2->DR = (ch & 0xFF);
	return ch;
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x20)){}												//wait until char arrive
	return (USART2->DR & 0xFF);
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART2_read();
	if (c == '\r'){
		USART2_write(c);
		c= '\n';
	}
	USART2_write(c);
	return c;
}

int fputc(int c, FILE *f)
{
	return USART2_write(c);
}
