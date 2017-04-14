#include "includes.h"

unsigned int  sys1msClock;

extern void delayMs(Uint count)
{
    sys1msClock = 0;
    while(sys1msClock < count)
    {
        pollint();
        publicEvent();
    }
}

extern void timer4Init(void)
{
	//��ʼ����ʱ��
	TIM4->ARR =  0x7d;//�Զ���װ�Ĵ���125,1ms��һ���ж�
	TIM4->PSCR = 0x07;//128��Ƶ
	TIM4->SR1 &= 0xFE;//����жϱ�־λ
	TIM4->IER |= 0x01;//�����¼��ж�ʹ��
	TIM4->CR1 |= 0x01;//ʹ�ܼ�ʱ����TIM4_CR0ֹͣ��ʱ��
}

