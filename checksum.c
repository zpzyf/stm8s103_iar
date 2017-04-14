#include "includes.h"

//函数  计算指定数据的和
//输入  buf 数据地址
//      len 数据长度
//输出  无
//返回  和
extern Uchar sum8(Uchar sum,Uchar *buf,Uint len)
{
    while(len--)
    {
        sum += *buf++;
    }
    return (sum);
}

