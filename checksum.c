#include "includes.h"

//����  ����ָ�����ݵĺ�
//����  buf ���ݵ�ַ
//      len ���ݳ���
//���  ��
//����  ��
extern Uchar sum8(Uchar sum,Uchar *buf,Uint len)
{
    while(len--)
    {
        sum += *buf++;
    }
    return (sum);
}

