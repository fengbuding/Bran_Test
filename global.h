#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "stm32f10x.h"



#define USART2_MAX_RECV_LEN		1024				
#define USART2_MAX_SEND_LEN		1024

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

extern char USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	
extern char USART2_RX_BUF[USART2_MAX_RECV_LEN]; 
extern uint16_t USART2_RX_STA;
extern u8 f_cmd;              //√¸¡Ó±Í÷æŒª
extern u32 T;
typedef enum
{
  err_none,
  err_crc,
  err_cmd,
  err_content,
}com_err;

#endif


