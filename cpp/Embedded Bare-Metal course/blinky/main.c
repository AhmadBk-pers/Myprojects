//PA5 LED
//AHB1
//RCC->AHB1ENR
//GPIOx_MODER
//GPIOx_ODR

#include "stm32f4xx.h"                  // Device header
void delayMs(int delay);

int main(void)
{
	RCC->AHB1ENR |= 1;										//enable GPi/O A clock
	
	GPIOA->MODER |=0x400;
	
	
	while(1){
		GPIOA->ODR = 0x20;
		delayMs(50);
		GPIOA->ODR &=~0x20;
		delayMs(50);
		
		
	}
}


void delayMs(int delay)
{
	int i;
	for(; delay>0;delay--){
		
		for(i = 0; i<3195;i++);
	}
}
