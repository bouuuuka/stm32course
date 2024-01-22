#include <stdint.h>

#define PERIPH_BASE        (0x40000000UL)
#define AHB1PERIPH_OFFSET  (0x20000UL)
#define AHB1_BASE          (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET       (0x0UL)
#define GPIOA_BASE         (AHB1_BASE + GPIOA_OFFSET)

#define RCC_OFFSET         (0x3800UL)
#define RCC_BASE           (AHB1_BASE + RCC_OFFSET)

#define AHB1ENR_OFFSET     (0x30UL)
#define RCC_AHB1ENR        (*(volatile uint32_t *)(RCC_BASE + AHB1ENR_OFFSET))

#define GPIOAEN            (1U<<0)

#define MODER_OFFSET       (0x00UL)
#define GPIOA_MODER        (*(volatile uint32_t *)(GPIOA_BASE + MODER_OFFSET))

#define ODR_OFFSET         (0x14UL)
#define GPIOA_ODR          (*(volatile uint32_t *)(GPIOA_BASE + ODR_OFFSET))

#define PIN5               (1U<<5)
#define LED_PIN            PIN5

int main(void) {
    /* 1. Enable clock access to GPIOA */
    RCC_AHB1ENR |= GPIOAEN;

    /* 2. Set PA5 as an output pin */
    GPIOA_MODER |= (1U<<10);
    GPIOA_MODER &= ~(1U<<11);

    while(1)
    {
        /* Toggle LED on PA5 */
        GPIOA_ODR |= LED_PIN;

        for (int i = 0; i < 10000000; ++i);

        /* Clear LED on PA5*/

        GPIOA_ODR &= ~LED_PIN;

        for (int delay = 0; delay < 10000000; ++delay);
    }
    return 0;
}
