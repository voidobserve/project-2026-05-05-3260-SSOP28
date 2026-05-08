#ifndef __AIP3368H_DISPLAY_H__
#define __AIP3368H_DISPLAY_H__ 

#include "my_config.h"

#define AIP3368H_DISPLAY_TEST_ENABLE 1

void aip3368h_display_engine_speed_back_light(void);
void aip3368h_display_exclamation_point(u8 is_enable);
void aip3368h_display_engine_speed_scale_bar(u8 level);
void aip3368h_display_bat_err_icon(u8 is_enable);
void aip3368h_display_err_icon(u8 is_enable);








#if AIP3368H_DISPLAY_TEST_ENABLE
void aip3368h_display_test_engine_speed_scale_bar_1ms_isr(void);

void aip3368h_display_test(void);
#endif

#endif