#include "pin_level_scan.h"

#if PIN_LEVEL_SCAN_ENABLE

volatile u16 pin_level_scan_time_cnt;

void pin_level_scan_config(void)
{ 

    // 检测 水温报警 的引脚:
    P2_MD0 &= ~(GPIO_P20_MODE_SEL(0x03)); // 输入模式
}

// 引脚电平扫描，都是低电平有效
void pin_level_scan(void)
{
    

}

#endif
