/**
 * @file button.h
 * @brief BUTTON interface
 */

#include "stm32f10x.h"

#ifndef _BUTTON_H
#define _BUTTON_H

//#define BUTTONS_NAMBER 8
#define BUTTONS_BOUNCE_TIME_MS 50


#define PIN_DIP_STATE GPIOB, GPIO_Pin_8
#define PIN_BUTTON1   GPIOC, GPIO_Pin_9
#define PIN_BUTTON2   GPIOA, GPIO_Pin_8
#define PIN_BUTTON3   GPIOA, GPIO_Pin_11
#define PIN_BUTTON4   GPIOA, GPIO_Pin_12
#define PIN_BUTTON5   GPIOA, GPIO_Pin_13
#define PIN_BUTTON6   GPIOA, GPIO_Pin_14
#define PIN_BUTTON7   GPIOA, GPIO_Pin_15


typedef enum btn{

	DIP_STATE = 0,
    BUTTON1,
    BUTTON2,
    BUTTON3,
    BUTTON4,
    BUTTON5,
    BUTTON6,
    BUTTON7,
    BUTTONS_NAMBER
} btn_name_t;


typedef struct {
	u32 cur_cnt;
	u8  idle_state;
	u32 press_state;
	u8  still_pressed;
	u8  synchro_flg;
} btn_t;


void ButtonInit(void);

void ButtonSkan(u32 call_period);

u8 ButtonSkanGet(btn_name_t btn_number);

void ButtonClear(void);


#endif    /* _BUTTON_H */
