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

//���������� ����������� �������� ����������� � �������� ������
unsigned char FIFO_RxBuf_Count_Get (void) {

    return RxBuf_count;
}

//"�������" �������� �����
void FIFO_RxBuf_Flush (void) {

//    portENTER_CRITICAL();
    RxBuf_tail = 0;
    RxBuf_head = 0;
    RxBuf_count = 0;
//	portEXIT_CRITICAL();
}

//������ ������
unsigned char FIFO_RxBuf_Char_Get (void) {

    unsigned char sym;
	portENTER_CRITICAL();
    if (RxBuf_count > 0) {                                          //���� �������� ����� �� ������
        sym = RxBuf[RxBuf_head];                                 //��������� �� ���� ������
        RxBuf_count--;                                               //��������� ������� ��������
        RxBuf_head++;                                                //���������������� ������ ������ ������

        if (RxBuf_head == FIFO_BUF_SIZE) {
		    RxBuf_head = 0;
        }
    portEXIT_CRITICAL();
    return sym;                                                      //������� ����������� ������
    }

return (-1);
}


//������ � �����
unsigned char FIFO_RxBuf_Char_Put (unsigned char c) {
    
	if (RxBuf_count < FIFO_BUF_SIZE) {                          //���� � ������ ��� ���� �����
	    
//		portENTER_CRITICAL();
        RxBuf[RxBuf_tail] = c;                               //������� ������ �� UDR � �����
        RxBuf_tail++;                                            //��������� ������ ������ ��������� ������

        if (RxBuf_tail == FIFO_BUF_SIZE) {
	        RxBuf_tail = 0;
        }

    	RxBuf_count++;                                               //��������� ������� �������� ��������
//	    portEXIT_CRITICAL();
    return (0); 
	}

return (-1);
} 

