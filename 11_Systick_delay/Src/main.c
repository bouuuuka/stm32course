#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN  1U
/*#define GPIOAEN  (1U<<0)*/
#define PIN5 		(1U<<5)
#define LED_PIN 	PIN5


int main(void) {

	/*Enable clock to GPIOA */
	RCC->AHB1ENR 	 |= GPIOAEN;
	/*Set PA5 as an output pin*/
	GPIOA->MODER	 |= (1U<<10);
	GPIOA->MODER	 &=~ (1U<<11);

	/*Initialisation of uart Tx*/
	uart2_tx_init();

	while(1){
		printf("A Second passed !!!!   \n\r");
		GPIOA->ODR ^= LED_PIN;
		systick_Delays_Ms(1000);
	}
}







