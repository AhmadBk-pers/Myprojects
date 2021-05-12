#include "stm32f4xx.h"                  // Device header



int main(void)
{
	RCC->AHB1ENR	|=	0x1;
	GPIOA->MODER	|=	0x800;		//set PA5 to Alternate function
	GPIOA->AFR[0]	|=	0x100000;	//SET PA5 to AF1
	
	RCC->APB1ENR	|=	1;			//enable TIM2
	TIM2->PSC			=	10-1;		//16 000 000 Divide by 10 = 1600 000 
	TIM2->ARR			=	26667 -1;	//60 hz
	TIM2->CNT			=	0;				//CLEAR the timer counter
	TIM2->CCMR1		=	0x60;			//ENABLE PWM mode
	TIM2->CCER		|=1;				//Enable CH1 pwm mode
	
	TIM2->CCR1		=	8889-1;		//pulse width 1/3 the period
	TIM2->CR1			=	1;				//ENABLE the counter
	
	while(1){
	}
}