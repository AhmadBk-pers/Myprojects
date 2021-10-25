#include "stm32f4xx.h"                  // Device header

int period;
float freq;

int main(void)
{
	int last_value =0;
	int current_value= 0;
	
	RCC->AHB1ENR	|=	0x1;
	GPIOA->MODER	|=	0x800;		//set PA5 to Alternate function
	GPIOA->AFR[0]	|=	0x100000;	//SET PA5 to AF1
	
	RCC->APB1ENR	|=	1;			//enable TIM2
	TIM2->PSC			=	160-1;		//16 000 000 Divide by 1600 = 10 000 
	TIM2->ARR			=	10000 -1;	//10	000	Divide by 10	000 = 1
	TIM2->CCMR1		=	0x30;			//SET output to toggle on match
	TIM2->CCR1		=	0;				//SET the value of the match
	TIM2->CCER		|=1;				//Enable CH1 compare mode
	TIM2->CNT			=	0;				//CLEAR the timer counter
	TIM2->CR1			=	1;				//ENABLE the counter
	
	//Configure PA6 as input of TIM3 CH1
	RCC->AHB1ENR	|=	0x1;
	GPIOA->MODER	|=	0x2000;		//set PA6 to Alternate function
	GPIOA->AFR[0]	|=	0x2000000;	//SET PA6 to AF2 for TIM3 CH1
	
	//Config TIM3
	RCC->APB1ENR	|=	2;			//enable TIM3
	TIM3->PSC			=	16000-1;		//16 000 000 Divide by 16000 
	TIM3->CCMR1		=	0x41;			//SET CH1 to capture at every edge
	TIM3->CCER		=0x0B;				//Enable CH1 compare mode
	TIM3->CR1			=	1;				//ENABLE the counter
	
	
	while(1){
			// wait until edge rises
			while(!(TIM3->SR &2)){}
			current_value = TIM3->CCR1;
				period = current_value - last_value;
				last_value = current_value;
				freq = 1000.0f/period;
	}
}
