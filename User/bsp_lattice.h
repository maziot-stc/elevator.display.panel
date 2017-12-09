#ifndef __BSP_LATTICE_H
#define __BSP_LATTICE_H

#include "main.h"

void lattice_init(u8 f);
void lattice_show(void);
void lattice_up(u8 up_step);
void lattice_down(u8 down_step);
void lattice_go(u8 to);

#endif /* __BSP_LATTICE_H */
