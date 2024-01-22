#include "uart.h"

#define GPIOAEN  		(1U<<0)
#define UART2EN  		(1U<<17)


#define SYS_FREQ		16000000
#define APB1_CLK			SYS_FREQ

#define UART_BAUDRATE 	115200


#define CR1_TE 			(1U<<3)
#define CR1_UE 			(1U<<13)
#define SR_TXE 			(1U<<7)
#define SR_RXNE			(1U<<5)


#define CR1_RE 			(1U<<2)

static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


void uart2_tx_init(void);
void uart2_write(int ch);



int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void  uart2_rxtx_init(void){
	/*configure uart GPIO pin*/
	RCC->AHB1ENR    |=  GPIOAEN;

	/* set PA2 to alternate function mode */

	GPIOA->MODER	&=~ (1U<<6);
	GPIOA->MODER	|=  (1U<<7);


	/*AFR[0] Pin 0..7*/
	/*AFR[1] Pin 8..15*/
	//GPIOA->AFR[0]   |=  (7<<12);
	GPIOA->AFR[0]   |=  (1<<12);
	GPIOA->AFR[0]   |=  (1<<13);
	GPIOA->AFR[0]   |=  (1<<14);
	GPIOA->AFR[0]	&= ~(1U<<15);

	GPIOA->AFR[0]   |=  (7<<8);
		/*GPIOA->AFR[0]   |=  (1<<8);
		GPIOA->AFR[0]   |=  (1<<9);
		GPIOA->AFR[0]   |=  (1<<10);*/
		GPIOA->AFR[0]	&= ~(1U<<11);



	/*********************Configure the uart module***********************/
	/*enable clock to uart2*/
	RCC->APB1ENR 	 |= UART2EN;
	/*configure bd*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	/*configure the transfer direction*/
	USART2->CR1      |= (CR1_TE | CR1_RE) ;

	/*enable uart module*/
	USART2->CR1      |= CR1_UE;

}


void  uart2_tx_init(){
	/*configure uart GPIO pin*/
	RCC->AHB1ENR    |=  GPIOAEN;

	/* set PA2 to alternate function mode */

	GPIOA->MODER	&=~ (1U<<4);
	GPIOA->MODER	|=  (1U<<5);


	/*AFR[0] Pin 0..7*/
	/*AFR[1] Pin 8..15*/
	//GPIOA->AFR[0]   |=  (7<<8);
	GPIOA->AFR[0]   |=  (1<<8);
	GPIOA->AFR[0]   |=  (1<<9);
	GPIOA->AFR[0]   |=  (1<<10);
	GPIOA->AFR[0]	&= ~(1U<<11);

	/*********************Configure the uart module***********************/
	/*enable clock to uart2*/
	RCC->APB1ENR 	 |= UART2EN;
	/*configure bd*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	/*configure the transfer direction*/
	USART2->CR1      |= CR1_TE;
	/*enable uart module*/
	USART2->CR1      |= CR1_UE;

}

static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk+(BaudRate/2U))/BaudRate);
}

char uart2_read(void){
		/*Make sure the receive data register is empty*/
		while (!(USART2->SR & SR_RXNE)) {}   // while ((USART2->SR & SR_TXE)==0)   ma3neha mezelna 9a3din nab3thou
		/*read  data from data register*/
		return USART2->DR ;
}

void uart2_write(int ch){
	/*Make sure the transmit data register is empty*/
	while (!(USART2->SR & SR_TXE)) {}   // while ((USART2->SR & SR_TXE)==0)   ma3neha mezelna 9a3din nab3thou
	/*Write to transmit data register*/
	USART2->DR = (ch & 0xFF);

}
