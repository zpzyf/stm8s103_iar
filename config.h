#ifndef __CONFIG_H
#define __CONFIG_H

//#define INCLUDE_RS485

#if defined (INCLUDE_RS485)
    #define RS485_SEND
    //#define RS485_RECV
#endif

#define INCLUDE_N32905_MP3
#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned char   Uchar;
typedef unsigned int    Uint;
typedef unsigned long   Ulong;

#endif
