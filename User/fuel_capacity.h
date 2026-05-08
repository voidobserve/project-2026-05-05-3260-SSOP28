#ifndef __FUEL_CAPACITY_H__
#define __FUEL_CAPACITY_H__

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

#if FUEL_CAPACITY_SCAN_ENABLE
 

/*
    根据客户提供的数据，定义各个油量格数对应的ad值
    单片机使用内部3V参考电压，12位精度(0~4095)
*/
enum
{
    FUEL_LEVEL_0_ADC_VAL = (u16)((u32)1448 * 4096 / 3 / 1000),  /* 油量为0 单片机引脚测得1.448V */
    FUEL_LEVEL_1_ADC_VAL = (u16)((u32)1278 * 4096 / 3 / 1000),  /* 油量为一格 */
    FUEL_LEVEL_2_ADC_VAL = (u16)((u32)1154 * 4096 / 3 / 1000),  /* 油量为两格 */
    FUEL_LEVEL_3_ADC_VAL = (u16)((u32)1061 * 4096 / 3 / 1000),  /* 油量为三格 */
    FUEL_LEVEL_4_ADC_VAL = (u16)((u32)9924 * 4096 / 3 / 10000), /* 油量为四格 单片机引脚测得0.9924 V */
    FUEL_LEVEL_5_ADC_VAL = (u16)((u32)888 * 4096 / 3 / 1000),   /* 油量为五格 单片机引脚测得0.888 V */
    /* 大于五格，油量为6格 */
    FUEL_LEVEL_6_ADC_VAL = (u16)((u32)788 * 4096 / 3 / 1000), /* 假设 单片机引脚测得0.788 V是对应6格100%油量 */
    /* 如果采集到的ad值接近0，或是接近4095，说明没有接油量检测模块 */
};

// 油量最大时，对应的ad值
#define FUEL_MAX_ADC_VAL (950)
// 油量最小时，对应的ad值
#define FUEL_MIN_ADC_VAL (2000)

// 刚上电时，更新油量的时间，单位：ms
#define FUEL_UPDATE_TIME_WHEN_POWER_ON (500)
// 更新油量的时间，单位：ms
#define FUEL_UPDATE_TIME ((u16)1000)

// 油量检测配置
// ======================================================

extern u32 fuel_capacity_scan_cnt; // 扫描时间计数，在1ms定时器中断中累加

void fuel_capacity_scan(void);

void adc_update_fuel_val(u16 adc_val);

#endif //  
#endif
