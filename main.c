/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*
* Filename      : main.c
* Version       : V1.00
* Programmer(s) : Palladin
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include <includes.h>

/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/




//#define REG_INPUT_START 1001
//#define REG_INPUT_NREGS 4


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/
xQueueHandle     xDataGetQueue;

//static USHORT   usRegInputStart = REG_INPUT_START;
//static USHORT   usRegInputBuf[REG_INPUT_NREGS];

//xSemaphoreHandle xCamDataSemaphoreHandle;


 u8 DataBuf[30];

 //snack_t Snack;

 u8 name0[16] = "Ñí³êåðñ";
 u8 name7[16] = "Mars";
 u8 name1[16] = "Snikers";

 u16 gLedCnt = 10;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
//void vTask3( void *pvParameters );

void TIM2_IRQHandler(void);
int timer_4_init ( void );
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main( void )
{

	bsp_init();

	//xDataGetQueue  = xQueueCreate(5, sizeof(cmd_t *));
	xDataGetQueue  = xQueueCreate(5, 6);


	xTaskCreate( vTask1, (signed char*) "Task 1", configMINIMAL_STACK_SIZE + 300, NULL, 1, NULL );
	xTaskCreate( vTask2, (signed char*) "Task 2", configMINIMAL_STACK_SIZE + 300, NULL, 1, NULL );
//	xTaskCreate( vTask3, (signed char*) "Task 3", configMINIMAL_STACK_SIZE + 100, NULL, 1, NULL );

	/* Çàïóñê øåäóëåðà, ïîñëå ÷åãî çàäà÷è çàïóñòÿòñÿ íà âûïîëíåíèå. */
	vTaskStartScheduler();



	for( ;; );
return (0);
}

/*
*********************************************************************************************************
*                                          LedInit()
*
* Description : Init the ports for leds
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : main()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void vTask1( void *pvParameters )
{
	  static u32 cnt = 50;
	  u32 fl = 0;

	  u8 er = 0;

	  timer_4_init();

	    for( ;; )
	    {
	        cnt--;
	    	if (cnt == 0) {
	    		LedToggle(LED_STATUS);

	    		cnt = gLedCnt;
	    		//USART_SendData(USART1, 'A');
	    	    if ( fl == 0 ) {
	    	    	u8 i;
	    	    	//for ( i = 1; i < 5; i++) {

	    		     //   er = eMBMasterReqWriteCoil( 1, 1, 0xFF00, (-1) );


	    			    //MB_MRE_NO_ERR,                  /*!< no error. */
	    			    //MB_MRE_NO_REG,                  /*!< illegal register address. */
	    			    //MB_MRE_ILL_ARG,                 /*!< illegal argument. */
	    			    //MB_MRE_REV_DATA,                /*!< receive data error. */
	    			    //MB_MRE_TIMEDOUT,                /*!< timeout error occurred. */
	    			    //MB_MRE_MASTER_BUSY,             /*!< master is busy now. */
	    			    //MB_MRE_EXE_FUN                  /*!< execute function error. */
	    		//	    if ( er == MB_MRE_NO_ERR )//|| er == MB_MRE_MASTER_BUSY || er == MB_MRE_REV_DATA || er == MB_MRE_EXE_FUN)
	    			//	    break;
	    		   // }

	    	    if ( i == 5 )
	    	    	gLedCnt = 2;
	    	   	}

	    	    fl = 1;
	        }

    	//ValidatorPulseProcessing(5 / portTICK_RATE_MS);
    	//ButtonSkan(5 / portTICK_RATE_MS);

        vTaskDelay(100 / portTICK_RATE_MS);
    }

    vTaskDelete (NULL);
}



