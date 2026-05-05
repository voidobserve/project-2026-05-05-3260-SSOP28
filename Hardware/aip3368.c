#include "aip3368.h"

#include "my_config.h"

#if 1 // AIP3368H_MODULE



// 显存
volatile u16 aip3368h_display_buff[AIP3368H_DEV_NUM];


static void aip3368h_module_send_data_to_one_dev(u16 dat)
{
    u16 i;
    // PDM = 1;

    for (i = 0; i < 16; i++)
    {
        DIO = dat & 0x8000 ? 1 : 0;

        aip3368h_delay();
        DCK = 1;
        aip3368h_delay();
        dat <<= 1;
        DCK = 0;
        aip3368h_delay();
    }
    // PDM = 0;
}

static void aip3368h_module_send_data_to_all_dev(u16 *buff, u8 len)
{
    u8 i;

    // EA = 0;
    // 开始
    DCK = 0;
    LAT = 0;
    // PDM = 1;
    aip3368h_delay();

    // 一帧完整数据
    for (i = 0; i < len; i++)
    {
        aip3368h_module_send_data_to_one_dev(buff[i]);
    }

    // 结束
    // PDM = 1;
    LAT = 1;
    aip3368h_delay();
    LAT = 0;
    // PDM = 0;
    aip3368h_delay();
    DIO = 0;
    
    // EA = 1;
}

#define AIP3368H_FLASH_TEST_ENABLE          0
void aip3368h_module_display(void)
{
    if (!systimer_flag_is_valid(SYSTIME_FLAG_50MS))
        return;

#if AIP3368H_FLASH_TEST_ENABLE
    // 闪烁测试
    if ( aip3368h_display_buff[0] == 0x0000)
        memset( aip3368h_display_buff, 0xFF, sizeof( aip3368h_display_buff));
    else
        memset( aip3368h_display_buff, 0x00, sizeof( aip3368h_display_buff));
#endif

    aip3368h_module_send_data_to_all_dev( aip3368h_display_buff, AIP3368H_DEV_NUM);
}

void aip3368h_module_clear(void)
{
    memset( aip3368h_display_buff, 0x00, sizeof(aip3368h_display_buff));
    aip3368h_module_send_data_to_all_dev(aip3368h_display_buff, AIP3368H_DEV_NUM);
}

void aip3368h_module_init(void)
{
    // memset(aip3368h_display_buff, 0xF0, sizeof(aip3368h_display_buff));
    for(act_tmp=0;act_tmp<16;act_tmp++){
		aip3368h_display_buff[act_tmp]=0x0000;
	}

    GPIO_Init(P05F, OUTPUT);
    GPIO_Init(P06F, OUTPUT);
    GPIO_Init(P07F, OUTPUT);
    GPIO_Init(P34F, OUTPUT);
    DIO = 0;
    DCK = 0;
    LAT = 0;
    // PDM = 1;
    aip3368h_module_send_data_to_all_dev(aip3368h_display_buff, AIP3368H_DEV_NUM);
}

void aip3368h_module_uninit(void)
{
    aip3368h_module_clear();    // 清屏
    GPIO_Init(P05F, 0);
    GPIO_Init(P06F, 0);
    GPIO_Init(P07F, 0);
    GPIO_Init(P34F, 0);
}

#endif
