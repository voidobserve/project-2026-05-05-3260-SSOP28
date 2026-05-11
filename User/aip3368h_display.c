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
    // 默认熄灭指示灯：
    aip3368h_display_buff[0] &= ~(0x01 << 1); // 发动机转速圆盘，感叹号标识

    if (is_enable)
    {
        aip3368h_display_buff[0] |= 0x01 << 1; // 发动机转速圆盘，感叹号标识
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
    // 默认先清空显示：
    aip3368h_display_buff[2] &= ~(0x01 << 10); // 电池电量低，第 1 格指示灯（红）
    aip3368h_display_buff[2] &= ~(0x01 << 11); // 电池电量低，第 0 格指示灯（红）

    if (is_enable)
    {
        aip3368h_display_buff[2] |= 0x01 << 10; // 电池电量低，第 1 格指示灯（红）
        aip3368h_display_buff[2] |= 0x01 << 11; // 电池电量低，第 0 格指示灯（红）
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
void aip3368h_display_fuel_level(aip3368h_display_fuel_level_t level)
{
    // 先清空显示，之后再根据传参点亮对应的指示灯
    aip3368h_display_buff[2] &= ~(0x01 << 15); // 油量，第 0 格指示灯（红）
    aip3368h_display_buff[2] &= ~(0x01 << 14); // 油量，第 1 格指示灯（绿）
    aip3368h_display_buff[2] &= ~(0x01 << 0);  // 油量，第 2 格指示灯（绿）
    aip3368h_display_buff[2] &= ~(0x01 << 1);  // 油量，第 3 格指示灯（绿）
    aip3368h_display_buff[2] &= ~(0x01 << 2);  // 油量，第 4 格指示灯（绿）

    // 如果 level == AIP3368H_DISPLAY_FUEL_LEVEL_4，那么0~4对应的指示灯都点亮
    switch (level)
    {
    case AIP3368H_DISPLAY_FUEL_LEVEL_4:
        aip3368h_display_buff[2] |= (0x01 << 2); // 油量，第 4 格指示灯（绿）
    case AIP3368H_DISPLAY_FUEL_LEVEL_3:
        aip3368h_display_buff[2] |= (0x01 << 1); // 油量，第 3 格指示灯（绿）
    case AIP3368H_DISPLAY_FUEL_LEVEL_2:
        aip3368h_display_buff[2] |= (0x01 << 0); // 油量，第 2 格指示灯（绿）
    case AIP3368H_DISPLAY_FUEL_LEVEL_1:
        aip3368h_display_buff[2] |= (0x01 << 14); // 油量，第 1 格指示灯（绿）
    case AIP3368H_DISPLAY_FUEL_LEVEL_0:
        aip3368h_display_buff[2] |= (0x01 << 15); // 油量，第 0 格指示灯（红）
    default:
        break;
    }
}

/**
 * @brief 显示里程的km字样图标
 *
 */
void aip3368h_display_mileage_km_icon(u8 is_enable)
{
    aip3368h_display_buff[5] &= 0x01 << 0; // 里程 km字样 指示灯，第 1 格
    aip3368h_display_buff[5] &= 0x01 << 1; // 里程 km字样 指示灯，第 0 格

    if (is_enable)
    {
        aip3368h_display_buff[5] |= 0x01 << 0; // 里程 km字样 指示灯，第 1 格
        aip3368h_display_buff[5] |= 0x01 << 1; // 里程 km字样 指示灯，第 0 格
    }
}

/**
 * @brief 7段数码管段码定义 (a,b,c,d,e,f,g)
 *        对应二进制位: bit0=a, bit1=b, bit2=c, bit3=d, bit4=e, bit5=f, bit6=g
 */
static const u8 digit_segment_code[10] = {
    0x3F, // 0: abcdef
    0x06, // 1: bc
    0x5B, // 2: abdeg
    0x4F, // 3: abcdg
    0x66, // 4: bcfg
    0x6D, // 5: acdfg
    0x7D, // 6: acdefg
    0x07, // 7: abc
    0x7F, // 8: abcdefg
    0x6F  // 9: abcdfg
};

/**
 * @brief 里程各位数码管的段映射表
 *        每个位置有7个段(a-g)，需要映射到不同的buff数组和bit位
 *        结构: [bit_position][segment] ->(映射)-> {buff_index, bit_offset}
 */
typedef struct
{
    u8 buff_index; // aip3368h_display_buff 数组索引
    u8 bit_offset; // 在aip3368h_display_buff 数组索引中的bit偏移
} segment_mapping_t;

// 里程6位数码管，每位的7个段(a-g)的映射关系
static const segment_mapping_t mileage_segment_map[6][7] = {
    // 第0位 ( 最左边 )
    {
        {3, 13}, // a段 -> buff[3], bit13
        {3, 12}, // b段 -> buff[3], bit12
        {2, 13}, // c段 -> buff[2], bit13
        {3, 8},  // d段 -> buff[3], bit8
        {3, 9},  // e段 -> buff[3], bit9
        {3, 11}, // f段 -> buff[3], bit11
        {3, 10}  // g段 -> buff[3], bit10
    },
    // 第1位 (   )
    {
        {3, 0}, // a段 -> buff[3], bit0
        {3, 2}, // b段 -> buff[3], bit2
        {3, 5}, // c段 -> buff[3], bit5
        {3, 7}, // d段 -> buff[3], bit7
        {3, 6}, // e段 -> buff[3], bit6
        {3, 3}, // f段 -> buff[3], bit3
        {3, 4}  // g段 -> buff[3], bit4
    },
    // 第2位 (   )
    {
        {4, 14}, // a段 -> buff[4], bit14
        {4, 12}, // b段 -> buff[4], bit12
        {4, 9},  // c段 -> buff[4], bit9
        {4, 8},  // d段 -> buff[4], bit8
        {4, 10}, // e段 -> buff[4], bit10
        {4, 13}, // f段 -> buff[4], bit13
        {4, 11}  // g段 -> buff[4], bit11
    },
    // 第3位 (   )
    {
        {4, 1},  // a段 -> buff[4], bit1
        {5, 15}, // b段 -> buff[5], bit15
        {4, 4},  // c段 -> buff[4], bit4
        {4, 6},  // d段 -> buff[4], bit6
        {4, 7},  // e段 -> buff[4], bit7
        {4, 0},  // f段 -> buff[4], bit0
        {4, 2}   // g段 -> buff[4], bit2
    },
    // 第4位 (   )
    {
        {5, 11}, // a段 -> buff[5], bit11
        {5, 10}, // b段 -> buff[5], bit10
        {4, 3},  // c段 -> buff[4], bit3
        {4, 5},  // d段 -> buff[4], bit5
        {5, 13}, // e段 -> buff[5], bit13
        {5, 14}, // f段 -> buff[5], bit14
        {5, 12}  // g段 -> buff[5], bit12
    },
    // 第5位 ( 最右边 )
    {
        {5, 3}, // a段 -> buff[5], bit3
        {5, 2}, // b段 -> buff[5], bit2
        {5, 4}, // c段 -> buff[5], bit4
        {5, 7}, // d段 -> buff[5], bit7
        {5, 9}, // e段 -> buff[5], bit9
        {5, 6}, // f段 -> buff[5], bit6
        {5, 5}  // g段 -> buff[5], bit5
    }};

/**
 * @brief 里程显示中，在第 x 位显示数字
 *
 * @attention 是 aip3368h_display_mileage() 的子函数
 *
 * @param bit_x 0 ~ 5 (0=个位, 5=十万位)
 * @param number 0 ~ 9
 */
static void __aip3368h_display_mileage_bit_x__(u8 bit_x, u8 number)
{
    u8 seg;
    // 参数有效性检查（为了节省程序空间，这里可以省略）
    // if (bit_x > 5 || number > 9)
    // {
    //     return;
    // }

    // 获取该数字对应的7段码 (要显示的数字 --> 七段码)
    u8 segment_code = digit_segment_code[number];

    // 根据段码设置对应的buff位
    for (seg = 0; seg < 7; seg++)
    {
        // 检查该段是否需要点亮 (segment_code的对应bit是否为1)
        if (segment_code & (1 << seg))
        {
            // 点亮该段
            aip3368h_display_buff[mileage_segment_map[bit_x][seg].buff_index] |=
                (0x01 << mileage_segment_map[bit_x][seg].bit_offset);
        } 
    }
}

/**
 * @brief 显示里程
 *
 * @param mileage
 * @param is_displaying_total_mileage 是否显示总里程。0：显示当前里程(TRIP)，1：显示总里程(ODO)
 */
void aip3368h_display_mileage(u32 mileage, u8 is_displaying_total_mileage)
{
    u8 i; // 循环计数值
    u8 j; // 循环计数值

    // 默认先清空有关里程的显示
    aip3368h_display_buff[3] &= ~(0x01 << 15); // 大计里程 ODO 指示灯，第 0 格
    aip3368h_display_buff[3] &= ~(0x01 << 14); // 大计里程 ODO 指示灯，第 1 格

    aip3368h_display_buff[3] &= ~(0x01 << 1);  // 小计里程 TRIP 指示灯，第 0 格
    aip3368h_display_buff[4] &= ~(0x01 << 15); // 小计里程 TRIP 指示灯，第 1 格
    aip3368h_display_buff[5] &= ~(0x01 << 8);  // 里程 小数点 指示灯
    aip3368h_display_mileage_km_icon(1);       // 显示里程 km字样 指示灯

    // 清除第 0 ~ 5 位数码管的显示
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++) // 第 i 位数码管的 a ~ g 段
        {
            aip3368h_display_buff[mileage_segment_map[i][j].buff_index] &=
                ~(0x01 << mileage_segment_map[i][j].bit_offset);
        }
    }

#if 1
    if (is_displaying_total_mileage)
    {
        aip3368h_display_buff[3] |= (0x01 << 15); // 大计里程 ODO 指示灯，第 0 格
        aip3368h_display_buff[3] |= (0x01 << 14); // 大计里程 ODO 指示灯，第 1 格

        // for (i = 0; i < 6; i++)
        // {
        //     __aip3368h_display_mileage_bit_x__(i, mileage % 10);
        //     mileage /= 10;
        // }
    }
    else
    {
        aip3368h_display_buff[3] |= (0x01 << 1);  // 小计里程 TRIP 指示灯，第 0 格
        aip3368h_display_buff[4] |= (0x01 << 15); // 小计里程 TRIP 指示灯，第 1 格
        aip3368h_display_buff[5] |= (0x01 << 8);  // 里程 小数点 指示灯

        // for (i = 0; i < 6; i++)
        // {
        //     __aip3368h_display_mileage_bit_x__(i, mileage % 10);
        //     mileage /= 10;
        // }
    }
#endif
}