void vTask2( void *pvParameters )
{


//	extern uint16_t   ucSDiscInBuf[]  ;
//	extern uint16_t   ucSCoilBuf[]    ;
//	extern uint16_t   usSRegInBuf[]   ;
//	extern uint16_t   usSRegHoldBuf[] ;

//	extern uint16_t   usMRegInBuf[16][];

	eMBErrorCode    eStatus;
	uint16_t errorCount = 0;

	//eStatus = eMBInit( MB_RTU, 10, UART1, 19200, 0 );
	//vMBMasterSetDestAddress( 1 );
	//eStatus = eMBMasterInit(MB_RTU, UART1, 19200,  MB_PAR_NONE);

	/* Enable the Modbus Protocol Stack. */
	//eStatus = eMBEnable(  );
	//eStatus = eMBMasterEnable();

	if ( eStatus != MB_ENOERR) {

	}

	eMBMasterReqErrCode    errorCode = MB_MRE_NO_ERR;

	USHORT  usModbusUserData[253];
	usModbusUserData[1] = 10;

	//eMBMasterReqWriteCoil( 1, 1, 0xFF00, (-1) );

    for( ;; )
    {

    	//( void )eMBPoll(  );
    	//( void )eMBMasterPoll(  );

    	//if ( eMBMasterPoll() == MB_MRE_TIMEDOUT )
    	//	gLedCnt = 2;

    	/* Here we simply count the number of poll cycles. */
    	//usSRegInBuf[0]++;
    	//if ( usSRegInBuf[0] == 65535)
    	//    usSRegInBuf[0] = 0;

//    	if ( usSRegInBuf[1] > 0)
//    		gLedCnt = usSRegInBuf[1];


    	//usSRegInBuf[1] = 'Z';
    	//usSRegInBuf[2] = 44;

    	//errorCode = eMBMasterReqReadInputRegister(10,100,4, (-1));

    	if (errorCode != MB_MRE_NO_ERR) {
    	    errorCount++;
    	}

     	vTaskDelay(100 / portTICK_RATE_MS);
    }

    vTaskDelete (NULL);
}


/*
void vTask3( void *pvParameters )
{
#define RXBUFF_SIZE 20

//    static u8 rx_buff[RXBUFF_SIZE];
//    static u8 cnt = 0;

//    message_t Message;

//   RS485_SET_MODE_RX;

    for( ;; )
    {

   	    if ( FIFO_RxBuf_Count_Get() > 0 ) {
 //   		 rx_buff[cnt] = FIFO_RxBuf_Char_Get();
 //   		 UartWrByte(UART1, rx_buff[cnt]);


    	}

        vTaskDelay(500 / portTICK_RATE_MS);
   }

    vTaskDelete (NULL);
}
*/


///////////////
/*
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    return MB_ENOREG;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
*/



#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "stm32f10x_tim.h"
#include "misc.h"

#include "led.h"

int timer_4_init ( void ) {

	uint16_t PrescalerValue = 0;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//====================================Ê±ÖÓ³õÊ¼»¯===========================
	//Ê¹ÄÜ¶¨Ê±Æ÷3Ê±ÖÓ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//====================================¶¨Ê±Æ÷³õÊ¼»¯===========================
	//¶¨Ê±Æ÷Ê±¼ä»ùÅäÖÃËµÃ÷
	//HCLKÎª72MHz£¬APB1¾­¹ý2·ÖÆµÎª36MHz
	//TIM3µÄÊ±ÖÓ±¶ÆµºóÎª72MHz£¨Ó²¼þ×Ô¶¯±¶Æµ,´ïµ½×î´ó£©
	//TIM3µÄ·ÖÆµÏµÊýÎª3599£¬Ê±¼ä»ùÆµÂÊÎª72 / (1 + Prescaler) = 20KHz,»ù×¼Îª50us
	//TIM×î´ó¼ÆÊýÖµÎªusTim1Timerout50u

	//PrescalerValue = (uint16_t) (SystemCoreClock / 20000) - 1;
	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;

	//¶¨Ê±Æ÷1³õÊ¼»¯
	//TIM_TimeBaseStructure.TIM_Period = (uint16_t) usTim1Timerout50us;
	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//Ô¤×°ÔØÊ¹ÄÜ
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//====================================ÖÐ¶Ï³õÊ¼»¯===========================
	//ÉèÖÃNVICÓÅÏÈ¼¶·Ö×éÎªGroup2£º0-3ÇÀÕ¼Ê½ÓÅÏÈ¼¶£¬0-3µÄÏìÓ¦Ê½ÓÅÏÈ¼¶
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//Çå³ýÒç³öÖÐ¶Ï±êÖ¾Î»
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//¶¨Ê±Æ÷3Òç³öÖÐ¶Ï¹Ø±Õ
	//TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	//¶¨Ê±Æ÷3½ûÄÜ
	//TIM_Cmd(TIM2, DISABLE);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);

	//TIM_SetAutoreload(TIM2, (uint16_t) (SystemCoreClock / 36000) - 1);

	TIM_Cmd(TIM2, ENABLE);

	return TRUE;

}

void TIM2_IRQHandler(void)
{


	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
LedToggle(LED_BUTTON1);

LedToggle(LED_BUTTON4);

		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	     //ÇåÖÐ¶Ï±ê¼Ç
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	 //Çå³ý¶¨Ê±Æ÷T3Òç³öÖÐ¶Ï±êÖ¾Î»
		//TIM_SetCounter(TIM2, 0);
	}
//	rt_interrupt_leave();
}





