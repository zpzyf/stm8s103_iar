#ifndef __HARDWARE_H
#define __HARDWARE_H
/*
#define GPORT_LCDMOSI           GPIOC
#define GPIN_LCDMOSI            GPIO_PIN_6

#define GPORT_LCDSCLK           GPIOC
#define GPIN_LCDSCLK            GPIO_PIN_5

#define GPORT_LCDCS             GPIOC
#define GPIN_LCDCS              GPIO_PIN_4

#define GPORT_LCDCMD            GPIOC
#define GPIN_LCDCMD             GPIO_PIN_3

#define GPORT_LCDLIGHT          GPIOA
#define GPIN_LCDLIGHT           GPIO_PIN_3

#define GPORT_I2C_CLK           GPIOB
#define GPIN_I2C_CLK            GPIO_PIN_4

#define GPORT_I2C_DAT           GPIOB
#define GPIN_I2C_DAT            GPIO_PIN_5

#define GPORT_I2C_BUSY          GPIOD
#define GPIN_I2C_BUSY           GPIO_PIN_4
*/
#ifdef INCLUDE_RS485

#define GPORT_485_LED_STATE         GPIOC           // led 1
#define GPIN_485_LED_STATE          GPIO_PIN_3

#define GPORT_RS485_CTL         GPIOA           //led 2
#define GPIN_RS485_CTL          GPIO_PIN_1

#endif
#define GPORT_ARM9_RST          GPIOD
#define GPIN_ARM9_RST           GPIO_PIN_2

#define GPORT_ARM9_POWER       GPIOD
#define GPIN_ARM9_POWER        GPIO_PIN_3


#define GPORT_UART_TX           GPIOD
#define GPIN_UART_TX            GPIO_PIN_5

#define GPORT_UART_RX           GPIOD
#define GPIN_UART_RX            GPIO_PIN_6


#ifdef INCLUDE_N32905_MP3
#define GPORT_LCDMOSI           GPIOC
#define GPIN_LCDMOSI            GPIO_PIN_6

#define GPORT_LCDSCLK           GPIOC
#define GPIN_LCDSCLK            GPIO_PIN_5

#define GPORT_LCDCS             GPIOC
#define GPIN_LCDCS              GPIO_PIN_4

#define GPORT_LCDCMD            GPIOC
#define GPIN_LCDCMD             GPIO_PIN_3

#define GPORT_LCDLIGHT          GPIOA
#define GPIN_LCDLIGHT           GPIO_PIN_3

#define GPORT_I2C_CLK           GPIOB
#define GPIN_I2C_CLK            GPIO_PIN_4

#define GPORT_I2C_DAT           GPIOB
#define GPIN_I2C_DAT            GPIO_PIN_5


#define GPORT_LED_BLUE         GPIOA           // led 1
#define GPIN_LED_BLUE          GPIO_PIN_2


#define GPORT_LED_RED           GPIOA           //led 2
#define GPIN_LED_RED            GPIO_PIN_1
#endif
#endif
