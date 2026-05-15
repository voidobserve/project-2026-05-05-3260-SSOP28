#include "fuel_capacity.h"

#if FUEL_CAPACITY_SCAN_ENABLE

// static volatile u16 adc_val_of_fuel = 0;

// volatile u32 fuel_capacity_scan_cnt = 0; // 扫描时间计数，在1ms定时器中断中累加

static volatile u16 fuel_capacity_scan_time_cnt = 0;

// 滑动平均：
#define SAMPLE_COUNT 20 // 样本计数
static volatile u16 fuel_capacity_adc_val_samples[SAMPLE_COUNT] = {0};
static volatile u8 fuel_capacity_adc_val_sample_index = 0;

static void __fuel_capacity_adc_val_samples_init__(u16 adc_val)
{
    u8 i;
    for (i = 0; i < SAMPLE_COUNT; i++)
    {
        fuel_capacity_adc_val_samples[i] = adc_val;
    }
}

// 将数据放入油量检测的滑动平均数组
void fuel_capacity_adc_val_samples_update(u16 adc_val)
{
    static u8 is_initiated = 0;
    if (0 == is_initiated)
    {
        is_initiated = 1;
        __fuel_capacity_adc_val_samples_init__(adc_val);
        return; // 初始化数组之后，直接退出，下一次得到新数据才执行下面的操作
    }

    fuel_capacity_adc_val_samples[fuel_capacity_adc_val_sample_index] = adc_val;
    fuel_capacity_adc_val_sample_index++;
    if (fuel_capacity_adc_val_sample_index >= SAMPLE_COUNT)
    {
        fuel_capacity_adc_val_sample_index = 0;
    }
}

// 从油量检测的滑动平均数组中获取数据
u16 fuel_capacity_adc_val_get(void)
{
    u8 i;
    u32 sum = 0;
    for (i = 0; i < SAMPLE_COUNT; i++)
    {
        sum += fuel_capacity_adc_val_samples[i];
    }

    return (sum / SAMPLE_COUNT);
}

void fuel_capacity_scan_time_add(void)
{
    if (fuel_capacity_scan_time_cnt < ((u16)-1))
    {
        fuel_capacity_scan_time_cnt++;
    }
}

void fuel_capacity_scan(void)
{
    u16 fuel_adc_val;
    u16 fuel_voltage;

    static u8 is_initiated = 0; // 初始化
    static u8 fuel_lev_of_lag = 0;
    u8 cur_fuel_lev = 0;

    if (fuel_capacity_scan_time_cnt >= 200)
    {
        fuel_capacity_scan_time_cnt = 0;
    }
    else
    {
        return;
    }

    fuel_adc_val = fuel_capacity_adc_val_get();
    fuel_voltage = (u32)fuel_adc_val * 2000 / 4096; //
    printf("fuel_adc_val == %u\n", fuel_adc_val);
    printf("fuel_voltage == %u\n", fuel_voltage);
}

#endif
