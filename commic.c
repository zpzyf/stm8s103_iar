#include "includes.h"

#define CMD_HEARTBEAT   0x10
//ǰ����: 0xEA (1byte)
//����: (2byte) -->ǰ����~У����
//����: (1byte)
//����: (0~255 byte)
//У����:sum8(1byte)-->ǰ����~����
static void cmdpacket(Uchar cmd, Uchar *buf, Uint len)
{
    Uint tlen = 0;
    Uchar checkSum;
    Uchar str[0x20];

    str[tlen] = 0xEA;
    tlen +=1;
    checkSum = 0xea;
    tranDt_Uint2Buf(&str[tlen],len + 5);
    tlen += 2;
    checkSum = sum8( checkSum, &str[tlen-2], 2);
    str[tlen] = cmd;
    tlen += 1;
    checkSum += cmd;
    memcpy(&str[tlen], buf, len);
    tlen += len;
    checkSum = sum8(checkSum, buf, len);
    str[tlen] = checkSum;
    tlen += 1;
    put_buffer(str, tlen, UartPort1);
}

extern void sendHeartbeatPacket(void)
{
    cmdpacket(CMD_HEARTBEAT, NULL, 0);
}

//return >0 ��Ч���ݳ��� ��<0 ����Ч ; =0 ��û����
static int checkPackageData(Uchar *buf,Uint len)
{
    //put_buffer(buf,len,UartPort1);
    if (*buf == 0xEA)
    {
        Uint tlen;
        if (len < 5)
        {
            return 0;
        }
        tlen = tranDt_Buf2Uint(buf+1);
        if (len < tlen )
        {
            return 0;
        }
        if (sum8(0,buf,tlen-1) != buf[tlen-1])
        {
            return -1;
        }

        return tlen;
    }
    return -1;
}


static void doHandlePackage(Uchar *buf,Uint len)
{
    Uchar cmd;
    Uchar *dt;
    cmd = *(buf + 3);

    dt = buf+4;
    switch(cmd)
    {
        case CMD_HEARTBEAT:
            //put_buffer(buf,len,UartPort1);
            #if defined (RS485_RECV)
                rs485_recv_timeout = 2000;
            #endif
            break;
        default:
            dt = dt;
            break;
    }

}

static void handleClientData(Uchar *buf,Uint len)
{
    //Uchar buffer[UART_RXBUFFERLEN+1];
    if (checkPackageData(buf,len) > 0)
    {
        doHandlePackage(buf,len);
    }
}
//��  ��:���������յ������ݰ�
//��  ��:buf    ���ݰ���ַ
//       len    ���ݳ���
//       port   ����
//��  ��:��
extern void handleUartPackage(Uchar *buf,Uint len,UARTPORT port)
{
    //put_buffer(buf,len,port);
    //sysPrintf(buf);
    //putDotLcdStr(1, buf);
    //setDotLcdData(buf);
    if (port == UartPort1)
    {
        //put_buffer(buf,len,port);
        handleClientData(buf,len);
    }
    clearRxBuffer(port);

}

