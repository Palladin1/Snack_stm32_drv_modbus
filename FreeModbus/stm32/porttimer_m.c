/*
 * FreeModbus Libary: STM32 Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer_m.c,v 1.60 2013/08/13 15:07:05 Armink add Master Functions$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

#include "stm32f10x_tim.h"
#include "misc.h"

#include "led.h"


#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
/* ----------------------- Variables ----------------------------------------*/
static USHORT usT35TimeOut50us;
static USHORT usPrescalerValue = 0;

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR(void);

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortTimersInit(USHORT usTimeOut50us)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//====================================К±ЦУіхКј»Ї===========================
	//К№ДЬ¶ЁК±Жч2К±ЦУ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//====================================¶ЁК±ЖчіхКј»Ї===========================
	//¶ЁК±ЖчК±јд»щЕдЦГЛµГч
	//HCLKОЄ72MHzЈ¬APB1ѕ­№э2·ЦЖµОЄ36MHz
	//TIM2µДК±ЦУ±¶ЖµєуОЄ72MHzЈЁУІјюЧФ¶Ї±¶Жµ,ґпµЅЧоґуЈ©
	//TIM2µД·ЦЖµПµКэОЄ3599Ј¬К±јд»щЖµВКОЄ72 / (1 + Prescaler) = 20KHz,»щЧјОЄ50us
	//TIMЧоґујЖКэЦµОЄusTim1Timerout50u	
	usPrescalerValue = (uint16_t) (SystemCoreClock / 20000) - 1;
	//±ЈґжT35¶ЁК±ЖчјЖКэЦµ
	usT35TimeOut50us = usTimeOut50us;

	//Ф¤Ч°ФШК№ДЬ
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//====================================ЦР¶ПіхКј»Ї===========================
	//ЙиЦГNVICУЕПИј¶·ЦЧйОЄGroup2Јє0-3ЗАХјКЅУЕПИј¶Ј¬0-3µДПмУ¦КЅУЕПИј¶
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//ЗеіэТзіцЦР¶П±кЦѕО»
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//¶ЁК±Жч3ТзіцЦР¶П№Ш±Х
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	//¶ЁК±Жч3ЅыДЬ
	TIM_Cmd(TIM2, DISABLE);
	return TRUE;
}

void vMBMasterPortTimersT35Enable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_T35);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t) usT35TimeOut50us;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersConvertDelayEnable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_CONVERT_DELAY);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(MB_MASTER_DELAY_MS_CONVERT * 1000 / 50);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersRespondTimeoutEnable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_RESPOND_TIMEOUT);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(MB_MASTER_TIMEOUT_MS_RESPOND * 1000 / 50);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersDisable()
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, DISABLE);
}

void prvvTIMERExpiredISR(void)
{
	(void) pxMBMasterPortCBTimerExpired();
}

void TIM2_IRQHandler(void)
{
	LedToggle(LED_BUTTON1);

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	     //���жϱ���
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	 //������ʱ��TIM2�����жϱ�־λ
		prvvTIMERExpiredISR();
	}
}

#endif
