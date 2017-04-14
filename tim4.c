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
	//初始化定时器
	TIM4->ARR =  0x7d;//自动重装寄存器125,1ms进一次中断
	TIM4->PSCR = 0x07;//128分频
	TIM4->SR1 &= 0xFE;//清除中断标志位
	TIM4->IER |= 0x01;//更新事件中断使能
	TIM4->CR1 |= 0x01;//使能计时器，TIM4_CR0停止计时器
}

