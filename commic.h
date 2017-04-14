#ifndef __COMNIC_H
#define __COMNIC_H

extern void sendHeartbeatPacket(void);
extern void handleUartPackage(Uchar *buf,Uint len,UARTPORT port);
#endif

