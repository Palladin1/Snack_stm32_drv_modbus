/**
* @file led.h
* @brief LED board support package
*/


//#include "stm32f10x.h"

#include "led.h"

//#include "gpio_init.h"

/**
* low level hardware initialization
*/
static void led_hw_init(void)
{


    // Enable GPIO Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //Initialize the LED pins as an output
//    GPIO_MULTI_INIT(LED_STATUS);
    GPIO_MULTI_INIT(LED_STATUS,  GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LED_BUTTON1, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
   // GPIO_MULTI_INIT(LED_BUTTON2, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
   // GPIO_MULTI_INIT(LED_BUTTON3, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
    GPIO_MULTI_INIT(LED_BUTTON4, GPIO_MODE_OUTPUT2_OPEN_DRAIN);
   // GPIO_MULTI_INIT(LED_BUTTON5, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
   // GPIO_MULTI_INIT(LED_BUTTON6, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
   // GPIO_MULTI_INIT(LED_BUTTON7, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);
}

void LedInit(void)
{
    led_hw_init();

}

void LedOn(GPIO_TypeDef * gpiox, uint16_t gpion)
{
//    if (led < LED_MAX_NUM)
        GPIO_SetBits(gpiox, gpion);
}

void LedOff(GPIO_TypeDef * gpiox, uint16_t gpion)
{
//    if (led < LED_MAX_NUM)
        GPIO_ResetBits(gpiox, gpion);
//        GPIO_SET(LED_BUTTON7);
}

void LedToggle(GPIO_TypeDef * gpiox, uint16_t gpion)
{
//    if (led < LED_MAX_NUM)
	gpiox->ODR ^= gpion;
}
