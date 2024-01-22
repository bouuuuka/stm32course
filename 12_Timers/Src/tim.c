#include "stm32f4xx.h"

#define TIM2EN 		(1U<<0)
#define TIM2CEN		(1U<<0)
void tim2_1hz_init(void) {

	/*Enable access to tim2 */
	RCC->APB1ENR |= TIM2EN ;
	/*Set the Prescaler Value*/
	TIM2->PSC = 1600 - 1 ;		// 16 000 000 / 1600 = 10 000
	/*Set the auto-reload value */
	TIM2->ARR = 10000 - 1 ;
	/*clear counter*/
	TIM2->CNT = 0 ;
	/*Enable Timer*/
	TIM2->CR1 |= TIM2CEN ;
}


