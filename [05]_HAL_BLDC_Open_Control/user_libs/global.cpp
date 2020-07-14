#include "global.h"

uint32_t get_tick_delay(uint32_t last_tick)
{
    uint32_t now_tick, delay_tick;

    now_tick = HAL_GetTick();
    if(now_tick >= last_tick)
    {
        delay_tick = now_tick - last_tick;
    }
    else                            //当前时间比过去时间小，证明tick_count溢出
    {
        delay_tick = now_tick + (0xFFFFFFFF - last_tick);
    }

    return  delay_tick; 
}

uint16_t floatToInt(float f){  
    uint16_t i = 0;  
    if(f>0) //正数
      i = (f*10 + 5)/10;
    else 
			i = 0;

    return i; 
}

