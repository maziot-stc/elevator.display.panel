#include "bsp_delay.h"
#include <intrins.h>

/** 
 * @Description 软件简单延时，微秒级延时
 * @param t 延时的微秒数
 */
void delay_us(u32 t)
{
        u32 i;
        for(i = t; i > 0; i--)
                _nop_();
}

/** 
 * @Description 软件简单延时，毫秒级延时
 * @param t 延时的微秒数
 */
void delay_ms(u32 t)
{
        u32 i;
        for(i = t; i > 0; i--)
                delay_us(1000);
}
