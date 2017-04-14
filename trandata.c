#include "includes.h"

//buf --> Uint
extern Uint tranDt_Buf2Uint(Uchar *buf)
{
    Uint dt;
    dt = *buf++ << 8;
    dt += *buf;
    return dt;
}
//Uint --> buf
extern void tranDt_Uint2Buf(Uchar *buf,Uint dt)
{
    *buf++ = (dt >>  8) & 0xff;
    *buf++ = dt & 0xff;
}


