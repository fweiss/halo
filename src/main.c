// #include "stm32f4xx.h"

#define PERIPH_BASE        ((unsigned int)0x40000000)
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x00020000)
#define RCC_BASE           (AHB1PERIPH_BASE + 0x3800)
#define RCC_AHB1ENR        (*(volatile unsigned int *)(RCC_BASE + 0x30))

#define GPIOC_BASE         (AHB1PERIPH_BASE + 0x0800)
#define GPIOC_MODER        (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_IDR          (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_ODR          (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

#define GPIOB_BASE         (AHB1PERIPH_BASE + 0x0400)
#define GPIOB_MODER        (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR          (*(volatile unsigned int *)(GPIOB_BASE + 0x14))

#define LED_PORT              GPIOB
#define LED_PORT_RCC_EN       0x2u 
#define GPIO_MODE_MASK       ~0x3u
#define GPIO_MODE_OUTPUT      0x1u

#define GREEN_LED_PIN         0u
#define BLUE_LED_PIN          7u
#define RED_LED_PIN           14u
#define FLASH_LED             BLUE_LED_PIN


void delayMs( unsigned delay );

int main(void)
{
    RCC_AHB1ENR |= LED_PORT_RCC_EN ; // enable for PORT B
    //LED_PORT->MODER &= GPIO_MODE_MASK << FLASH_LED ;
    //LED_PORT->MODER |= GPIO_MODE_OUTPUT << FLASH_LED ;
      GPIOB_MODER |= 0x4000;  // blue LED PB7
      GPIOB_MODER |= 0x1;  // green LED PB0
      GPIOB_ODR |= 0x1; // green LED ODR
      GPIOB_MODER |=  0x1 << 28; // red LED PB14
      GPIOB_ODR |= 0x1 <<14; // RED LED ODR
      //GPIOB_BSRR |= 0x4000; // 7th pin 
    // connected to pull up resistor -- when we press button , it goes low
        //B1 user button is connected to PC13 - i.e. blue button
      // Enable clock to PC13 i.e. Port C
      RCC_AHB1ENR |=  0x1 << 2;
      //GPIOC_MODER |=     //Input mode PC13- 13th pin 0
       // by default pins are input only
      GPIOC_MODER |=  0;

    for(;;) {
        // pressed blue button
        if( (GPIOC_IDR & (1<<13)) ) // PC13
            {
                GPIOB_ODR |= 0x1 << FLASH_LED ;
            }
            else
            {
                GPIOB_ODR &= ~(0x1 << FLASH_LED) ;
            }
    }

    return 0 ;
}

void delayMs( unsigned delay )
{
    for( volatile unsigned d = delay; d > 0; d--)
    {
        for( volatile int i = 0; i < 3195; i++ )
        {
        }
    }
}
