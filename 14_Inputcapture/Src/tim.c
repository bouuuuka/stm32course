#include "stm32f4xx.h"

#define TIM2EN 		(1U<<0)
#define CR1_CEN		(1U<<0)
#define OC_TOGGLE 	((1U<<4)|(1U<<5))
#define CCER_CC1E	(1U<<0)
#define GPIOAEN		(1U<<0)
#define TIM3EN 		(1U<<1)
#define CCER_CC1S	(1U<<1)


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
	TIM2->CR1 |= CR1_CEN ;
}


void tim2_PA5_output_compare(void) {

	/*Enable access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN ;
	/*Set the pin PA5 to an alternate function*/
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);
	/*SEt PA to AF01*/
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] &=~(1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);
	/*Enable access to tim2 */
	RCC->APB1ENR |= TIM2EN ;
	/*Set the Prescaler Value*/
	TIM2->PSC = 1600 - 1 ;		// 16 000 000 / 1600 = 10 000
	/*Set the auto-reload value */
	TIM2->ARR = 10000 - 1 ;
	/*Set Output Compare toggle mode */
	TIM2->CCMR1 = OC_TOGGLE;
	/*Enable Tim2 ch1 in compare mode */
	TIM2->CCER |=  CCER_CC1E ;

	/*clear counter*/
	TIM2->CNT = 0 ;
	/*Enable Timer*/
	TIM2->CR1 |= CR1_CEN ;
}

void tim3_PA6_input_capture(void) {
	/*Enable access to GPIOA*/
		RCC->AHB1ENR |= GPIOAEN ;
		/*Set the pin PA6 to an alternate function*/
		GPIOA->MODER &=~ (1U<<12);
		GPIOA->MODER |= (1U<<13);
		/*SEt PA6 to AF02*/
		GPIOA->AFR[0] |= (1U<<25);
		GPIOA->AFR[0] &=~(1U<<24);
		GPIOA->AFR[0] &=~(1U<<26);
		GPIOA->AFR[0] &=~(1U<<27);
		/*Enable access to tim3 */
		RCC->APB1ENR |= TIM3EN ;
		/*Set the Prescaler Value*/
		TIM3->PSC = 1600 - 1 ;		// 16 000 000 / 1600 = 10 000
		/*Set CH1 to input capture */
		TIM3->CCMR1 |= CCER_CC1S;
		/*Set CH1 to capture at rising edge */
		TIM3->CCER  |= CCER_CC1E;
		/*Enable TIM3*/
		TIM3->CR1 |= CR1_CEN ;
}
