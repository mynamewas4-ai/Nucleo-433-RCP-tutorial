#include "stm32l4xx.h"

int main(void)
{
    RCC->AHB2ENR |= (1<<1)|(1<<2); // enable clock for GPIOB and GPIOC
		RCC->APB2ENR |= (1<<0);				 // enable clock for SYSCFG 
	
		GPIOC->MODER &= ~(0x3<<26);      // PC13 as input
		GPIOB->MODER &= ~(0x3<<26);			 // PB13 as output
		GPIOB->MODER |= (1<<26);
		
		SYSCFG->EXTICR[3] &= ~(0xF<<4);  // Mapping PC13 -> EXTI13
		SYSCFG->EXTICR[3] |= (0x2<<4);
	
		EXTI->RTSR1 |= (1<<13);        // trigger on rising edge
		EXTI->PR1 = (1<<13);           // clearing pending flag
		EXTI->IMR1 |= (1<<13);         // enable EXTI13
 
		NVIC->IP[40] = (2<<4);				 // set IRQ40's priority at lv2
		NVIC->ISER[1] = (1<<8);				 // enable IRQ40

    while (1)
    {
			// do nothing
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1U << 13))
    {
        EXTI->PR1 = (1U << 13);

        GPIOB->ODR ^= (1U << 13);
    }
}