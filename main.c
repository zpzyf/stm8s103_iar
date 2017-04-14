/**
  ******************************************************************************
  * @file    Project/main.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    25-February-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "includes.h"

static void sysCLKInit(void)
{
	//时钟配置
  CLK->CKDIVR = 0x00;//时钟为16MHz
}


static void watchDogInit() //初始化窗口看门狗
{

    IWDG->KR = 0xCC; //启动IWDG
    IWDG->KR = 0x55; //解除 PR 及 RLR 的写保护
    IWDG->RLR = 0xff; //看门狗计数器重装载数值
    IWDG->PR = 0x05; //分频系数为256，最长超时时间为：1.02S
    IWDG->KR = 0xAA; //刷新IWDG，避免产生看门狗复位，同时恢复 PR 及 RLR 的写保护状态
}


extern void feedIWDG(void)
{
    IWDG->KR = 0xAA;  //喂狗
}

static void sysGPIOInit()
{
	GPIO_Init( GPORT_UART_TX,    GPIN_UART_TX,     GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init( GPORT_UART_RX,    GPIN_UART_RX,     GPIO_MODE_IN_PU_NO_IT);
#ifdef INCLUDE_N32905_MP3
	GPIO_Init( GPORT_LED_BLUE,    GPIN_LED_BLUE,     GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow( GPORT_LED_BLUE,    GPIN_LED_BLUE);

    GPIO_Init( GPORT_LED_RED,      GPIN_LED_RED,       GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteHigh( GPORT_LED_RED,      GPIN_LED_RED);

	GPIO_Init( GPORT_ARM9_POWER,   GPIN_ARM9_POWER,   GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_WriteLow( GPORT_ARM9_POWER,   GPIN_ARM9_POWER);

	GPIO_Init( GPORT_ARM9_RST,     GPIN_ARM9_RST,   GPIO_MODE_OUT_PP_HIGH_SLOW);
	GPIO_WriteLow( GPORT_ARM9_RST,     GPIN_ARM9_RST);

	GPIO_Init( GPORT_LCDMOSI,    GPIN_LCDMOSI,     GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_Init( GPORT_LCDSCLK,    GPIN_LCDSCLK,     GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_Init( GPORT_LCDCS,    GPIN_LCDCS,     GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_Init( GPORT_LCDCMD,    GPIN_LCDCMD,     GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_Init( GPORT_LCDLIGHT,    GPIN_LCDLIGHT,     GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_WriteLow( GPORT_LCDLIGHT,   GPIN_LCDLIGHT);
#endif
#ifdef INCLUDE_RS485
	GPIO_Init( GPORT_485_LED_STATE,    GPIN_485_LED_STATE,     GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow( GPORT_485_LED_STATE,    GPIN_485_LED_STATE);
    GPIO_Init( GPORT_RS485_CTL,    GPIN_RS485_CTL,     GPIO_MODE_OUT_PP_HIGH_FAST);
#if defined (RS485_SEND)
    GPIO_WriteHigh( GPORT_RS485_CTL,    GPIN_RS485_CTL);
#elif defined (RS485_RECV)
    GPIO_WriteLow( GPORT_RS485_CTL,    GPIN_RS485_CTL);
#endif
#endif
}
#ifdef INCLUDE_N32905_MP3
static void setArm9Reset(void)
{
	GPIO_WriteHigh(GPORT_ARM9_RST,  GPIN_ARM9_RST);
    delayMs(50);
	GPIO_WriteLow( GPORT_ARM9_RST,  GPIN_ARM9_RST);
}

static void setArmWarkupPin(Uint dlytime)
{
	GPIO_WriteLow( GPORT_ARM9_POWER,  GPIN_ARM9_POWER);
    delayMs(10);
	GPIO_WriteHigh( GPORT_ARM9_POWER,  GPIN_ARM9_POWER);
    delayMs(dlytime);
    setArm9Reset();
    delayMs(50);
	GPIO_WriteLow( GPORT_ARM9_POWER,  GPIN_ARM9_POWER);

}

#endif
void main(void)
{
    disableInterrupts();
    sysCLKInit();
    sysGPIOInit();
#ifdef INCLUDE_RS485
    initUart(9600);
#else
    initUart(115200);
#endif
    timer4Init();
    watchDogInit();
    enableInterrupts();//打开总中断
#ifdef INCLUDE_N32905_MP3
    setArmWarkupPin(1000);//(800); //800正常
#endif
    //put_buffer("start mainloop\n\r", 16, UartPort1);
    while (1)
    {
        pollint();
        publicEvent();
    }

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
