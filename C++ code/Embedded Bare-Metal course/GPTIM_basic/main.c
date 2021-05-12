#include "stm32f4xx.h"                  // Device header


int main (void)
{
	//init the Led
	RCC->AHB1ENR	|=	0x1;
	GPIOA->MODER	|=	0x400;
	
	//TIM2 Config
	RCC->APB1ENR|=	1;				//enable TIM2
	TIM2->PSC		=	1600-1;			//16 000 000 Divide by 1600 = 10 000 
	TIM2->ARR		=	10000 -1;		//10	000	Divide by 10	000 = 1
	TIM2->CNT		=	0;					//CLEAR the timer counter
	TIM2->CR1		=	1;					//ENABLE the counter
	
	
	while(1)
	{
		while(!(TIM2->SR & 1)){}
		TIM2->SR	&=~1;
		GPIOA->ODR	^=	0x20;
	}
}
