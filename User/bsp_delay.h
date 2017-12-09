#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#include "main.h"

/* 通过软件实现简单延时 */
void delay_us(u32 t);
void delay_ms(u32 t);

#endif /* __BSP_DELAY_H */
