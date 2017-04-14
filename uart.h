#ifndef __UART_H
#define __UART_H

#define   RXTIMEOUT    20         // ���ճ�ʱʱ��,��10mSec��δ�����κ�����,����һ�����հ�
#define   TXTIMEOUT    20
#define   UART_TXBUFFERLEN  0x20         //���ͻ�������С
#define   UART_RXBUFFERLEN  0x20          //�ӽӻ�������С

typedef struct
{
	//����
	Uint		rxHead;
	Uint		rxTail;
	Uint		rxCount;
	Uchar		rxBuf[UART_RXBUFFERLEN];
	Uchar		rxTimeOut;
	//����
	Uint		txHead;
	Uint 		txTail;
	Uchar      txEmpty;
	Uchar 		txBuf[UART_TXBUFFERLEN];
    Uchar      txcount;
}UART_STRUCT;

typedef enum
{
	UartPort1,
}UARTPORT;

extern UART_STRUCT uart;
extern Uint rs485_send_timeout;
extern Uint rs485_recv_timeout;

extern void checkUarTxtRxTimeOut(void);
extern void put_buf(Uchar ch,UARTPORT port);
extern void put_buffer(Uchar const *buf, Uint len,UARTPORT port);
extern Uchar *getRxBuffer(UARTPORT port);
extern Uint getRxBufLength(UARTPORT port);
extern void clearRxBuffer(UARTPORT port);
extern void initUart(Ulong baud);
#endif
