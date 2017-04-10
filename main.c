#include "global.h"
#include "bsp_usart1.h"
#include "bsp_TiMbase.h" 
#include "bsp_SysTick.h"
#include "stm32f10x_it.h"
#include "string.h"
#include "LED.h"
#include "port.h"
#include "adc.h"
//0--Burn Firmware Prepare
//1--Burn Firmware Start
//2--Burn Firmware End
//3--Change Usb A0B0
//4--Change Usb A0B1
//5--Change Usb A1B0
//6--Change Usb A1B1
//7--Get Voltage
char * cmd[8] = {"Burn Firmware Prepare","Burn Firmware Start","Burn Firmware End","Change Usb A0B0",\
                "Change Usb A0B1","Change Usb A1B0","Change Usb A1B1","Get Voltage"}; //
//43 47 31 42 30 01 2d
//C  G  1  B  0
char ack_buf[USART2_MAX_SEND_LEN] = {0};
float vol[CH_NUM] = {0}; 
void send_ack(char * s)
{
    u16 crc = 0;
    char arry[3];
    u8 len = 3 + USART2_RX_BUF[2]; 
    memset(ack_buf, 0, strlen(ack_buf));
    strncpy(ack_buf, USART2_RX_BUF, len);
    arry[0] = strlen(s);
    arry[1] = '\0';
    strcat(ack_buf, arry);
    strcat(ack_buf, s);
    for(u8 i = 0; i < strlen(ack_buf); i++)
    {
        crc += ack_buf[i];
    }
    arry[0] = (crc >> 8) & 0xff;
    arry[1] = crc & 0xff;
    arry[2] = '\0';
    strcat(ack_buf,arry);
    uart4Printf("%s", ack_buf);  
    printf(">>>%s\r\n", ack_buf);
}
com_err handle_data(void)
{
    u16 crc = 0;    
    u8 i = 0;
    u8 LEN = 0;
    LEN = 2 + 1 + USART2_RX_BUF[2];
    LEN = LEN + 1 + USART2_RX_BUF[LEN] + 2;
    printf(">>>%s   %d\r\n", USART2_RX_BUF, LEN); 
    for(i = 0; i < LEN - 2; i++)
    {
        crc += USART2_RX_BUF[i];
    }
    if(crc != ((USART2_RX_BUF[LEN-2] << 8) | USART2_RX_BUF[LEN-1]))
    {
        return err_crc;
    }
    for(i = 0; i < 8; i++)
    {
        if(strstr(USART2_RX_BUF, cmd[i]) != NULL)
        {
            f_cmd = i; 
            break;
        }
    }
    if(i == 8)
    {
        return err_cmd;
    }
    char s[100] = {0};
    char s1[12] = {0};
    switch(f_cmd)
    {
        case 0:                                           //0--Burn Firmware Prepare
               VBUS_DIS();
               BAT_DIS();           
               DCIN_DIS(); 
               BOOT_EN();
               strcpy(s, "Success");
               send_ack(s);
               printf("cmd%d ok...\r\n", f_cmd);
               break;
        case 1:                                    //1--Burn Firmware Start
               VBUS_EN();
               BAT_DIS();           
               DCIN_DIS();  
               strcpy(s,"Success");
               send_ack(s);
               printf("cmd%d ok...\r\n",f_cmd);          
               break;
        case 2:                                     //2--Burn Firmware End
               BOOT_DIS();
               strcpy(s, "Success");
               send_ack(s);
               printf("cmd%d ok...\r\n", f_cmd);          
               break;
        case 3:                                     //3--Change Usb A0B0--电池--BAT打开    
               VBUS_DIS();
               DCIN_DIS();                
               BAT_EN();          
               strcpy(s, "Success");
               send_ack(s);
               printf("cmd%d ok...\r\n", f_cmd);
               break;
        case 4:                                        //4--Change Usb A0B1--USB--VBUS打开
               VBUS_EN();   
               DCIN_DIS();
               BAT_DIS();
               strcpy(s, "Success");
               send_ack(s);
               printf("cmd%d ok...\r\n", f_cmd);
               break;
        case 5:                                         //5--Change Usb A1B0--底座--DCIN打开
               VBUS_DIS();   
               DCIN_EN();
               BAT_DIS();
               strcpy(s, "Success");
               send_ack(s);
               printf("cmd%d ok...\r\n", f_cmd);
               break;
        case 6:                                         //6--Change Usb A1B1--底座+USB打开
               VBUS_EN();   
               DCIN_EN();
               BAT_DIS();                    
               strcpy(s, "Success");
               send_ack(s);
               printf("\r\ncmd%d ok...\r\n", f_cmd);
               break;
        case 7:                                             //7--Get Voltage 
               //VBUS_EN();
               //DCIN_DIS();                
               //BAT_DIS();
               get_ChannelVale(vol);        // do something
               for(i = 0; i < 7; i++)
               {
                   sprintf(s1, "Vol%d=%.2f,", i, vol[i]);  //s1--10byte
                   strcat(s, s1);
               }    
               sprintf(s1, "Vol7=%.2f", vol[7]);
               strcat(s, s1);
               send_ack(s);
               printf("\r\ncmd%d ok...\r\n", f_cmd);
               break;               
        default:    ;
    }
    memset(USART2_RX_BUF, 0, LEN); 
    return err_none;
}
//Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer, u16 rlr) //prer = 0 ~ 7, rlr < 2047
{
	IWDG->KR = 0X5555;	 										  
  	IWDG->PR = prer;  
  	IWDG->RLR = rlr;   
	IWDG->KR = 0XAAAA;//reload											   
  	IWDG->KR = 0XCCCC;	
}
void IWDG_Feed(void)
{
	IWDG->KR = 0XAAAA;//reload											   
}

int main(void) 
{
    com_err error = err_none;
    SysTick_Init();
    UsartInit();
    LED_Gpioinit();
    Port_Gpioinit();
    adc_config();
    adc_start();
    TIM2_Configuration();
    TIM3_Configuration();
    IWDG_Init(5,1250);    //超过4s，复位
    printf("system start...\r\n");
    for(;;)
    {	
      if(USART2_RX_STA & 0x8000)
      {
          error = handle_data();
          printf("error code: %d\r\n",error);                 
          USART2_RX_STA = 0;
      }
      if((T ^ 100) == 0)
      {
        T = 0;
        bsp_LedToggle(GREEN);
      }
      IWDG_Feed();
    }
}
/*********************************************END OF FILE**********************/
