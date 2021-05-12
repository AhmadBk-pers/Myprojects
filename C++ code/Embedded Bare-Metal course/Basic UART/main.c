//USART_CR1
//bit 13  bit 2 bit 3 1

#include "stm32f4xx.h"                  // Device header

void USART2_init(void); 
void USART_write(int ch);
void delayMs(int delay);
	
int main(void)
{
	USART2_init();
	while(1)
	{
		USART_write('Y');
		USART_write('i');
		USART_write('\r');
		USART_write('\n');
		delayMs(1000);
	}
	
}


void USART2_init(void)
{
	RCC->APB1ENR	|= 0x20000;				//ENABLE USART
	RCC->AHB1ENR	|= 0x1;						//ENABLE portA
	
	GPIOA->AFR[0]	=0x0700;					//using usart code alternate function on PA2 
	GPIOA->MODER	|= 0x20; 					//setting the GPIO PA2 to alternate mode
	
	USART2->BRR		|=0x0683;					//Buad rate 9600 @16MHZ
	USART2->CR1		|= 0x0008;				//ENABLE TX
	USART2->CR1		|= 0x2000;				//ENABLE Uart    (it is advicable that this is the last thing to do
	
}

void USART_write(int ch)
{
	while(!(USART2->SR & 0x0080)){}	//checking tx buffer to empty
	USART2->DR = (ch & 0xFF);	
}

void delayMs(int delay)
{
	int i;
	for (;delay>0;delay--)
	{
		for (i=0; i<319500;i++);
	}
}
	
