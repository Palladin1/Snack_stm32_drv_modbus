/*
*********************************************************************************************************
*
*                                           LCD WH1602 INTERFACE
*
* Filename      : lcd.h
* Version       : V1.00
* Programmer(s) : Palladin
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "lcd.h"

#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "gpio_init.h"

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
//массив для русских символов
/*
const u8 convert_HD44780[256] =
{
0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,
0xAC,0xE2,0xAD,0xAE,0xAD,0xAF,0xB0,0xB1,
0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,
0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,
0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
};
*/


const u8 convert_font_to_ua[256] =
{
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA2,0xA9,/*0xAA*/0x02/**/,0xAB,0xAC,0xAD,0xAE,/*0xAF*/0x00/**/,
        0xB0,0xB1,/*0xB2*/0x04/**/,/*0xB3*/0x05/**/,0xB4,0xB5,0xB6,0xB7,0xB5,0xB9,/*0xBA*/0x03/**/,0xBB,0xBC,0xBD,0xBE,/*0xBF*/0x01/**/,
        0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
        0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
        0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
        0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
};

/*Symbol - */
const u8 symbol_ua_1[8] =
{
	0b00001010,
	0b00001110,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00001110,
	0b00000000
};
/*Symbol - */
const u8 symbol_ua_2[8] =
{
	0b00001010,
	0b00000000,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000000
};
/*Symbol - */
const u8 symbol_ua_3[8] =
{
	0b00001110,
	0b00010001,
	0b00010000,
	0b00011100,
	0b00010000,
	0b00010001,
	0b00001110,
	0b00000000
};
/*Symbol - */
const u8 symbol_ua_4[8] =
{
	0b00000000,
	0b00000000,
	0b00001110,
	0b00010001,
	0b00011100,
	0b00010001,
	0b00001110,
	0b00000000
};
/*Symbol - */
const u8 symbol_ua_5[8] =
{
	0b00000000,
	0b00001110,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00001110,
	0b00000000
};
/*Symbol - */
const u8 symbol_ua_6[8] =
{
	0b00000100,
	0b00000000,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000000
};



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
static void lcd_hw_init(void);
static void lcd_write(uint8_t data);
static void lcd_command_write(uint8_t data);
static void lcd_data_write(uint8_t data);
static void delay_ms(u32 a);

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
u8 lcd_epson_rus(u8 c){

   if  (c > 191){
           c= convert_HD44780[c - 192];
   }

return c;
}
*/

void lcd_add_some_symbol (const u8 *symbol)
{
	u8 i;
	for (i = 0; i < 8; i++) {
		delay_ms(1);
		lcd_data_write(symbol[i]);
	}
}

