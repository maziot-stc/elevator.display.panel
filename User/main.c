#include "main.h"
#include "bsp_delay.h"
#include "bsp_lattice.h"
#include "bsp_key.h"

int main()
{
        /* 设置当期楼层为 1 楼 */
        lattice_init(1);
        
        while(1)
        {
                /* 循环里面读取按键键值, 根据键值控制电梯显示面板 */
                key_control(key_scan());
                lattice_show();
        }
}
