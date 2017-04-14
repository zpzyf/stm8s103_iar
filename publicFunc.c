#include "includes.h"

extern void feedIWDG(void);

extern void publicEvent(void)
{
    EVENTSTRUCT evt;

    if (getEventPara(&evt,0) == 0)
    {
       switch(evt.event)
        {
            case ev1S:

                #if defined (RS485_SEND)
                    sendHeartbeatPacket();
                #elif defined (RS485_RECV)
                    //put_buffer("1S\n\r", 4, UartPort1);
                    if (!rs485_recv_timeout)
                        GPIO_WriteReverse( GPORT_485_LED_STATE,    GPIN_485_LED_STATE);
                #endif
                break;
            case ev100MS:
                #if defined (INCLUDE_N32905_MP3)
        	        GPIO_WriteReverse( GPORT_LED_RED,      GPIN_LED_RED);
        	        GPIO_WriteReverse( GPORT_LED_BLUE,      GPIN_LED_BLUE);
                #endif

                #if defined (RS485_SEND)
                    if (rs485_send_timeout)
                        GPIO_WriteReverse( GPORT_485_LED_STATE,    GPIN_485_LED_STATE);
                #elif defined (RS485_RECV)
                    if (rs485_recv_timeout)
                        GPIO_WriteReverse( GPORT_485_LED_STATE,    GPIN_485_LED_STATE);
                #endif
                break;
            case evCOM1:
                handleUartPackage(getRxBuffer(UartPort1),getRxBufLength(UartPort1),UartPort1);
                break;
            case evIWDT:
                feedIWDG();
            default:
                break;
        }
    }
}

