#include "includes.h"

EVENTSTRUCT ecrEvent[MaxSysEvent];

Uint eventTail,eventHead;

extern void displayEvent(void)
{
    //DEBUGDATA(eventHead);
    //DEBUGDATA(eventTail);
}
//函  数:初始化系统任务队列
//		  初始化完后不能马上PUSHEVENT,要等待调用startCanPusEvent
//参  数:无
//返  回:无
extern void initEventQueue()
{
    clearEvent();
}

//函  数:PUSH EVENT
//参  数:evt		事件
//		para 	参  数
//返  回:无
extern void pushEvent(Uint evt,Uint para)
{
    if (((eventHead + 1) & (MaxSysEvent -1)) != eventTail)
    {
        eventHead = (eventHead+1) & (MaxSysEvent -1);
        ecrEvent[eventHead].event = evt;
        ecrEvent[eventHead].para = para;
    }
}
extern void pushEvent16(Uint evt)
{
    pushEvent(evt,0);
}
//函  数:清空所有事件
//参  数:无
//返  回:无
extern void clearEvent(void)
{
    eventHead = eventTail = 0;
}
//函  数:取事件(带参  数)
//参  数:*evt       事件
//       timeout    Timt Out 时间
//返  回:0 取到EVENT   1： TIMEOUT
extern Uchar getEventPara(EVENTSTRUCT *evt,Ulong timeout)
{
    if (timeout < 20)
    {
        timeout = 20;
    }
    do
    {
        if (eventTail != eventHead)
        {
            *evt = *(ecrEvent+eventTail);
            eventTail = (eventTail+1) & (MaxSysEvent - 1);
            return 0;
        }

        timeout -= 10;
        if (timeout < 10)
        {
            evt->event = evNON;
            evt->para = 0;
            break;
        }
    }while(1);

    return 1;
}

