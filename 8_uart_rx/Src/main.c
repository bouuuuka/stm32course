#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

/*usart2 RX pin = PA3*/
char key;

#define GPIOAEN  1U
#define PIN5 		(1U<<5)
#define LED_PIN 	PIN5




int main(void) {


	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_rxtx_init();

	while(1){
		key = uart2_read();
		if(key=='O') {
			GPIOA->ODR |= LED_PIN;
		}
		else if ( key=='C') {
			GPIOA->ODR &=~ LED_PIN;
		}
	}
}







