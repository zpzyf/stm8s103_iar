#include "includes.h"

UART_STRUCT uart;
#if defined (RS485_SEND)
Uint rs485_send_timeout;
#elif defined (RS485_RECV)
Uint rs485_recv_timeout;
#endif

static void USART1_Init(Ulong baudrate)
{
    UART1_DeInit();//串口复位
	UART1_Init(baudrate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);//串口初始化
	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);

//	UART1_Cmd(ENABLE); //使能串口
}

//初始化串口相关参  数
static void initUartPara(void)
{
	memset((Uchar *)&uart,0,sizeof(uart));
	uart.txEmpty = TRUE;
}


//函  数:初始化串口
//参  数:无
//返  回:无

extern void initUart(Ulong baud)
{
    USART1_Init(baud);
	initUartPara();
//    UARTTxEmpty = 1;
}

#if 0
/*给printf函数使用*/
int putchar(int ch)
{
    while(!UART1_SR_TXE);
    return (UART1_DR = ch);
}
#endif

static UART_STRUCT *getUartStruct(UARTPORT port)
{
	if (port == UartPort1)
	{
		return &uart;
	}
	return &uart;
}



extern void put_buf(Uchar ch,UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	while (((uart->txHead + 1)  &  (UART_TXBUFFERLEN -1)) == uart->txTail);
	uart->txBuf[uart->txHead] = ch;
	uart->txHead = (uart->txHead + 1) & (UART_TXBUFFERLEN -1);
    if (uart->txEmpty)
    {
    	uart->txEmpty = FALSE;
        //UART1->CR2 |= 0x80;  //发送中断使能
        UART1_ITConfig(UART1_IT_TXE, ENABLE);
    }
}

//函  数:发送一个字符串到串口
//参  数:buf	要发送的字符串
//		len	长度
//		port 串口号
//返  回:无
extern void put_buffer(Uchar const *buf, Uint len,UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
    while(uart->txcount)
    {
        pollint();
        publicEvent();
    }
	while(len--)
	{
		put_buf(*buf++,port);
	}
}

//函  数:取接收数据指针
//参  数port 串口号
//返  回:数据指针
extern Uchar *getRxBuffer(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	return (Uchar *)uart->rxBuf;
}
//函  数:取接收数据长度
//参  数port 串口号
//返  回:数据指针
extern Uint getRxBufLength(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	return uart->rxCount;
}
//函  数:清除接收BUF
//参  数port 串口号
//返  回:无
extern void clearRxBuffer(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	uart->rxCount = 0;
}


//函  数:检查是否有收到数据包，1ms调用一次
//参  数无
//返  回:无
extern void checkUarTxtRxTimeOut(void)
{
	if (uart.rxTimeOut)
	{
		if (--uart.rxTimeOut == 0)
		{
			pushEvent(evCOM1,uart.rxCount);
		}
	}

    if(uart.txcount> 0) uart.txcount--;

    #if defined(RS485_SEND)
        if (rs485_send_timeout) rs485_send_timeout--;
    #elif defined (RS485_RECV)
        if (rs485_recv_timeout) rs485_recv_timeout--;
    #endif
}


extern Uint getUartRxData(Uchar *tbuf,UARTPORT port)
{
    Uint len;
	UART_STRUCT *uart;
	uart = getUartStruct(port);

    if (uart->rxHead >= uart->rxTail)
    {
        len = uart->rxHead - uart->rxTail;
        memcpy(tbuf,(Uchar *)uart->rxBuf+uart->rxTail,len);
        return len;
    }
    else
    {
        len = UART_RXBUFFERLEN - uart->rxTail;
        memcpy(tbuf,(Uchar *)uart->rxBuf+uart->rxTail,len);
        memcpy(tbuf+len,(Uchar *)uart->rxBuf,uart->rxHead);
        len += uart->rxHead;
        return len;
    }
}



