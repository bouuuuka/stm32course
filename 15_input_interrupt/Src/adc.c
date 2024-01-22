#include "stm32f4xx.h"
#include "adc.h"


#define ADC1EN			(1U<<8)
#define GPIOAEN  		(1U<<0)
#define ADC_CH1 		(1U<<0)
#define ADC_SEQ_LEN_1 	(0x00)
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)
/**
 * adc configured with 3 channels
 * ch2,ch3,ch5
 * first channel = ch5
 * second = ch2
 * third = ch3
 */

void pa1_adc_init(void) {
	/*Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN ;
	/*Set the mode of PA1 to analo */
	GPIOA->MODER	 |= (1U<<2);
	GPIOA->MODER	 |= (1U<<3);
	/***configure the ADC module***/
	/*Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN ;

	/*conversion sequence start*/
	ADC1->SQR3 |= ADC_CH1;

	/*conversion sequence length*/
	//how many channels i am using
	 ADC1->SQR1 |= ADC_SEQ_LEN_1 ;
	/*Enable ADC module*/
	 ADC1->CR2 |= CR2_ADON ;

}


void start_conversation(void) {
	/*Strat the conversation */
	ADC1->CR2 |= CR2_SWSTART ;
}
uint32_t adc_read(void){
	/*wait for the conversation to be complete */
	// to see the status of any register we search in Status register
	while (!(ADC1->SR & SR_EOC)){}

	/*Read the converted result*/
	return (ADC1->DR);
}
