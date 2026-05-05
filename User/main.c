/**
 ******************************************************************************
 * @file    main.c
 * @author  HUGE-IC Application Team
 * @version V1.0.0
 * @date    05-11-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2021 HUGE-IC</center></h2>
 *
 * 版权说明后续补上
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "include.h"
#include "my_config.h"

void user_init(void)
{

    tmr1_config(); // 检测一段时间内的脉冲个数所需的定时器(用于计时)

#if SPEED_SCAN_ENABLE
    speed_scan_config(); // 时速扫描的配置
#endif

#if ENGINE_SPEED_SCAN_ENABLE
    engine_speed_scan_config(); // 发动机转速扫描的配置
#endif

#if (BATTERY_SCAN_ENABLE || AD_KEY_ENABLE || FUEL_CAPACITY_SCAN_ENABLE || TEMP_OF_WATER_SCAN_ENABLE)
    adc_config();
#endif

#if TOUCH_KEY_ENABLE
    tk_param_init(); // 触摸按键模块初始化
#endif

    tmr2_config(); // 扫描脉冲(电平变化)的定时器

    // iic_config();
    // eeprom_24cxx_clear(); // 全片擦除

    // printf("begin read eeprom\n");
    fun_info_init(); // 初始化用于存放信息的变量

#if USER_DEBUG_ENABLE
    uart0_debug_init();
    printf("sys reset\n");
#endif

    delay_ms(1); // 等待系统稳定
                 // delay_ms(2000); // 等待系统稳定
}

void main(void)
{
    // 看门狗默认打开, 复位时间2s
    system_init();

    // WDT_KEY = WDT_KEY_VAL(0xDD); //  关闭看门狗

    // 关闭HCK和HDA的调试功能
    WDT_KEY = 0x55;  // 解除写保护
    IO_MAP &= ~0x01; // 清除这个寄存器的值，实现关闭HCK和HDA引脚的调试功能（解除映射）
    WDT_KEY = 0xBB;

    /* 用户代码初始化接口 */
    user_init();

    // 上电后，需要点亮一下所有的指示灯，再关闭:
    P23 = 1;
    delay_ms(1000);
    P23 = 0;

    // USER_TO_DO 上电之后，需要先跑一遍开机动画，再继续主循环

    /* 系统主循环 */
    while (1)
    {
        // printf("main circle\n");

#if 1
        WDT_KEY = WDT_KEY_VAL(0xAA); // 喂狗并清除 wdt_pending

#if TOUCH_KEY_ENABLE
        /* 按键扫描函数 */
        __tk_scan();                 // 使用了库里面的接口（闭源库）
        WDT_KEY = WDT_KEY_VAL(0xAA); // 喂狗并清除 wdt_pending
#endif

#if AD_KEY_ENABLE
        key_driver_scan(&ad_key_para);
        ad_key_handle(); // ad按键处理函数
#endif                   //  #if AD_KEY_ENABLE

#if TOUCH_KEY_ENABLE
        key_driver_scan(&touch_key_para);
        touch_key_handle(); // 触摸按键处理函数
#endif
#if SPEED_SCAN_ENABLE
        speed_scan(); // 检测时速
#endif

        mileage_scan(); // 检测大计里程和小计里程

#if ENGINE_SPEED_SCAN_ENABLE
        engine_speed_scan(); // 检测发动机转速
#endif

#if FUEL_CAPACITY_SCAN_ENABLE
        fuel_capacity_scan(); // 油量检测
#endif

#if BATTERY_SCAN_ENABLE
        battery_scan(); // 电池电量检测
#endif

#endif //
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
