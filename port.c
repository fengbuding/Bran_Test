#include "port.h"


void Port_Gpioinit(void)
{
	GPIO_InitTypeDef f;
    RCC_APB2PeriphClockCmd(RCC_PORT, ENABLE );
	f.GPIO_Pin = GPIO_PIN_VBUS | GPIO_PIN_DCIN |GPIO_PIN_BAT | GPIO_PIN_BOOT;
	f.GPIO_Speed = GPIO_Speed_50MHz;
	f.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_PORT_PORT, &f);
//	GPIO_SetBits(GPIO_PORT_PORT, GPIO_PIN_VBUS | GPIO_PIN_DCIN |GPIO_PIN_BAT);	//ÖÃ1
//   GPIO_ResetBits(GPIO_PORT_PORT, GPIO_PIN_BOOT);                              //ÖÃ0 
    
    DCIN_DIS();
    VBUS_DIS();
    BAT_DIS();
    BOOT_DIS();
}
void Port_Clear(PORT_t _no)
{
	if (_no == VBUS)
	{
		GPIO_PORT_PORT->BRR = GPIO_PIN_VBUS;
	}
	else if (_no == DCIN)
	{
		GPIO_PORT_PORT->BRR = GPIO_PIN_DCIN;
	}
	else if (_no == BAT)
	{
		GPIO_PORT_PORT->BRR = GPIO_PIN_BAT;
	}
    else if (_no == BOOT)
	{
		GPIO_PORT_PORT->BRR = GPIO_PIN_BOOT;
	}
    
}
void Port_Set(PORT_t _no)
{
	if (_no == VBUS)
	{
		GPIO_PORT_PORT->BSRR = GPIO_PIN_VBUS;
	}
	else if (_no == DCIN)
	{
		GPIO_PORT_PORT->BSRR = GPIO_PIN_DCIN;
	}
	else if (_no == BAT)
	{
		GPIO_PORT_PORT->BSRR = GPIO_PIN_BAT;
	}
    else if (_no == BOOT)
	{
		GPIO_PORT_PORT->BSRR = GPIO_PIN_BOOT;
	}
}
void Port_Toggle(PORT_t _no)
{
	if (_no == VBUS)
	{
		GPIO_PORT_PORT->ODR ^= GPIO_PIN_VBUS;
	}
	else if (_no == DCIN)
	{
		GPIO_PORT_PORT->ODR ^= GPIO_PIN_DCIN;
	}
	else if (_no == BAT)
	{
		GPIO_PORT_PORT->ODR ^= GPIO_PIN_BAT;
	}
    else if (_no == BOOT)
	{
		GPIO_PORT_PORT->ODR ^= GPIO_PIN_BOOT;
	}
}
void VBUS_EN(void)
{
    Port_Set(VBUS);
}
void VBUS_DIS(void)
{
    Port_Clear(VBUS);
}
void DCIN_EN(void)
{
  Port_Set(DCIN);
}
void DCIN_DIS(void)
{
  Port_Clear(DCIN);
}
void BAT_EN(void)
{
  Port_Set(BAT);
}
void BAT_DIS(void)
{
  Port_Clear(BAT);
}
void BOOT_EN(void)
{
  Port_Set(BOOT);
}
void BOOT_DIS(void)
{
  Port_Clear(BOOT);
}
