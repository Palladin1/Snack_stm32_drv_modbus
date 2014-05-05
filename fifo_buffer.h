#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H

#include "stm32f10x.h"


//размер буфера макс. = 255
//#define GSM_SIZE_RX_BUF 100
#define FIFO_BUF_SIZE 50

unsigned char FIFO_RxBuf_Count_Get (void);
unsigned char FIFO_RxBuf_Char_Get (void);
unsigned char FIFO_RxBuf_Char_Put (u8 c);
void FIFO_RxBuf_Flush (void);

#endif // FIFO_BUFFER_H
