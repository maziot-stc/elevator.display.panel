#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_lattice.h"

#define GPIO_KEY P1

/** 
 * @Description 按键扫描函数(最多支持同时扫描8个按键)
 * @return u8   按键键值
 */
u8 Key_Scan(void)
{
        /* 保存按键键值的变量, 默认值0xff表示没有按键按下 */
        u8 keyValue = 0xff;
        
        /* 用于松手检测的累加变量 */
        int i = 0;
        
        /* 这里在1ms前后检测两边是为了滤除按键抖动产生的尖峰脉冲 */
        if(GPIO_KEY != 0xff)
        {
                delay_ms(1);
                
                /* 如果1ms前后检测都是低电平的话, 就说明是真的有按键按下 */
                if(GPIO_KEY != 0xff)
                {
                        /* 真的有按键按下, 则将按键键值存入keyValue中 */
                        keyValue = GPIO_KEY;
                        
                        /* 这里是松手检测, 在20ms内按键没有放开, 程序会一直停在此处 */
                        /* 倘若50ms期间, 松开了按键, 则会跳出此while循环 */
                        /* 也就是说：按键没有松开的话, 程序不会去做其他的事情 */
                        /* 当然也有松手检测的超时时间, 就是我们设置的20ms */
                        while((i < 20) && (GPIO_KEY != 0xff))
                        {
                                delay_ms(1);
                                i++;
                        }
                }
        }
        
        /* 返回按键的键值, 通过解析这个键值, 就能知道是哪一个按键按下 */
        return keyValue;
}

/** 
 * @Description 按键扫描函数(最多支持同时扫描8个按键)
 * @return u8   按键键值
 */
void Key_Control(u8 keyValue)
{
        /* 根据捕捉的键值解析出按下的键, 并作出相应的处理 */
        switch(keyValue)
        {
                case(0xfe):
                        lattice_go(0);
                        break;
                
                case(0xfd):
                        lattice_go(1);
                        break;
                
                case(0xfb):
                        lattice_go(2);
                        break;
                
                case(0xf7):
                        lattice_go(3);
                        break;
                
                case(0xef):
                        lattice_go(4);
                        break;
                
                case(0xdf):
                        lattice_go(5);
                        break;
                
                case(0xbf):
                        lattice_go(6);
                        break;
                
                case(0x7f):
                        lattice_go(7);
                        break;
                default:
                        break;
        }
}
