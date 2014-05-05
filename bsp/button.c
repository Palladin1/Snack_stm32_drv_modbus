/**
* @file led.c
* @brief LED board support package
*/
#include "button.h"

#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "gpio_init.h"

#include "portmacro.h"


static GPIO_TypeDef *button_gpio_port[] = {
    [0] = GPIOB,
    [1] = GPIOC,
    [2] = GPIOA,
    [3] = GPIOA,
    [4] = GPIOA,
    [5] = GPIOA,
    [6] = GPIOA,
    [7] = GPIOA
};

static uint16_t button_gpio_pin[] = {
    [0] = GPIO_Pin_8,
    [1] = GPIO_Pin_9,
    [2] = GPIO_Pin_8,
    [3] = GPIO_Pin_11,
    [4] = GPIO_Pin_12,
    [5] = GPIO_Pin_13,
    [6] = GPIO_Pin_14,
    [7] = GPIO_Pin_15
};


 btn_t Button[BUTTONS_NAMBER];

/**
* low level hardware initialization
*/
void ButtonInit(void)
{

    // Enable GPIO Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    //Initialize the button pins as an input
///*
    GPIO_MULTI_INIT(PIN_DIP_STATE, GPIO_MODE_INPUT_PULL_UP);
    GPIO_MULTI_INIT(PIN_BUTTON1, GPIO_MODE_INPUT_PULL_UP);

    GPIO_MULTI_INIT(PIN_BUTTON2, GPIO_MODE_INPUT_PULL_UP);
    GPIO_MULTI_INIT(PIN_BUTTON3, GPIO_MODE_INPUT_PULL_UP);
    GPIO_MULTI_INIT(PIN_BUTTON4, GPIO_MODE_INPUT_PULL_UP);
//TODO: need the comment delete below for the program work version. That is SWD pins//
    GPIO_MULTI_INIT(PIN_BUTTON5, GPIO_MODE_INPUT_PULL_UP);
    GPIO_MULTI_INIT(PIN_BUTTON6, GPIO_MODE_INPUT_PULL_UP);
    GPIO_MULTI_INIT(PIN_BUTTON7, GPIO_MODE_INPUT_PULL_UP);
//*/

   u32 i;
   for (i = 0; i < BUTTONS_NAMBER; i++) {

	  // if ((i != 5) || (i != 6)) //TODO: need the comment delete below for the program work version. That is SWD pins//
       //    GPIO_MULTI_INIT(button_gpio_port[i], button_gpio_pin[i], GPIO_MODE_INPUT_PULL_UP);

       Button[i].press_state = RESET;
       Button[i].synchro_flg = RESET;
       Button[i].idle_state  = SET;
       Button[i].still_pressed = RESET;
   }

}

void ButtonSkan (u32 call_period)
{
	u32 i;
	for (i = 0; i < BUTTONS_NAMBER; i++) {
	    if (GPIO_ReadInputDataBit(button_gpio_port[i], button_gpio_pin[i]) != Button[i].idle_state) {

	    	if (Button[i].still_pressed == RESET) {
	    		Button[i].cur_cnt += call_period;

	    		if (Button[i].cur_cnt >= BUTTONS_BOUNCE_TIME_MS) {

//	    			Button[i].synchro_flg = SET;
	    			portENTER_CRITICAL();
                    Button[i].press_state = SET;
                    portEXIT_CRITICAL();
 //                   Button[i].synchro_flg = RESET;

                    Button[i].still_pressed = SET;
	    	    }
	    	}
	    }
	    else {
	    	Button[i].cur_cnt = RESET;
	    	Button[i].still_pressed = RESET;
	    }
	}
}


u8 ButtonSkanGet (btn_name_t btn_number)
{
    u8 btn_status = 0;

//    while (Button[btn_number].synchro_flg == SET);
    portENTER_CRITICAL();
    btn_status = Button[btn_number].press_state;
    Button[btn_number].press_state = 0;
    portEXIT_CRITICAL();

return btn_status;
}

void ButtonClear (void)
{
    u16 btn_cnt;

    for ( btn_cnt = 0; btn_cnt < BUTTONS_NAMBER; btn_cnt++) {

        Button[btn_cnt].press_state = 0;
    }

}
