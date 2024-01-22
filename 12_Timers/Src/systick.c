#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL	16000
#define CTRL_ENABLE			(1U<<0)
#define CTRL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)

void systick_Delays_Ms(int delay) {

	/*Reload with number of clocks per milliseconds*/
	SysTick->LOAD |= SYSTICK_LOAD_VAL ;

	/*clear sysTick current value register */
	SysTick->VAL = 0 ;

	/*enable systick and select internal clk src*/
	SysTick->CTRL |= CTRL_ENABLE | CTRL_CLKSRC ;

	for (int i =0;i< delay;i++){
		/*wait to count flag is set*/
		while (!(SysTick->CTRL & CTRL_COUNTFLAG )) {}
	}

	SysTick->CTRL=0;
}
