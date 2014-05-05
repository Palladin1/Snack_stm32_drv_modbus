#ifndef _BSP_H
#define _BSP_H

//#include "sys.h"
#include "uart.h"
//#include "delay.h"
//#include "led.h"
//#include "sensor.h"
//#include "spi.h"

#define PIN_BUZZER GPIOC, GPIO_Pin_13
#define PIN_RS485  GPIOA, GPIO_Pin_1

#define RS485_SET_MODE_TX  GPIO_SetBits(PIN_RS485)
#define RS485_SET_MODE_RX  GPIO_ResetBits(PIN_RS485)

#define BUZZER_ON   GPIO_SetBits(PIN_BUZZER)
#define BUZZER_OFF  GPIO_ResetBits(PIN_BUZZER)


int bsp_init(void);

#endif
