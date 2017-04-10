#ifndef _PORT_H_
#define _PORT_H_

#include "global.h"
#define RCC_PORT 	      RCC_APB2Periph_GPIOC
#define GPIO_PORT_PORT    GPIOC
#define GPIO_PIN_VBUS	  GPIO_Pin_6
#define GPIO_PIN_DCIN	  GPIO_Pin_7
#define GPIO_PIN_BAT 	  GPIO_Pin_8
#define GPIO_PIN_BOOT 	  GPIO_Pin_9
typedef enum
{
  VBUS,
  DCIN,
  BAT,
  BOOT,
}PORT_t;
void Port_Gpioinit(void);
void Port_Set(PORT_t _no);
void Port_Clear(PORT_t _no);
void Port_Toggle(PORT_t _no);
void VBUS_EN(void);
void VBUS_DIS(void);
void DCIN_EN(void);
void DCIN_DIS(void);
void BAT_EN(void);
void BAT_DIS(void);
void BOOT_EN(void);
void BOOT_DIS(void);

#endif

