#include "aip3368h_display.h"

//   aip3368h_display_buff[6] = 0x01 << 7;

void aip3368h_display_speed(void)
{
}

// 显示发动机转速圆盘对应的背光灯
void aip3368h_display_engine_speed_back_light(void)
{
    aip3368h_display_buff[0] |= 0x01 << 15; // 发动机转速圆盘，第 5 格对应的背光灯（白）

    aip3368h_display_buff[1] |= 0x01 << 0;  // 发动机转速圆盘，第 0 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 4;  // 发动机转速圆盘，第 1 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 8;  // 发动机转速圆盘，第 2 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 12; // 发动机转速圆盘，第 3 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 15; // 发动机转速圆盘，第 4 格对应的背光灯（白）
}

// 显示发动机转速圆盘的感叹号标识
void aip3368h_display_exclamation_point(u8 is_enable)
{
    if (is_enable)
    {
        aip3368h_display_buff[0] |= 0x01 << 1; // 发动机转速圆盘，感叹号标识
    }
    else
    {
        aip3368h_display_buff[0] &= ~(0x01 << 1); // 发动机转速圆盘，感叹号标识
    }
}

/**
 * @brief 发动机转速对圆盘，上面的转速刻度条
 *
 * @param level 0 ~ 12
 */
void aip3368h_display_engine_speed_scale_bar(u8 level)
{
    // 先清空显示，再根据传参重新点亮对应的灯光
    aip3368h_display_buff[1] &= ~(0x01 << 2);  // 发动机转速，第 0 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 3);  // 发动机转速，第 1 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 5);  // 发动机转速，第 2 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 6);  // 发动机转速，第 3 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 7);  // 发动机转速，第 4 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 9);  // 发动机转速，第 5 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 10); // 发动机转速，第 6 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 11); // 发动机转速，第 7 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 13); // 发动机转速，第 8 格指示灯（绿）
    aip3368h_display_buff[1] &= ~(0x01 << 14); // 发动机转速，第 9 格指示灯（红）
    aip3368h_display_buff[0] &= ~(0x01 << 8);  // 发动机转速，第 10 格指示灯（红）
    aip3368h_display_buff[0] &= ~(0x01 << 9);  // 发动机转速，第 11 格指示灯（红）

    // level == 12，那么0~11格指示灯都点亮
    switch (level)
    {
    case 12:
        aip3368h_display_buff[0] |= (0x01 << 9); // 发动机转速，第 11 格指示灯（红）
    case 11:
        aip3368h_display_buff[0] |= (0x01 << 8); // 发动机转速，第 10 格指示灯（红）
    case 10:
        aip3368h_display_buff[1] |= (0x01 << 14); // 发动机转速，第 9 格指示灯（红）
    case 9:
        aip3368h_display_buff[1] |= (0x01 << 13); // 发动机转速，第 8 格指示灯（绿）
    case 8:
        aip3368h_display_buff[1] |= (0x01 << 11); // 发动机转速，第 7 格指示灯（绿）
    case 7:
        aip3368h_display_buff[1] |= (0x01 << 10); // 发动机转速，第 6 格指示灯（绿）
    case 6:
        aip3368h_display_buff[1] |= (0x01 << 9); // 发动机转速，第 5 格指示灯（绿）
    case 5:
        aip3368h_display_buff[1] |= (0x01 << 7); // 发动机转速，第 4 格指示灯（绿）
    case 4:
        aip3368h_display_buff[1] |= (0x01 << 6); // 发动机转速，第 3 格指示灯（绿）
    case 3:
        aip3368h_display_buff[1] |= (0x01 << 5); // 发动机转速，第 2 格指示灯（绿）
    case 2:
        aip3368h_display_buff[1] |= (0x01 << 3); // 发动机转速，第 1 格指示灯（绿）
    case 1:
        aip3368h_display_buff[1] |= (0x01 << 2); // 发动机转速，第 0 格指示灯（绿）
        break;
    case 0:
        break;
    default:
        break;
    }
}

