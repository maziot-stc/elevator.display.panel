#include "bsp_lattice.h"
#include "bsp_delay.h"

#define ROW P3
#define COL P0

/* 根据此表(数组)下标访问此表, 可以得到选中下标对应行的控制信号 */
static u8 row_table[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

/* 点阵字模表, 此字模只适用与本程序 */
static u8 num_table[] = 
{
        0x00,   0x04,   0x0c,   0x04,   0x34,   0x04,   0x0e,   0x00,   /* -1 */
        0x00,   0x08,   0x38,   0x08,   0x08,   0x08,   0x3e,   0x00,   /* 1 */
        0x00,   0x3c,   0x42,   0x04,   0x08,   0x32,   0x7e,   0x00,   /* 2 */
        0x00,   0x3c,   0x42,   0x1c,   0x02,   0x42,   0x3c,   0x00,   /* 3 */
        0x00,   0x0c,   0x14,   0x24,   0x44,   0x3e,   0x04,   0x00,   /* 4 */
        0x00,   0x7e,   0x40,   0x7c,   0x02,   0x42,   0x3c,   0x00,   /* 5 */
        0x3C,   0x42,   0x40,   0x7c,   0x42,   0x42,   0x3c,   0x00,   /* 6 */
        0x00,   0x7e,   0x02,   0x04,   0x08,   0x10,   0x10,   0x00,   /* 7 */
};

/* 定义一个电梯运动结构体, 记录电梯的运行参数 */
typedef struct
{
        u32 count;              // 中断计数变量
        u32 speed;              // 电梯运行速度
        u32 step;               // 电梯上升或者下降2楼, 则step=2
}action;

/* 定义一个电梯结构体 */
typedef struct
{
        u32 base;               // 当前查表基地址
        u8 current_floor;       // 电梯当前楼层
        action up;              // 电梯上升运动对应的结构体
        action down;            // 电梯下降运动对应的结构体
}elevator;

/* 构建一个电梯对象 */
static elevator ele;

/**
 * @Descroption 电梯面板初始化
 * @param floor 指定当前楼层
 */
void lattice_init(u8 floor)
{
        /* 配置电梯开机默认在哪一个楼层 */
        ele.current_floor = floor;
        
        /* 并且根据当前楼层得到字模的基地址 */
        ele.base = 8 * floor;
        
        /* 配置电梯初始化参数 */
        ele.up.count = 0;
        ele.up.speed = 2;
        ele.up.step = 0;
        
        ele.down.count = 0;
        ele.down.speed = 2;
        ele.down.step = 0;
        
        /* 配置定时器工作方式, 定时器0和定时器1都工作在方式1: 16位定时计数模式 */
        TMOD = 0x11;
        
        /* 给定时器装载计数初值 */
        TH0 = 0x0b;
        TL0 = 0xdc;
        
        TH1 = 0x0b;
        TL1 = 0xdc;
        
        /* 开启总中断和定时器中断 */
        IE |= 0x8a;
}

/**
 * @Descroption 电梯面板开机显示
 */
void lattice_show(void)
{
        u8 i;
        
        /* 根据基地址取出字模, 呈现在 LED 点阵上 */
        for(i = 0; i < 8; i++)
        {
                ROW = row_table[i];
                COL = num_table[ele.base + i];
                delay_us(100);
        }
}

/**
 * @Descroption 从当前楼层上升指定楼层
 * @param up_step 上升 step 层
 */
void lattice_up(u8 step)
{
        ele.up.step = step;
        TR0 = 1;
}

/**
 * @Descroption 从当前楼层下降指定楼层
 * @param up_step 下降 step 层
 */
void lattice_down(u8 step)
{
        ele.down.step = step;
        TR1 = 1;
}

/**
 * @Descroption 从当前楼层跳转到指定楼层
 * @param to 指定楼层
 */
void lattice_go(u8 to)
{
        int step = ele.current_floor - to;
        if(step > 0)
        {
                lattice_down(step);
        }
        else if(step < 0)
        {
                lattice_up(0 - step);
        }
        ele.current_floor = to;
}

/**
 * @Descroption 定时器0中断服务函数
 */
void TIM0_Handler() interrupt 1
{
        TR0 = 0;
        
        TH0 = 0x0b;
        TL0 = 0xdc;
        
        TR0 = 1;
        
        ele.up.count++;
               
        if(ele.up.count >= 8 * ele.up.step * ele.up.speed)
        {
                ele.up.count = 0;
                TR0 = 0;
        }
        
        if(ele.up.count % ele.up.speed == 0)
        {
                ele.base++;
        }
}

/**
 * @Descroption 定时器0中断服务函数
 */
void TIM1_Handler() interrupt 3
{
        TR1 = 0;
        
        TH1 = 0x0b;
        TL1 = 0xdc;
        
        TR1 = 1;
        
        ele.down.count++;
               
        if(ele.down.count >= 8 * ele.down.step * ele.down.speed)
        {
                ele.down.count = 0;
                TR1 = 0;
        }
        
        if(ele.down.count % ele.down.speed == 0)
        {
                ele.base--;
        }
}

