#include "includes.h"

UART_STRUCT uart;
#if defined (RS485_SEND)
Uint rs485_send_timeout;
#elif defined (RS485_RECV)
Uint rs485_recv_timeout;
#endif

static void USART1_Init(Ulong baudrate)
{
    UART1_DeInit();//���ڸ�λ
	UART1_Init(baudrate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);//���ڳ�ʼ��
	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);

//	UART1_Cmd(ENABLE); //ʹ�ܴ���
}

//��ʼ��������ز�  ��
static void initUartPara(void)
{
	memset((Uchar *)&uart,0,sizeof(uart));
	uart.txEmpty = TRUE;
}


//��  ��:��ʼ������
//��  ��:��
//��  ��:��

extern void initUart(Ulong baud)
{
    USART1_Init(baud);
	initUartPara();
//    UARTTxEmpty = 1;
}

#if 0
/*��printf����ʹ��*/
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
        //UART1->CR2 |= 0x80;  //�����ж�ʹ��
        UART1_ITConfig(UART1_IT_TXE, ENABLE);
    }
}

//��  ��:����һ���ַ���������
//��  ��:buf	Ҫ���͵��ַ���
//		len	����
//		port ���ں�
//��  ��:��
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

//��  ��:ȡ��������ָ��
//��  ��port ���ں�
//��  ��:����ָ��
extern Uchar *getRxBuffer(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	return (Uchar *)uart->rxBuf;
}
//��  ��:ȡ�������ݳ���
//��  ��port ���ں�
//��  ��:����ָ��
extern Uint getRxBufLength(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	return uart->rxCount;
}
//��  ��:�������BUF
//��  ��port ���ں�
//��  ��:��
extern void clearRxBuffer(UARTPORT port)
{
	UART_STRUCT *uart;
	uart = getUartStruct(port);
	uart->rxCount = 0;
}


//��  ��:����Ƿ����յ����ݰ���1ms����һ��
//��  ����
//��  ��:��
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



