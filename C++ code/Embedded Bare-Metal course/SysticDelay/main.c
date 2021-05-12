#include "stm32f4xx.h"                  // Device header

void systickdelayMs(int n);

int main (void)
{
	RCC->AHB1ENR 	|=1;
	GPIOA->MODER 	|=0x400;
	
	while (1)
	{
		GPIOA->ODR		^=0x20;
		systickdelayMs(50);
	}
}

void systickdelayMs(int n)
{
	SysTick->LOAD	= 16000;			//Reload with number of clocks per millisecond
	SysTick->VAL	=	0;										//CLEAR_BIT current value register
	SysTick->CTRL	=	0x5;									//ENABLE systic
	for (int i =0;i<n;i++)
	{
		//wait until the COUNT flag is set
		while ((SysTick->CTRL & 0x10000) ==0){}
	}
	SysTick->CTRL	=	0;
}