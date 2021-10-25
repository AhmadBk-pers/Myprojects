//PC13
//AHB1
//

#include "stm32f4xx.h"                  // Device header

int main (void){
	RCC->AHB1ENR |= 4;				//Enable port C
	RCC->AHB1ENR |= 1;				//Enable port A
	
	GPIOA->MODER |=0x400;
	
	while (1){
		if (GPIOC->IDR & 0x2000)
		{
			GPIOA->BSRR = 0x200000;
		}else
			GPIOA->BSRR = 0x20;
		
	}
	
	
}
