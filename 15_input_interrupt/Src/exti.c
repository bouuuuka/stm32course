#include "exti.h"

#define GPIOCEN    (1U<<2)
#define SYSCFGEN   (1U<<14)
#define TR13	   (1U<<13)


void pc13_exti_init(void) {

	/*Disable the global interrupts*/
	__disable_irq();
	/*Enable GPIOC CLock*/
	RCC->AHB1ENR |= GPIOCEN;

	//Set PIN pc13 Mode
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	/*Enable clock to sysconfig (SYSCFG) */
	RCC->APB2ENR |= SYSCFGEN;

	/*Select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |=(1U<<5);
	SYSCFG->EXTICR[3] &=~(1U<<4);
	SYSCFG->EXTICR[3] &=~(1U<<6);
	SYSCFG->EXTICR[3] &=~(1U<<7);

	/*Unmask EXTI13*/
	EXTI->IMR  |= (1<<13);

	/*Select falling edge trigger*/
	EXTI->FTSR |= TR13;

	/*Enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);


	/*Enable the global interrupts*/
	__enable_irq();

}
