#ifndef __PIN_LEVEL_SCAN_H__
#define __PIN_LEVEL_SCAN_H__

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

#if PIN_LEVEL_SCAN_ENABLE
 

#define PIN_DETECT_TEMP_OF_WATER_ALERT (P20)
// #define PIN_DETECT_MALFUNCTION (P21) // 检测故障的引脚
 

// ======================================================
// 引脚电平扫描配置：
// 扫描时间，每隔 xx ms更新一次状态(不能大于变量类型对应的最大值)
#define PIN_LEVEL_SCAN_TIME_MS (200)
// 引脚电平扫描配置
// ======================================================

extern u16 pin_level_scan_time_cnt;

void pin_level_scan_config(void); // 扫描引脚的配置（初始化）
void pin_level_scan(void);        // 扫描引脚的电平
#endif                            // PIN_LEVEL_SCAN_ENABLE

#endif
