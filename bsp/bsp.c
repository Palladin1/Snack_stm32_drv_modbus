#include "bsp.h"

#include "led.h"
#include "lcd.h"

#include "button.h"
#include "nv9usb.h"


#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#include "gpio_init.h"

void bsp_pin_init (void);


int bsp_init (void)
{
   int32_t retval = 0;

   LedInit();

/*
   UartInit(UART1, 19200);
   UartInit(UART2, 19200);





   ButtonInit();
   LcdInit();

   ValidatorInit(90, 110);

   bsp_pin_init();
*/
return retval;
}

void bsp_pin_init (void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_MULTI_INIT(PIN_BUZZER, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);

    GPIO_MULTI_INIT(PIN_RS485, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);

    /*initialization backup registers*/
    RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN; // Backup and Power interface clock enable
    PWR->CR |= PWR_CR_DBP;                                 // Disable Backup Domain write protection
}
