#ifndef __UART_H
#define __UART_H

#define   RXTIMEOUT    20         // 接收超时时间,如10mSec内未接收任何数据,当作一个接收包
#define   TXTIMEOUT    20
#define   UART_TXBUFFERLEN  0x20         //发送缓冲区大小
#define   UART_RXBUFFERLEN  0x20          //接接缓冲区大小

typedef struct
{
	//接收
	Uint		rxHead;
	Uint		rxTail;
	Uint		rxCount;
	Uchar		rxBuf[UART_RXBUFFERLEN];
	Uchar		rxTimeOut;
	//发送
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
