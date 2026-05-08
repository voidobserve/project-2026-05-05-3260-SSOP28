#ifndef __AIP3368_H__
#define __AIP3368_H__

#include "my_config.h"

// aip3368h 芯片的数量（有多少个芯片级联）：
#define AIP3368H_DEV_NUM 8

#define DIO P25 // 串行数据输入端
#define DCK P16 // 串行时钟信号的输入端
#define LAT P24 // 数据锁存
#define PDM     // 输出使能控制端口，LED驱动ic引脚直接接地，不由单片机控制

extern volatile u16 aip3368h_display_buff[AIP3368H_DEV_NUM];

// #define aip3368h_delay()  do { Dly_us(1); } while(0)
#define aip3368h_delay()  // 延时函/数，根据需要决定使用，目前测试48Mhz主频无定时中断不需要延时也能正常点亮
// #define aip3368h_delay() do { delay(1); } while (0) // 延时函数，根据需要决定使用，目前测试48Mhz主频无定时中断不需要延时也能正常点亮

void aip3368h_refresh_time_add();

void aip3368h_module_init(void);
// void aip3368h_module_uninit(void);
void aip3368h_module_display(void);
void aip3368h_module_clear(void);

#endif