#ifndef _EVENT_H_
#define _EVENT_H_

#define MaxSysEvent     10

enum
{
    evNON = 0,
    ev1MS = evNON + 1,
    ev10MS,
    ev100MS,
    ev1S,
    evCOM1,
    evIWDT,
};

typedef struct
{
    Uint    event;
    Uint    para;
}EVENTSTRUCT;
extern void displayEvent(void);
extern void initEventQueue(void);
extern void pushEvent(Uint buzzerEvt,Uint para);
extern void clearEvent(void);
extern Uchar getEventPara(EVENTSTRUCT *evt,Ulong timeout);
#define isDispEvent(event)      ((event > evNON) && (event < evKEY_END))
#define isPressKeyEvent(event)  ((event > evNON) && (event < evKEY_END))

#endif

