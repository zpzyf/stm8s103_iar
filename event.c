#include "includes.h"

EVENTSTRUCT ecrEvent[MaxSysEvent];

Uint eventTail,eventHead;

extern void displayEvent(void)
{
    //DEBUGDATA(eventHead);
    //DEBUGDATA(eventTail);
}
//��  ��:��ʼ��ϵͳ�������
//		  ��ʼ�����������PUSHEVENT,Ҫ�ȴ�����startCanPusEvent
//��  ��:��
//��  ��:��
extern void initEventQueue()
{
    clearEvent();
}

//��  ��:PUSH EVENT
//��  ��:evt		�¼�
//		para 	��  ��
//��  ��:��
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
//��  ��:��������¼�
//��  ��:��
//��  ��:��
extern void clearEvent(void)
{
    eventHead = eventTail = 0;
}
//��  ��:ȡ�¼�(����  ��)
//��  ��:*evt       �¼�
//       timeout    Timt Out ʱ��
//��  ��:0 ȡ��EVENT   1�� TIMEOUT
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

