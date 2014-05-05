#ifndef GPIO_INIT_H
#define GPIO_INIT_H

#define GPIO_MODE_INPUT_ANALOG                          0x00
#define GPIO_MODE_INPUT_FLOATING                        0x04
#define GPIO_MODE_INPUT_PULL_UP_DOWN                    0x08
#define GPIO_MODE_OUTPUT2_PUSH_PULL                     0x02
#define GPIO_MODE_OUTPUT2_OPEN_DRAIN                    0x06
#define GPIO_MODE_OUTPUT2_ALT_PUSH_PULL                 0x0A
#define GPIO_MODE_OUTPUT2_ALT_OPEN_DRAIN                0x0E
#define GPIO_MODE_OUTPUT10_PUSH_PULL                    0x01
#define GPIO_MODE_OUTPUT10_OPEN_DRAIN                   0x05
#define GPIO_MODE_OUTPUT10_ALT_PUSH_PULL                0x09
#define GPIO_MODE_OUTPUT10_ALT_OPEN_DRAIN               0x0D
#define GPIO_MODE_OUTPUT50_PUSH_PULL                    0x03
#define GPIO_MODE_OUTPUT50_OPEN_DRAIN                   0x07
#define GPIO_MODE_OUTPUT50_ALT_PUSH_PULL                0x0B
#define GPIO_MODE_OUTPUT50_ALT_OPEN_DRAIN               0x0F
#define GPIO_MODE_RESERVED                              0x0C

#define GPIO_MODE_INPUT_PULL_DOWN                       0x80
#define GPIO_MODE_INPUT_PULL_UP                         0x81
#define GPIO_MODE_OUTPUT2_PUSH_PULL_DOWN                0x20
#define GPIO_MODE_OUTPUT2_PUSH_PULL_UP                  0x21
#define GPIO_MODE_OUTPUT2_OPEN_DRAIN_DOWN               0x60
#define GPIO_MODE_OUTPUT2_OPEN_DRAIN_UP                 0x61
#define GPIO_MODE_OUTPUT10_PUSH_PULL_DOWN               0x10
#define GPIO_MODE_OUTPUT10_PUSH_PULL_UP                 0x11
#define GPIO_MODE_OUTPUT10_OPEN_DRAIN_DOWN              0x50
#define GPIO_MODE_OUTPUT10_OPEN_DRAIN_UP                0x51
#define GPIO_MODE_OUTPUT50_PUSH_PULL_DOWN               0x30
#define GPIO_MODE_OUTPUT50_PUSH_PULL_UP                 0x31
#define GPIO_MODE_OUTPUT50_OPEN_DRAIN_DOWN              0x70
#define GPIO_MODE_OUTPUT50_OPEN_DRAIN_UP                0x71

#define _INIT_PIN_CRL(PORT,PIN_NUM,PIN_MODE)    PORT->CRL = (PORT->CRL &(~((uint32_t)0x0F<<(((PIN_NUM) & 0x07)<<2)))) | (((uint32_t)(PIN_MODE)&0x0F)<<(((PIN_NUM) & 0x07)<<2))
#define _INIT_PIN_CRH(PORT,PIN_NUM,PIN_MODE)    PORT->CRH = (PORT->CRH &(~((uint32_t)0x0F<<(((PIN_NUM) & 0x07)<<2)))) | (((uint32_t)(PIN_MODE)&0x0F)<<(((PIN_NUM) & 0x07)<<2))
#define _INIT_PIN(PORT,PIN_NUM,PIN_MODE)        ((PIN_NUM)<8)? (_INIT_PIN_CRL(PORT,PIN_NUM,PIN_MODE)):(_INIT_PIN_CRH(PORT,PIN_NUM,PIN_MODE))
#define _GPIO_SET_RESET(PORT,PIN_NUM,PIN_MODE) ((PIN_MODE)==0x01)? (PORT->BSRR = (uint32_t)0x01<<(PIN_NUM)) : (PORT->BRR=(uint32_t)0x01<<(PIN_NUM))

#define _GPIO_INIT_PIN(PORT,PIN_NUM,PIN_MODE)           ((PIN_MODE)<0x10)? (_INIT_PIN(PORT,PIN_NUM,PIN_MODE))   :\
                (_GPIO_SET_RESET(PORT,PIN_NUM,(PIN_MODE)&0x01), _INIT_PIN(PORT,PIN_NUM,(PIN_MODE)>>4))

#define GPIO_INIT_PIN(PORT,PIN_NUM,PIN_MODE)    _GPIO_INIT_PIN(PORT,PIN_NUM,PIN_MODE)

#define _BITSET(bits) ((uint16_t)((bits % 010) | (bits / 010 % 010) << 1 | (bits / 0100 % 010) << 2 | \
  (bits / 01000 % 010) << 3 | (bits / 010000 % 010) << 4 | (bits / 0100000 % 010) << 5 | (bits / 01000000 % 010) << 6 | \
  (bits / 010000000 % 010) << 7 | (bits / 0100000000 % 010) << 8 | (bits / 01000000000 % 010) << 9 | (bits / 010000000000 % 010) << 10 | \
  (bits / 0100000000000 % 010) << 11 | (bits / 01000000000000 % 010) << 12 | (bits / 010000000000000 % 010) << 13 | \
  (bits / 0100000000000000 % 010) << 14 | (bits / 01000000000000000 % 010) << 15))

