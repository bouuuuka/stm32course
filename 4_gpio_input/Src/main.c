#include "stm32f4xx.h"


#define GPIOCEN  (1U<<2)
/*#define GPIOAEN  (1U<<0)*/
#define PIN13 		(1U<<13)
#define PUSH_BTN 	PIN13


#define GPIOAEN  1U
/*#define GPIOAEN  (1U<<0)*/
#define PIN5 		(1U<<5)
#define LED_PIN 	PIN5


int main(void) {
	RCC->AHB1ENR 	 |= GPIOCEN;
	GPIOC->MODER	 &=~ (1U<<26);
	GPIOC->MODER	 &=~ (1U<<27);

	RCC->AHB1ENR 	 |= GPIOAEN;
	GPIOA->MODER	 |= (1U<<10);
	GPIOA->MODER	 &=~ (1U<<11);



	while(1){
		if ((GPIOC->IDR) & PUSH_BTN){
			(GPIOA->BSRR) |= (1U<<21);
		}
		else {
			(GPIOA->BSRR) |= LED_PIN;
		}



	}
	return 0;
}
