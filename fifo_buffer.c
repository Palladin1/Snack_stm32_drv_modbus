#include "fifo_buffer.h"
#include "portmacro.h"



//unsigned char GSM_TxBuf[GSM_SIZE_TX_BUF];
//unsigned char GSM_TxBuf_tail  = 0;
//unsigned char GSM_TxBuf_head  = 0;
//unsigned char GSM_TxBuf_count = 0;

volatile unsigned char RxBuf[FIFO_BUF_SIZE];
volatile unsigned char RxBuf_tail  = 0;
volatile unsigned char RxBuf_head  = 0;
volatile unsigned char RxBuf_count = 0;

//возвращает колличество символов находящихся в приемном буфере
unsigned char FIFO_RxBuf_Count_Get (void) {

    return RxBuf_count;
}

//"очищает" приемный буфер
void FIFO_RxBuf_Flush (void) {

//    portENTER_CRITICAL();
    RxBuf_tail = 0;
    RxBuf_head = 0;
    RxBuf_count = 0;
//	portEXIT_CRITICAL();
}

//чтение буфера
unsigned char FIFO_RxBuf_Char_Get (void) {

    unsigned char sym;
	portENTER_CRITICAL();
    if (RxBuf_count > 0) {                                          //если приемный буфер не пустой
        sym = RxBuf[RxBuf_head];                                 //прочитать из него символ
        RxBuf_count--;                                               //уменьшить счетчик символов
        RxBuf_head++;                                                //инкрементировать индекс головы буфера

        if (RxBuf_head == FIFO_BUF_SIZE) {
		    RxBuf_head = 0;
        }
    portEXIT_CRITICAL();
    return sym;                                                      //вернуть прочитанный символ
    }

return (-1);
}


//Запись в буфер
unsigned char FIFO_RxBuf_Char_Put (unsigned char c) {
    
	if (RxBuf_count < FIFO_BUF_SIZE) {                          //если в буфере еще есть место
	    
//		portENTER_CRITICAL();
        RxBuf[RxBuf_tail] = c;                               //считать символ из UDR в буфер
        RxBuf_tail++;                                            //увеличить индекс хвоста приемного буфера

        if (RxBuf_tail == FIFO_BUF_SIZE) {
	        RxBuf_tail = 0;
        }

    	RxBuf_count++;                                               //увеличить счетчик принятых символов
//	    portEXIT_CRITICAL();
    return (0); 
	}

return (-1);
} 