#define BIN(bits) _BITSET(0##bits)

#define _BIT_IN_MASK(MASK,BIT)  ((MASK) & (1<<(BIT)))? (uint32_t)1<<((BIT)<<2) : 0

#define __MULTI_INIT(PORT,PIN_MASK,PIN_MODE,REG)        (PORT->REG = (PORT->REG &((uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),7))|\
        (uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),6))|(uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),5))|\
        (uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),4))|(uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),3))|\
        (uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),2))|(uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),1))|\
        (uint32_t)0x0F*(_BIT_IN_MASK(~(PIN_MASK),0))))|((uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,7))|\
        (uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,6))|(uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,5))|\
        (uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,4))|(uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,3))|\
        (uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,2))|(uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,1))|\
        (uint32_t)(PIN_MODE)*(_BIT_IN_MASK(PIN_MASK,0))))

#define _MULTI_INIT(PORT,PIN_MASK,PIN_MODE) (((PIN_MASK) & 0x00FF)&&((PIN_MASK) & 0xFF00))? (__MULTI_INIT(PORT,(PIN_MASK)>>8,PIN_MODE,CRH),__MULTI_INIT(PORT,(PIN_MASK)&0xFF,PIN_MODE,CRL)):\
                                                                (((PIN_MASK) & 0x00FF)? __MULTI_INIT(PORT,(PIN_MASK)&0xFF,PIN_MODE,CRL) : __MULTI_INIT(PORT,(PIN_MASK)>>8,PIN_MODE,CRH))
#define _MULTI_SET_RESET(PORT,PIN_MASK,PIN_MODE) ((PIN_MODE)==0x01)? (PORT->BSRR = (uint32_t)(PIN_MASK)) : (PORT->BRR=(uint32_t)(PIN_MASK))

#define _GPIO_MULTI_INIT(PORT,PIN_MASK,PIN_MODE) ((PIN_MODE)<0x10)? (_MULTI_INIT(PORT,PIN_MASK,PIN_MODE)) : \
		                                         (_MULTI_SET_RESET(PORT,PIN_MASK,(PIN_MODE)&0x01), _MULTI_INIT(PORT,PIN_MASK,((PIN_MODE)>>4)&0x0F))

//#define _GPIO_MULTI_INIT(PORT,PIN_MASK,PIN_MODE) ((PIN_MODE)<0x10)? (_MULTI_INIT(PORT,PIN_MASK,PIN_MODE) (RCC->APB2ENR |= RCC_APB2Periph_/**/PORT)) : (_MULTI_SET_RESET(PORT,PIN_MASK,(PIN_MODE)&0x01), _MULTI_INIT(PORT,PIN_MASK,((PIN_MODE)>>4)&0x0F))


//#define GPIO_MULTI_INIT(PORT,PIN_MASK,PIN_MODE)  _GPIO_MULTI_INIT(PORT,PIN_MASK,PIN_MODE)
#define GPIO_MULTI_INIT(...) _GPIO_MULTI_INIT(__VA_ARGS__)


#define _GPIO_SET(PORT, PIN)    PORT->BRR = PIN
#define _GPIO_ISSET(PORT, PIN)  (PORT->IDR & PIN)
#define _GPIO_RESET(PORT, PIN)  PORT->BRR  = PIN
#define _GPIO_TOGGLE(PORT, PIN) PORT->ODR ^= PIN

//соотв макросы работы с портом
#define GPIO_SET(PIN_DESC)    _GPIO_SET(PIN_DESC)
#define GPIO_RESET(PIN_DESC)  _GPIO_RESET(PIN_DESC)
#define GPIO_TOGGLE(PIN_DESC) _GPIO_TOGGLE(PIN_DESC)
#define GPIO_ISSET(PIN_DESC)  _GPIO_ISSET(PIN_DESC)
/*
//#define _GPIO_SET(PORT, PIN)    PORT->BSRR = (1 << PIN)
#define _GPIO_ISSET(PORT, PIN)  (PORT->IDR & (1 << PIN))
#define _GPIO_RESET(PORT, PIN)  PORT->BRR  = (1 << PIN)
#define _GPIO_TOGGLE(PORT, PIN) PORT->ODR ^= (1 << PIN)

//соотв макросы работы с портом
#define GPIO_SET(PIN_DESC)    _GPIO_SET(PIN_DESC)
#define GPIO_RESET(PIN_DESC)  _GPIO_RESET(PIN_DESC)
#define GPIO_TOGGLE(PIN_DESC) _GPIO_TOGGLE(PIN_DESC)
#define GPIO_ISSET(PIN_DESC)  _GPIO_ISSET(PIN_DESC)

#define _GPIO_BB(PORT, PIN, MODE, OUT) (*(uint32_t*)(PERIPH_BB_BASE + ((uint32_t)&(GPIO##PORT->ODR) -  PERIPH_BASE)*32 + PIN*4))
// макрос работы с портом через bit-bang
#define GPIO_BB(PIN_DESC) _GPIO_BB(PIN_DESC)
*/


//Example: GPIO_INIT_PIN(GPIOA,3,GPIO_MODE_INPUT_PULL_DOWN);
//Example2: GPIO_MULTI_INIT(GPIOA,BIN(1010101010101010),GPIO_MODE_OUTPUT50_OPEN_DRAIN_DOWN);
#endif
