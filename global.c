#include "global.h"


char USART2_TX_BUF[USART2_MAX_SEND_LEN] = {0}; 	
char USART2_RX_BUF[USART2_MAX_RECV_LEN] = {0}; 
uint16_t USART2_RX_STA = 0;
u8 f_cmd = 0;              //√¸¡Ó±Í÷æŒª
u32 T = 0;
u32 T_err = 0;
u8 f_err_vol = 0;



