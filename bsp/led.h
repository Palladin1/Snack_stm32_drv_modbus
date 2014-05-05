/**
 * @file led.h
 * @brief LED interface
 */

#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "gpio_init.h"



/**
 * @addtogroup kite
 * @{
 */

/**
 * @addtogroup BSP
 * @{
 */

#define NUMBER_LED 2
#define	LED_STATUS   GPIOC, GPIO_Pin_9
//#define	LED_STATUS   GPIOB, GPIO_Pin_2
#define	LED_BUTTON1  GPIOC, GPIO_Pin_8
#define	LED_BUTTON2  GPIOC, GPIO_Pin_7
#define	LED_BUTTON3  GPIOC, GPIO_Pin_6
#define	LED_BUTTON4  GPIOB, GPIO_Pin_15
#define	LED_BUTTON5  GPIOB, GPIO_Pin_14
#define	LED_BUTTON6  GPIOB, GPIO_Pin_13
#define LED_BUTTON7  GPIOB, GPIO_Pin_12


/**
 * @brief Initialize LEDs
 *
 * @param None
 * @return None
 */
void LedInit(void);

/**
 * @brief Turn on LED
 *
 * @param led The LED number
 * @return None
 */
void LedOn(GPIO_TypeDef * gpiox, uint16_t gpion);

/**
 * @brief Turn off LED
 *
 * @param led The LED number
 * @return None
 */
void LedOff(GPIO_TypeDef * gpiox, uint16_t gpion);

/**
 * @brief Toogle LED
 *
 * @param led The LED number
 * @return None
 */
void LedToggle(GPIO_TypeDef * gpiox, uint16_t gpion);


/** @} */

/** @} */

#endif /* _LED_H */
