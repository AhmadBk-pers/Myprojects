#include "stm32f4xx.h"                  // Device header

//Toggle led at 1 hz using timer 2 compare mode

int main (void)
{
	RCC->AHB1ENR	|=	0x1;
	GPIOA->MODER	|=	0x800;		//set PA5 to Alternate function
	GPIOA->AFR[0]	|=	0x100000;	//SET PA5 to AF1
	
	RCC->APB1ENR	|=	1;			//enable TIM2
	TIM2->PSC			=	1600-1;		//16 000 000 Divide by 1600 = 10 000 
	TIM2->ARR			=	10000 -1;	//10	000	Divide by 10	000 = 1
	TIM2->CCMR1		=	0x30;			//SET output to toggle on match
	TIM2->CCR1		=	0;				//SET the value of the match
	TIM2->CCER		|=1;				//Enable CH1 compare mode
	TIM2->CNT			=	0;				//CLEAR the timer counter
	TIM2->CR1			=	1;				//ENABLE the counter
	
	while(1){
	}
		
}