#if AIP3368H_DISPLAY_TEST_ENABLE

#if 0
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
#endif

#if 0
/**
 * @brief 测试油量的刻度条显示，需要放在1ms的中断内调用
 *
 */
void aip3368h_display_test_fuel_level_1ms_isr(void)
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
    if (level > AIP3368H_DISPLAY_FUEL_LEVEL_4)
    {
        level = 0;
    }

    aip3368h_display_fuel_level(level);
}
#endif

#if 0
/**
 * @brief 测试里程显示，需要放在1ms的中断内调用
 *
 */
void aip3368h_display_test_mileage_1ms_isr(void)
{
    static u16 cnt = 0;
    static u8 dir = 0;
    u8 i; // 循环计数值
    u8 j; // 循环计数值

    cnt++;
    if (cnt < 500)
    {
        return;
    }
    else
    {
        cnt = 0;
    }

    if (dir == 0)
    {
        aip3368h_display_buff[3] &= ~(0x01 << 15); // 大计里程 ODO 指示灯，第 0 格
        aip3368h_display_buff[3] &= ~(0x01 << 14); // 大计里程 ODO 指示灯，第 1 格

        aip3368h_display_buff[3] &= ~(0x01 << 1);  // 小计里程 TRIP 指示灯，第 0 格
        aip3368h_display_buff[4] &= ~(0x01 << 15); // 小计里程 TRIP 指示灯，第 1 格
        aip3368h_display_buff[5] &= ~(0x01 << 8);  // 里程 小数点 指示灯

        aip3368h_display_mileage_km_icon(dir);

        // 清除第 0 ~ 5 位数码管的显示
        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < 7; j++) // 第 i 位数码管的 a ~ g 段
            {
                aip3368h_display_buff[mileage_segment_map[i][j].buff_index] &=
                    ~(0x01 << mileage_segment_map[i][j].bit_offset);
            }
        }

        dir = 1;
    }
    else
    {
        aip3368h_display_buff[3] |= (0x01 << 15); // 大计里程 ODO 指示灯，第 0 格
        aip3368h_display_buff[3] |= (0x01 << 14); // 大计里程 ODO 指示灯，第 1 格

        aip3368h_display_buff[3] |= (0x01 << 1);  // 小计里程 TRIP 指示灯，第 0 格
        aip3368h_display_buff[4] |= (0x01 << 15); // 小计里程 TRIP 指示灯，第 1 格
        aip3368h_display_buff[5] |= (0x01 << 8);  // 里程 小数点 指示灯

        aip3368h_display_mileage_km_icon(dir);

        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < 7; j++)
            {
                aip3368h_display_buff[mileage_segment_map[i][j].buff_index] |=
                    (0x01 << mileage_segment_map[i][j].bit_offset);
            }
        }

        dir = 0;
    }
}

#endif

#if 0
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

#endif
