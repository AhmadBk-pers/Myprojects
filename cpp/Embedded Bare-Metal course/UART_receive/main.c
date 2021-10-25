#include "stm32f4xx.h"                  // Device header



void USART2_init_rec(void);
char USART2_read(void);
void delayMs(int delay);
void led_play(int value);

int main (void)
{
	RCC->AHB1ENR	|= 0x1;						//ENABLE portA
	GPIOA->MODER	|=0x400;					//set pin as output
	
	USART2_init_rec();
	
	while (1)
	{
		char ch = USART2_read();
		led_play(ch);
	}
}

void USART2_init_rec(void)
{
	RCC->APB1ENR	|= 0x20000;				//ENABLE USART
	RCC->AHB1ENR	|= 0x1;						//ENABLE portA
	
	//Configuring PA3 as USART2 RX
	GPIOA->AFR[0]	=0x7000;					//using usart code alternate function on PA2 
	GPIOA->MODER	|= 0x80; 					//setting the GPIO PA2 to alternate mode
	
	USART2->BRR		|=0x008b;					//Buad rate 115200 @16MHZ
	USART2->CR1		|=0x4;						//ENABLE RX
	USART2->CR1		|=0x2000;					//ENABLE Uart    (it is advicable that this is the last thing to do
	
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x20)){}												//wait until char arrive
	return (USART2->DR & 0xFF);
}

void led_play(int value)
{
	value %= 16;
	for (;value>0;value--)
	{
		GPIOA->BSRR	= 0x20;						//turn on the led
		delayMs(100);
		GPIOA->BSRR	=	0x20000;				//turn off the led
		delayMs(100);
	}
	delayMs(100);
}

void delayMs(int delay)
{
	volatile int i;
	for (;delay>0;delay--)
	{
		for (i=0; i<3195;i++);
	}
}
