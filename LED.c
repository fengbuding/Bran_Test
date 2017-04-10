#include "LED.h"


void LED_Gpioinit(void)
{
	GPIO_InitTypeDef f;
    RCC_APB2PeriphClockCmd(RCC_LED, ENABLE );
	f.GPIO_Pin = GPIO_PIN_RED | GPIO_PIN_GREEN |GPIO_PIN_BLUE;
	f.GPIO_Speed = GPIO_Speed_50MHz;
	f.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_PORT_LED, &f);
	GPIO_SetBits(GPIO_PORT_LED, GPIO_PIN_RED | GPIO_PIN_GREEN | GPIO_PIN_BLUE);	
}
void bsp_LedOn(LED_COLOUR_t _no)
{
	if (_no == RED)
	{
		GPIO_PORT_LED->BRR = GPIO_PIN_RED;
	}
	else if (_no == GREEN)
	{
		GPIO_PORT_LED->BRR = GPIO_PIN_GREEN;
	}
	else if (_no == BLUE)
	{
		GPIO_PORT_LED->BRR = GPIO_PIN_BLUE;
	}
}
void bsp_LedOff(LED_COLOUR_t _no)
{
	if (_no == RED)
	{
		GPIO_PORT_LED->BSRR = GPIO_PIN_RED;
	}
	else if (_no == GREEN)
	{
		GPIO_PORT_LED->BSRR = GPIO_PIN_GREEN;
	}
	else if (_no == BLUE)
	{
		GPIO_PORT_LED->BSRR = GPIO_PIN_BLUE;
	}
}
void bsp_LedToggle(LED_COLOUR_t _no)
{
	if (_no == RED)
	{
		GPIO_PORT_LED->ODR ^= GPIO_PIN_RED;
	}
	else if (_no == GREEN)
	{
		GPIO_PORT_LED->ODR ^= GPIO_PIN_GREEN;
	}
	else if (_no == BLUE)
	{
		GPIO_PORT_LED->ODR ^= GPIO_PIN_BLUE;
	}
}
