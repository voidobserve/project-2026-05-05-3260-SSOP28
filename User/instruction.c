#include "instruction.h"

#include <string.h> // memset()

// 用bit定义，来节省空间
// 下面的标志位，有可能是从串口接收到了指令来置位，也有可能是其他的扫描函数更新了状态来置位
volatile bit flag_get_all_status; // 获取所有功能的状态
volatile bit flag_get_gear;       // 获取挡位状态 / 得到了挡位的状态
volatile bit flag_get_battery;    // 获取电池状态 / 得到了电池的状态（电池电量，单位：百分比）
// volatile bit flag_get_brake;        // 获取刹车状态 / 得到了刹车的状态
volatile bit flag_get_left_turn;    // 获取左转向灯的状态 / 得到了左转向灯的状态
volatile bit flag_get_right_turn;   // 获取右转向灯的状态 / 得到了右转向灯的状态
volatile bit flag_get_high_beam;    // 获取远光灯的状态 / 得到了远光灯的状态
volatile bit flag_get_engine_speed; // 获取发动机的转速 / 得到了发动机的转速
volatile bit flag_get_speed;        // 获取时速 / 得到了时速
volatile bit flag_get_fuel;         // 获取油量 / 得到了油量（单位：百分比）
#if TEMP_OF_WATER_SCAN_ENABLE
// volatile bit flag_get_temp_of_water = 0; // 获取水温 / 得到了水温
#endif
// volatile bit flag_update_malfunction_status; // 标志位，更新故障状态
volatile bit flag_update_abs_status; // 标志位，更新abs的状态

volatile bit flag_get_total_mileage;     // 获取大计里程 / 得到了大计里程(数据需要更新)
volatile bit flag_get_sub_total_mileage; // 获取小计里程 / 得到了小计里程(数据需要更新)
// volatile bit flag_get_sub_total_mileage_2; // 获取小计里程2 / 得到了小计里程2(数据需要更新)

// volatile bit flag_get_touch_key_status = 0; // 获取触摸按键的状态
// volatile bit flag_alter_date = 0; // 修改日期
volatile bit flag_alter_time; // 修改时间
volatile bit flag_get_time;   // 获取时间

volatile bit flag_get_voltage_of_battery; // 获取电池电压

// #if TEMP_OF_WATER_SCAN_ENABLE
volatile bit flag_set_temp_of_water_warning = 0; // 设置水温报警
// #endif

volatile bit flag_clear_total_mileage;       // 清除大计里程
volatile bit flag_clear_sub_total_mileage;   // 清除小计里程
volatile bit flag_clear_sub_total_mileage_2; // 清除小计里程2

volatile u8 synchronous_request_status;    // 同步请求状态机
volatile u16 synchronous_request_time_cnt; // 同步请求时间计时

volatile u8 update_time_status; // 更新时间的状态机
// volatile u8 update_date_status = 0; // 更新日期的状态机

volatile u16 update_time_cooling_cnt; // 更新时间的冷却计数
// volatile u16 update_date_cooling_cnt = 0; // 更新日期的冷却计数

// // 存放接收到的设置水温报警的指令中，对应的操作，默认为无操作
// volatile u8 operation_set_temp_of_water_warning = OPERATION_SET_TEMP_OF_WATER_WARNING_NONE;

// 检查接收是否正确的函数，如果接收正确，
// 根据接收到的数据中的指令，给对应的指令的标志位置一
void instruction_scan(void)
{ 
}

void instruction_handle(void)
{ 
}
