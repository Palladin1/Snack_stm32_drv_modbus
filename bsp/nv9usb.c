/*
*********************************************************************************************************
*
*                                            VALIDATOR INTERFACE
*
* Filename      : nv9usb.c
* Version       : V1.00
* Programmer(s) : Palladin
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "nv9usb.h"

#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "gpio_init.h"

#include "portmacro.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
validator_t    ValidatorNV9;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void validator_hw_init(void);
//static void  uart2_init(u32 baud_rate);

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          validator_hw_init()
*
* Description : Initialize a PINS for work with validator.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void validator_hw_init(void)
{

	//Enable GPIO Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//Initialize the pins
	GPIO_MULTI_INIT(VALIDATOR_STATUS,  GPIO_MODE_INPUT_PULL_UP);
	GPIO_MULTI_INIT(VALIDATOR_PULS_IN, GPIO_MODE_INPUT_PULL_UP);

	//GPIO_MULTI_INIT(VALIDATOR_INHIBIT, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
	GPIO_MULTI_INIT(VALIDATOR_INHIBIT, GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN);

	GPIO_MULTI_INIT(VALIDATOR_ESCROW,  GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
	GPIO_MULTI_INIT(VALIDATOR_PWR_PIN, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          ValidatorInit()
*
* Description : Initialize a bill count - NV9USB.
*
* Argument(s) : min and max for pulse range.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void ValidatorInit (u32 period_cnt_min, u32 period_cnt_max) {

	validator_hw_init();

	ValidatorNV9.PeriodCntMin  = RESET;
	ValidatorNV9.PeriodCntMax  = RESET;
	ValidatorNV9.PeriodCntCar  = RESET;
	ValidatorNV9.MoneyQuantity = RESET;
	ValidatorNV9.SynchroFlag   = RESET;

	ValidatorNV9.PeriodCntMin  = period_cnt_min;
	ValidatorNV9.PeriodCntMax  = period_cnt_max;

	if ((ValidatorNV9.PeriodCntMax - ValidatorNV9.PeriodCntMin) > 0) {
		GPIO_SetBits(VALIDATOR_PWR_PIN);
		//GPIO_SetBits(VALIDATOR_INHIBIT);
		GPIO_ResetBits(VALIDATOR_ESCROW);

//		VALIDATOR_INHIBIT_DISABLE();
	}
}

/*
*********************************************************************************************************
*                                                UartReadByte()
*
* Description : Receive a single byte.
*
* Argument(s) : number of UART.
*
* Return(s)   : The received byte.
*
* Caller(s)   : Application.
*
* Note(s)     : 
*********************************************************************************************************
*/
void ValidatorPulseProcessing (u32 call_period) {

	static u32 puls_with_cnt = 0;

    if (!GPIO_ReadInputDataBit(VALIDATOR_PULS_IN)) {

    	puls_with_cnt += call_period;
    }

    else if (puls_with_cnt > 0) {

    	if ((puls_with_cnt > ValidatorNV9.PeriodCntMin) && (puls_with_cnt < ValidatorNV9.PeriodCntMax)) {

//    		ValidatorNV9.SynchroFlag   = SET;
    		portENTER_CRITICAL();
    		ValidatorNV9.MoneyQuantity++;
    		portEXIT_CRITICAL();
//    		ValidatorNV9.SynchroFlag   = RESET;
    	}

    	puls_with_cnt = 0;
    }
}

/*
*********************************************************************************************************
*                                                ValidatorMoneyQuantity()
*
* Description : Get the quantity of token money .
*
* Argument(s) : none.
*
* Return(s)   : quantity money.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
u32  ValidatorMoneyQuantity (void) {

	u32 ret = 0;

	portENTER_CRITICAL();
	ret = ValidatorNV9.MoneyQuantity;

//	while (ValidatorNV9.SynchroFlag == SET) ;

	ValidatorNV9.MoneyQuantity = 0;
	portEXIT_CRITICAL();

return ret;
}