/**
 * @brief 显示电池电量故障图标
 *
 * @param is_enable 0: 不显示 1：显示
 */
void aip3368h_display_bat_err_icon(u8 is_enable)
{
    if (is_enable)
    {
        aip3368h_display_buff[2] |= 0x01 << 10; // 电池电量低，第 1 格指示灯（红）
        aip3368h_display_buff[2] |= 0x01 << 11; // 电池电量低，第 0 格指示灯（红）
    }
    else
    {
        aip3368h_display_buff[2] &= ~(0x01 << 10); // 电池电量低，第 1 格指示灯（红）
        aip3368h_display_buff[2] &= ~(0x01 << 11); // 电池电量低，第 0 格指示灯（红）
    }
}

/**
 * @brief 显示故障图标
 *
 * @param is_enable 0: 不显示 1：显示
 */
void aip3368h_display_err_icon(u8 is_enable)
{
    // 默认先清空显示
    aip3368h_display_buff[2] &= ~(0x01 << 4); // 故障，第 1 格指示灯（红）
    aip3368h_display_buff[2] &= ~(0x01 << 5); // 故障，第 0 格指示灯（红）

    if (is_enable)
    {
        aip3368h_display_buff[2] |= 0x01 << 4; // 故障，第 1 格指示灯（红）
        aip3368h_display_buff[2] |= 0x01 << 5; // 故障，第 0 格指示灯（红）
    }
}

// USER_TO_DO 需要给传参定义一个枚举类型，方便索引和维护
/**
 * @brief
 *
 * @param level
 */
void aip3368h_display_fuel_level(u8 level)
{
    // 先清空显示，之后再根据传参点亮对应的指示灯
    switch (level)
    {
    }
}

#if AIP3368H_DISPLAY_TEST_ENABLE

/**
 * @brief 测试发动机转速的刻度条显示，需要放在1ms的中断内调用
 *
 * @return * void
 */
void aip3368h_display_test_engine_speed_scale_bar_1ms_isr(void)
{
    static u16 cnt = 0;
    static u8 level = 0;

    cnt++;
    if (cnt < 500)
    {
        return;
    }
    else
    {
        cnt = 0;
    }

    level++;
    if (level > 12)
    {
        level = 0;
    }

    aip3368h_display_engine_speed_scale_bar(level);
}