/*
*********************************************************************************************************
*                                          lcd_hw_init()
*
* Description : Initialize port for communication.
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

static void lcd_hw_init(void)
{
    // Enable GPIO Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // Disable jtag for correct work the PB3 and PB4 pin
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    //Initialize the LCD pins as an output
    GPIO_MULTI_INIT(LCD_PIN_RS, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_EN, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D7, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D6, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D5, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D4, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D3, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D2, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D1, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);
    GPIO_MULTI_INIT(LCD_PIN_D0, GPIO_MODE_OUTPUT2_PUSH_PULL_UP);

}


//---Функция задержки---//
static void delay_ms(u32 a)
{
    a *= 24000;
    while(a != 0)
    {
        a--;
    }
}

/*
*********************************************************************************************************
*                                                lcd_write()
*
* Description : Write data to LCD.
*
* Argument(s) : data.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
static void lcd_write(uint8_t data)
{
	(data & (1 << 7)) ? GPIO_SetBits(LCD_PIN_D7) : GPIO_ResetBits(LCD_PIN_D7);

	(data & (1 << 6)) ? GPIO_SetBits(LCD_PIN_D6) : GPIO_ResetBits(LCD_PIN_D6);

	(data & (1 << 5)) ? GPIO_SetBits(LCD_PIN_D5) : GPIO_ResetBits(LCD_PIN_D5);

	(data & (1 << 4)) ? GPIO_SetBits(LCD_PIN_D4) : GPIO_ResetBits(LCD_PIN_D4);

	(data & (1 << 3)) ? GPIO_SetBits(LCD_PIN_D3) : GPIO_ResetBits(LCD_PIN_D3);

	(data & (1 << 2)) ? GPIO_SetBits(LCD_PIN_D2) : GPIO_ResetBits(LCD_PIN_D2);

	(data & (1 << 1)) ? GPIO_SetBits(LCD_PIN_D1) : GPIO_ResetBits(LCD_PIN_D1);

	(data & (1 << 0)) ? GPIO_SetBits(LCD_PIN_D0) : GPIO_ResetBits(LCD_PIN_D0);

	GPIO_SetBits(LCD_PIN_EN);
	delay_ms(1);
	GPIO_ResetBits(LCD_PIN_EN);


	GPIO_SetBits(LCD_PIN_D7);
	GPIO_SetBits(LCD_PIN_D6);
	GPIO_SetBits(LCD_PIN_D5);
	GPIO_SetBits(LCD_PIN_D4);
	GPIO_SetBits(LCD_PIN_D3);
	GPIO_SetBits(LCD_PIN_D2);
	GPIO_SetBits(LCD_PIN_D1);
	GPIO_SetBits(LCD_PIN_D0);

}


/*
*********************************************************************************************************
*                                                lcd_command_write()
*
* Description : Write the command to LCD.
*
* Argument(s) : data.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
static void lcd_command_write(uint8_t data)
{
	GPIO_ResetBits(LCD_PIN_RS);

	lcd_write(data);
}

/*
*********************************************************************************************************
*                                                lcd_data_write()
*
* Description : Write the data to LCD.
*
* Argument(s) : data.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
static void lcd_data_write(uint8_t data)
{
	GPIO_SetBits(LCD_PIN_RS);

	lcd_write(data);
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
*                                          LcdInit()
*
* Description : Initialize a Display.
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

void LcdInit (void) {

	lcd_hw_init();

//	GPIO_ResetBits(LCD_PIN_EN);
	GPIO_ResetBits(LCD_PIN_RS);
//	GPIO_ResetBits(LCD_PIN_D7);
//	GPIO_ResetBits(LCD_PIN_D6);
//	GPIO_ResetBits(LCD_PIN_D5);
//	GPIO_ResetBits(LCD_PIN_D4);
//	GPIO_ResetBits(LCD_PIN_D3);
//	GPIO_ResetBits(LCD_PIN_D2);
//	GPIO_ResetBits(LCD_PIN_D1);
//	GPIO_ResetBits(LCD_PIN_D0);

	delay_ms(15);

	lcd_write(LCD_CMD_RESET);
	delay_ms(5);

	lcd_write(LCD_CMD_RESET);
	delay_ms(1);

	lcd_write(LCD_CMD_RESET);
	delay_ms(1);

	lcd_write(LCD_CMD_RESET | LCD_CMD_LINES_TWO |LCD_CMD_FONT_5X8);

	delay_ms(1);
	//lcd_write(LCD_CMD_DISPLAY_CLEAR);

	delay_ms(1);


	lcd_write(LCD_CMD_DISPLAY_ON | LCD_CMD_CURSOR_ON);
    delay_ms(1);

	lcd_write(LCD_CMD_DISPLAY_CLEAR);


	delay_ms(1);
	lcd_command_write(LCD_CMD_CGRAM_ADDR);
	delay_ms(1);

	lcd_add_some_symbol(symbol_ua_1);
	lcd_add_some_symbol(symbol_ua_2);
	lcd_add_some_symbol(symbol_ua_3);
	lcd_add_some_symbol(symbol_ua_4);
	lcd_add_some_symbol(symbol_ua_5);
	lcd_add_some_symbol(symbol_ua_6);

	delay_ms(1);
    lcd_command_write(LCD_CMD_DDRAM_ADDR);
}


/*
*********************************************************************************************************
*                                                LcdSetPosition()
*
* Description : Set position of cursor.
*
* Argument(s) : position row and column.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
void LcdSetPosition(uint8_t row, uint8_t column)
{
	uint8_t position = LCD_CMD_DDRAM_ADDR;

	if (row > 0)
	{
		position |= LCD_CMD_NEXT_LINE;
	}

	lcd_command_write(position | column);
}

/*
*********************************************************************************************************
*                                                LcdPrintChar()
*
* Description : Send char to LCD.
*
* Argument(s) : data.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
void LcdPrintChar(uint8_t data)
{


//	if  (data > 191)
//		lcd_data_write(convert_HD44780[data - 192]);
	if (data == '@')
		LcdSetPosition(1, 0);
	else
	    lcd_data_write( convert_font_to_ua[data]);
//	else
//		lcd_data_write(data);

}

/*
*********************************************************************************************************
*                                                LcdPrintString()
*
* Description : Send string to LCD.
*
* Argument(s) : pointer to string.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     :
*********************************************************************************************************
*/
void LcdPrintString(uint8_t * string)
{
	while (*string != 0x00)
	{
		LcdPrintChar(*string++);
	}
}
