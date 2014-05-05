/*
*********************************************************************************************************
*
*                                            UART INTERFACE
*
* Filename      : uart.c
* Version       : V1.00
* Programmer(s) : Palladin
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "uart.h"


#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#include "gpio_init.h"
//#include "fifo_buffer.h"

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



/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void  uart1_init(u32 baud_rate);
static void  uart2_init(u32 baud_rate);

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
*                                          Uart1Init()
*
* Description : Initialize a serial port for communication.
*
* Argument(s) : baud_rate           The desire RS232 baud rate.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void  uart1_init (u32 baud_rate) {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitTypeDef uart1_gpio;
	uart1_gpio.GPIO_Pin = GPIO_Pin_10;                               /* UART1 RX pin */
	uart1_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &uart1_gpio);

	uart1_gpio.GPIO_Pin = GPIO_Pin_9;                                /* UART1 TX pin */
	uart1_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	uart1_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &uart1_gpio);

    USART_InitTypeDef uart1;
    uart1.USART_BaudRate = baud_rate;
    uart1.USART_WordLength = USART_WordLength_8b;
    uart1.USART_StopBits = USART_StopBits_1;
    uart1.USART_Parity = USART_Parity_No;
    uart1.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    uart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USART1, &uart1);

    #if UART1_RX_INTERRAPT_ENABLE
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        NVIC_EnableIRQ(USART1_IRQn);
    #endif
    #if UART1_TX_INTERRAPT_ENABLE
        USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
        NVIC_EnableIRQ(USART1_IRQn);
    #endif

    USART_Cmd(USART1, ENABLE);
}

/*
*********************************************************************************************************
*                                          Uart2Init()
*
* Description : Initialize a serial port for communication.
*
* Argument(s) : baud_rate           The desire RS232 baud rate.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void  uart2_init (u32 baud_rate) {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitTypeDef uart2_gpio;
	uart2_gpio.GPIO_Pin = GPIO_Pin_3;                               /* UART2 RX pin */
	uart2_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &uart2_gpio);

	uart2_gpio.GPIO_Pin = GPIO_Pin_2;                                /* UART2 TX pin */
	uart2_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	uart2_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &uart2_gpio);

    USART_InitTypeDef uart2;
    uart2.USART_BaudRate = baud_rate;
    uart2.USART_WordLength = USART_WordLength_8b;
    uart2.USART_StopBits = USART_StopBits_1;
    uart2.USART_Parity = USART_Parity_No;
    uart2.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    uart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USART2, &uart2);

    #if UART2_RX_INTERRAPT_ENABLE
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
        NVIC_EnableIRQ(USART2_IRQn);
    #endif
    #if UART2_TX_INTERRAPT_ENABLE
        USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
        NVIC_EnableIRQ(USART2_IRQn);
    #endif

    USART_Cmd(USART2, ENABLE);
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
*                                          UartInit()
*
* Description : Initialize a serial port for communication.
*
* Argument(s) : baud_rate           The desire RS232 baud rate.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void UartInit (uart_t number_uart, u32 baud_rate) {

	switch (number_uart)
	{
		case UART1: uart1_init(baud_rate);
		break;
		case UART2: uart2_init(baud_rate);
		break;
//		case UART3: Uart3Init(baud_rate);
//		break;
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
u8  UartReadByte (uart_t number_uart) {

	u8 data;
	if (number_uart == UART1) {
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
            data = (USART_ReceiveData(USART1));
//        USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
	if (number_uart == UART2) {
		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	        data = (USART_ReceiveData(USART2));
//	    USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
return (data);
}

/*
*********************************************************************************************************
*                                                UartWrByte()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : tx_byte     The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  UartWrByte (uart_t number_uart, u8 c) {

	if (number_uart == UART1) {
	    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	        USART_SendData(USART1, c);
	}

	if (number_uart == UART2) {
	    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	        USART_SendData(USART2, c);
	}
}


/*
*********************************************************************************************************
*                                                UartWrStr()
*
* Description : Transmits a string.
*
* Argument(s) : p_str       Pointer to the string that will be transmitted.
*
* Caller(s)   : Application.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  UartWrStr (uart_t number_uart, u8  *p_str) {
    
    while (1) {
        if (!(*p_str)) {
            break;
        }
        UartWrByte(number_uart, *(p_str++));
    }
    
}


#if UART1_RX_INTERRAPT_ENABLE || UART1_TX_INTERRAPT_ENABLE
void  USART1_IRQHandler (void) {
	unsigned char z;
    #if UART1_RX_INTERRAPT_ENABLE
      if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    	  /* Read one byte from the receive data register */
    	  z = USART_ReceiveData(USART1);
      }
    #endif
    #if UART1_TX_INTERRAPT_ENABLE
      if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {

      }
    #endif
}
#endif


#if UART2_RX_INTERRAPT_ENABLE || UART2_TX_INTERRAPT_ENABLE
void USART2_IRQHandler (void) {
	unsigned char z;
    #if UART2_RX_INTERRAPT_ENABLE
      if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
    	  /* Read one byte from the receive data register */
    	  z = USART_ReceiveData(USART2);
    	  FIFO_RxBuf_Char_Put(z);
      }
    #endif
    #if UART2_TX_INTERRAPT_ENABLE
      if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET) {

      }
    #endif
}
#endif
