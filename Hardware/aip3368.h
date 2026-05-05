#ifndef __AIP3368_H__
#define __AIP3368_H__

#include "my_config.h"

// aip3368h 芯片的数量（有多少个芯片级联）：
#define AIP3368H_DEV_NUM 16

#define DIO P05
#define DCK P06
#define LAT P07
#define PDM  // 输出使能控制端口，目前是由外部硬件控制，不由单片机控制

extern volatile u16 aip3368h_display_buff[AIP3368H_DEV_NUM];

// #define aip3368h_delay()  do { Dly_us(1); } while(0)
#define aip3368h_delay() // 延时函数，根据需要决定使用，目前测试48Mhz主频无定时中断不需要延时也能正常点亮

void aip3368h_module_init(void);
void aip3368h_module_uninit(void);
void aip3368h_module_display(void);
void aip3368h_module_clear(void);

#endif