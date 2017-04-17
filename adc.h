#ifndef ADC_H_MJL
#define ADC_H_MJL

#include "global.h"
#include <math.h>
#define CH_NUM  8           //Ҫʹ�õ�ADCͨ����
#define N       10          // �ɼ�����
extern uint16_t ad_value[N][CH_NUM];
extern const float arr_per[8];
extern const float arr_vol[8];
void adc_gpio_init(void);
void adc_dma_init(void);
void adc_init(void);
void adc_config(void);
void adc_start(void);
void get_ChannelVale(float arr[]);
#endif
