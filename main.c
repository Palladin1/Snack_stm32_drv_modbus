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

 u8 name0[16] = "Снікерс";
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


	xTaskCreate( vTask1, (signed char*) "Task 1", configMINIMAL_STACK_SIZE + 150, NULL, 1, NULL );
	xTaskCreate( vTask2, (signed char*) "Task 2", configMINIMAL_STACK_SIZE + 300, NULL, 1, NULL );
//	xTaskCreate( vTask3, (signed char*) "Task 3", configMINIMAL_STACK_SIZE + 100, NULL, 1, NULL );

	/* Запуск шедулера, после чего задачи запустятся на выполнение. */
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

	    		        er = eMBMasterReqWriteCoil( 1, 1, 0xFF00, (-1) );


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
	eStatus = eMBMasterInit(MB_RTU, UART1, 19200,  MB_PAR_NONE);

	/* Enable the Modbus Protocol Stack. */
	//eStatus = eMBEnable(  );
	eStatus = eMBMasterEnable();

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

    	if ( eMBMasterPoll() == MB_MRE_TIMEDOUT )
    		gLedCnt = 2;

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

     	vTaskDelay(1 / portTICK_RATE_MS);
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
