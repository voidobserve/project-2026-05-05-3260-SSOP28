#ifndef __FUEL_CAPACITY_H__
#define __FUEL_CAPACITY_H__

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

#if FUEL_CAPACITY_SCAN_ENABLE

/*
    根据客户提供的数据，定义各个油量格数对应的ad值
    单片机使用内部3V参考电压，12位精度(0~4095)
*/
// enum
// {
//     FUEL_LEVEL_0_ADC_VAL = (u16)((u32)1448 * 4096 / 3 / 1000),  /* 油量为0 单片机引脚测得1.448V */
//     FUEL_LEVEL_1_ADC_VAL = (u16)((u32)1278 * 4096 / 3 / 1000),  /* 油量为一格 */
//     FUEL_LEVEL_2_ADC_VAL = (u16)((u32)1154 * 4096 / 3 / 1000),  /* 油量为两格 */
//     FUEL_LEVEL_3_ADC_VAL = (u16)((u32)1061 * 4096 / 3 / 1000),  /* 油量为三格 */
//     FUEL_LEVEL_4_ADC_VAL = (u16)((u32)9924 * 4096 / 3 / 10000), /* 油量为四格 单片机引脚测得0.9924 V */
//     FUEL_LEVEL_5_ADC_VAL = (u16)((u32)888 * 4096 / 3 / 1000),   /* 油量为五格 单片机引脚测得0.888 V */
//     /* 大于五格，油量为6格 */
//     FUEL_LEVEL_6_ADC_VAL = (u16)((u32)788 * 4096 / 3 / 1000), /* 假设 单片机引脚测得0.788 V是对应6格100%油量 */
//     /* 如果采集到的ad值接近0，或是接近4095，说明没有接油量检测模块 */
// };

// 将电压值转换为油量检测点对应的ad值，单位：mV
#define FUEL_VOLTAGE_TO_ADC_VAL(voltage) ((u16)((u32)(voltage) * 4096 / 2 / 1000))
// 补偿电压值
#define FUEL_COMPENSATION_VOLTAGE (100)
enum
{
    // 检测到电压大于 1.7 V，就认为油量为空
    FUEL_LEV_EMPTY_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(1700),
    FUEL_LEV_0_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(1450), // 第 0 格油量指示灯
    FUEL_LEV_1_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(1100), // 第 1 格油量指示灯
    FUEL_LEV_2_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(916),  // 第 2 格油量指示灯
    FUEL_LEV_3_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(700),  // 第 3 格油量指示灯
    FUEL_LEV_4_ADC_VAL = FUEL_VOLTAGE_TO_ADC_VAL(355),  // 第 4 格油量指示灯
};

// USER_TO_DO 如果把满油量和没有油量对应的电压值进行线性划分
/*
    1.43 ~ 0
    1430 / 5 ==

*/
// 满油量对应的电压
#define FUEL_FULL_VOLTAGE (220)
// 没有油量对应的电压
#define FUEL_EMPTY_VOLTAGE (1430)
// 油量挡位
#define FUEL_LEVEL_MAX (5)
// 线性划分的各个油量挡位对应的电压值：
enum
{
    FUEL_LEVEL_0_VOLTAGE = FUEL_EMPTY_VOLTAGE,
    FUEL_LEVEL_1_VOLTAGE = FUEL_EMPTY_VOLTAGE -
                           (FUEL_EMPTY_VOLTAGE - FUEL_FULL_VOLTAGE) *
                               1 / FUEL_LEVEL_MAX,
    FUEL_LEVEL_2_VOLTAGE = FUEL_EMPTY_VOLTAGE -
                           (FUEL_EMPTY_VOLTAGE - FUEL_FULL_VOLTAGE) *
                               2 / FUEL_LEVEL_MAX,
    FUEL_LEVEL_3_VOLTAGE = FUEL_EMPTY_VOLTAGE -
                           (FUEL_EMPTY_VOLTAGE - FUEL_FULL_VOLTAGE) *
                               3 / FUEL_LEVEL_MAX,
    FUEL_LEVEL_4_VOLTAGE = FUEL_EMPTY_VOLTAGE -
                           (FUEL_EMPTY_VOLTAGE - FUEL_FULL_VOLTAGE) *
                               4 / FUEL_LEVEL_MAX,

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

void fuel_capacity_scan_time_add(void);
void fuel_capacity_adc_val_samples_update(u16 adc_val);
u16 fuel_capacity_adc_val_get(void);

void fuel_capacity_scan(void);

#endif //
#endif
