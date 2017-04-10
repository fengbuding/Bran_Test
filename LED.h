#ifndef _LED_H_
#define _LED_H_

#include "global.h"
#define RCC_LED 	      RCC_APB2Periph_GPIOF
#define GPIO_PORT_LED     GPIOF
#define GPIO_PIN_RED	  GPIO_Pin_3
#define GPIO_PIN_GREEN	  GPIO_Pin_4
#define GPIO_PIN_BLUE	  GPIO_Pin_5
typedef enum
{
  RED,
  GREEN,
  BLUE,
}LED_COLOUR_t;
void LED_Gpioinit(void);
void bsp_LedOn(LED_COLOUR_t _no);
void bsp_LedOff(LED_COLOUR_t _no);
void bsp_LedToggle(LED_COLOUR_t _no);

#endif