void aip3368h_display_test(void)
{
    aip3368h_display_buff[0] |= 0x01 << 0;  // NC
    aip3368h_display_buff[0] |= 0x01 << 1;  // 发动机转速圆盘，感叹号标识
    aip3368h_display_buff[0] |= 0x01 << 2;  // NC
    aip3368h_display_buff[0] |= 0x01 << 3;  // NC
    aip3368h_display_buff[0] |= 0x01 << 4;  // NC
    aip3368h_display_buff[0] |= 0x01 << 5;  // NC
    aip3368h_display_buff[0] |= 0x01 << 6;  // NC
    aip3368h_display_buff[0] |= 0x01 << 7;  // NC
    aip3368h_display_buff[0] |= 0x01 << 8;  // 发动机转速，第 10 格指示灯（红）
    aip3368h_display_buff[0] |= 0x01 << 9;  // 发动机转速，第 11 格指示灯（红）
    aip3368h_display_buff[0] |= 0x01 << 10; // NC
    aip3368h_display_buff[0] |= 0x01 << 11; // NC
    aip3368h_display_buff[0] |= 0x01 << 12; // NC
    aip3368h_display_buff[0] |= 0x01 << 13; // NC
    aip3368h_display_buff[0] |= 0x01 << 14; // NC
    aip3368h_display_buff[0] |= 0x01 << 15; // 发动机转速圆盘，第 5 格对应的背光灯（白）

    aip3368h_display_buff[1] |= 0x01 << 0;  // 发动机转速圆盘，第 0 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 1;  // NC
    aip3368h_display_buff[1] |= 0x01 << 2;  // 发动机转速，第 0 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 3;  // 发动机转速，第 1 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 4;  // 发动机转速圆盘，第 1 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 5;  // 发动机转速，第 2 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 6;  // 发动机转速，第 3 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 7;  // 发动机转速，第 4 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 8;  // 发动机转速圆盘，第 2 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 9;  // 发动机转速，第 5 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 10; // 发动机转速，第 6 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 11; // 发动机转速，第 7 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 12; // 发动机转速圆盘，第 3 格对应的背光灯（白）
    aip3368h_display_buff[1] |= 0x01 << 13; // 发动机转速，第 8 格指示灯（绿）
    aip3368h_display_buff[1] |= 0x01 << 14; // 发动机转速，第 9 格指示灯（红）
    aip3368h_display_buff[1] |= 0x01 << 15; // 发动机转速圆盘，第 4 格对应的背光灯（白）

    aip3368h_display_buff[2] |= 0x01 << 0;  // 油量，第 2 格指示灯（绿）
    aip3368h_display_buff[2] |= 0x01 << 1;  // 油量，第 3 格指示灯（绿）
    aip3368h_display_buff[2] |= 0x01 << 2;  // 油量，第 4 格指示灯（绿）
    aip3368h_display_buff[2] |= 0x01 << 3;  // NC
    aip3368h_display_buff[2] |= 0x01 << 4;  // 故障，第 1 格指示灯（红）
    aip3368h_display_buff[2] |= 0x01 << 5;  // 故障，第 0 格指示灯（红）
    aip3368h_display_buff[2] |= 0x01 << 6;  // NC
    aip3368h_display_buff[2] |= 0x01 << 7;  // 时速，第 2 位，d 段（绿）
    aip3368h_display_buff[2] |= 0x01 << 8;  // 时速，第 0 位，第 0 个指示灯（从上往下数）（绿）
    aip3368h_display_buff[2] |= 0x01 << 9;  // NC
    aip3368h_display_buff[2] |= 0x01 << 10; // 电池电量低，第 1 格指示灯（红）
    aip3368h_display_buff[2] |= 0x01 << 11; // 电池电量低，第 0 格指示灯（红）
    aip3368h_display_buff[2] |= 0x01 << 12; // NC
    aip3368h_display_buff[2] |= 0x01 << 13; // 里程，第 0 位，c 段（蓝）
    aip3368h_display_buff[2] |= 0x01 << 14; // 油量，第 1 格指示灯（绿）
    aip3368h_display_buff[2] |= 0x01 << 15; // 油量，第 0 格指示灯（红）

    aip3368h_display_buff[3] |= 0x01 << 0;  // 里程，第 1 位，a 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 1;  // 小计里程 TRIP 指示灯，第 0 格
    aip3368h_display_buff[3] |= 0x01 << 2;  // 里程，第 1 位，b 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 3;  // 里程，第 1 位，f 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 4;  // 里程，第 1 位，g 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 5;  // 里程，第 1 位，c 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 6;  // 里程，第 1 位，e 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 7;  // 里程，第 1 位，d 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 8;  // 里程，第 0 位，d 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 9;  // 里程，第 0 位，e 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 10; // 里程，第 0 位，g 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 11; // 里程，第 0 位，f 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 12; // 里程，第 0 位，b 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 13; // 里程，第 0 位，a 段（蓝）
    aip3368h_display_buff[3] |= 0x01 << 14; // 大计里程 ODO 指示灯，第 1 格
    aip3368h_display_buff[3] |= 0x01 << 15; // 大计里程 ODO 指示灯，第 0 格

    aip3368h_display_buff[4] |= 0x01 << 0;  // 里程，第 3 位，f 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 1;  // 里程，第 3 位，a 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 2;  // 里程，第 3 位，g 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 3;  // 里程，第 4 位，c 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 4;  // 里程，第 3 位，c 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 5;  // 里程，第 4 位，d 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 6;  // 里程，第 3 位，d 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 7;  // 里程，第 3 位，e 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 8;  // 里程，第 2 位，d 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 9;  // 里程，第 2 位，c 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 10; // 里程，第 2 位，e 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 11; // 里程，第 2 位，g 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 12; // 里程，第 2 位，b 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 13; // 里程，第 2 位，f 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 14; // 里程，第 2 位，a 段（蓝）
    aip3368h_display_buff[4] |= 0x01 << 15; // 小计里程 TRIP 指示灯，第 1 格

    aip3368h_display_buff[5] |= 0x01 << 0;  // 里程 km字样 指示灯，第 1 格
    aip3368h_display_buff[5] |= 0x01 << 1;  // 里程 km字样 指示灯，第 0 格
    aip3368h_display_buff[5] |= 0x01 << 2;  // 里程，第 5 位，b 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 3;  // 里程，第 5 位，a 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 4;  // 里程，第 5 位，c 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 5;  // 里程，第 5 位，g 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 6;  // 里程，第 5 位，f 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 7;  // 里程，第 5 位，d 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 8;  // 里程 小数点 指示灯
    aip3368h_display_buff[5] |= 0x01 << 9;  // 里程，第 5 位，e 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 10; // 里程，第 4 位，b 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 11; // 里程，第 4 位，a 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 12; // 里程，第 4 位，g 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 13; // 里程，第 4 位，e 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 14; // 里程，第 4 位，f 段（蓝）
    aip3368h_display_buff[5] |= 0x01 << 15; // 里程，第 3 位，b 段（蓝）

    aip3368h_display_buff[6] |= 0x01 << 0;  // 时速，第 2 位，f 段（绿）
    aip3368h_display_buff[6] |= 0x01 << 1;  // 时速，第 2 位，b 段（绿）
    aip3368h_display_buff[6] |= 0x01 << 2;  // 时速，第 2 位，a 段（绿）
    aip3368h_display_buff[6] |= 0x01 << 3;  // 时速圆盘对应的刻度条，第 8 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 4;  // 时速圆盘对应的刻度条，第 9 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 5;  // 时速圆盘对应的刻度条，第 10 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 6;  // 时速圆盘对应的刻度条，第 11 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 7;  // 时速圆盘对应的刻度条，第 12 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 8;  // 时速圆盘对应的刻度条，第 13 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 9;  // 时速圆盘对应的刻度条，第 14 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 10; // 时速圆盘对应的刻度条，第 15 个指示灯（蓝）
    aip3368h_display_buff[6] |= 0x01 << 11; // 时速 km字样 指示灯，第 1 格（绿）
    aip3368h_display_buff[6] |= 0x01 << 12; // 时速 km字样 指示灯，第 0 格（绿）
    aip3368h_display_buff[6] |= 0x01 << 13; // 时速，第 2 位，g 段（绿）
    aip3368h_display_buff[6] |= 0x01 << 14; // 时速，第 2 位，e 段（绿）
    aip3368h_display_buff[6] |= 0x01 << 15; // 时速，第 2 位，c 段（绿）

    aip3368h_display_buff[7] |= 0x01 << 0;  // 时速，第 1 位，e 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 1;  // 时速，第 1 位，c 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 2;  // 时速，第 1 位，d 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 3;  // 时速，第 0 位，第 1 个指示灯（从上往下数）（绿）
    aip3368h_display_buff[7] |= 0x01 << 4;  // 时速圆盘对应的刻度条，第 3 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 5;  // 时速圆盘对应的刻度条，第 2 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 6;  // 时速圆盘对应的刻度条，第 1 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 7;  // 时速圆盘对应的刻度条，第 0 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 8;  // 时速圆盘对应的刻度条，第 4 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 9;  // 时速圆盘对应的刻度条，第 5 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 10; // 时速圆盘对应的刻度条，第 6 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 11; // 时速圆盘对应的刻度条，第 7 个指示灯（蓝）
    aip3368h_display_buff[7] |= 0x01 << 12; // 时速，第 1 位，g 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 13; // 时速，第 1 位，f 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 14; // 时速，第 1 位，b 段（绿）
    aip3368h_display_buff[7] |= 0x01 << 15; // 时速，第 1 位，a 段（绿）
}
#endif
