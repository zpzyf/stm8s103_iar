#include "includes.h"

unsigned char pollintack;

static Uchar _1ms;
static Uchar _10ms;
static Uchar _100ms;
void pollint(void)
{
    if (!pollintack)
    {
        return;
    }
    pollintack = 0;

    if (++_1ms>10)
    {
        _1ms = 0;

        if (++_10ms > 10)
        {
            _10ms = 0;
            if (++_100ms > 10)
            {
                _100ms = 0;
            }
        }
    }

    checkUarTxtRxTimeOut();
    switch(_1ms) //10mS
    {
        case 1:
            break;
        case 2:
            pushEvent(ev10MS, 0);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 0:
            switch(_10ms)   //100mS
            {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    pushEvent(ev100MS, 0);
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    pushEvent(evIWDT, 0);
                    break;
                case 0:
                    switch(_100ms)  //1S
                    {
                        case 1:
                            pushEvent(ev1S, 0);
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:

                            break;
                        case 6:
                            break;
                        case 7:
                            break;
                        case 8:
                            break;
                        case 9:
                            break;
                        case 0:
                            break;
                    }
                    break;
            }
            break;
        }
}
