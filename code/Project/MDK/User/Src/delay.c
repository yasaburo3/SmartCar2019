#include "delay.h"

void delay_us(uint32_t us)//延世不要超过400ms
{
	

    if(us == 0)   return;
	us*=40;

    SysTick->CTRL = 0x00;//先关了 systick ,清标志位
    SysTick->LOAD = us;//设置延时时间
    SysTick->VAL = 0x00;//清空计数器
    SysTick->CTRL = ( 0 | SysTick_CTRL_ENABLE_Msk     //使能 systick
                  //| SysTick_CTRL_TICKINT_Msk        //使能中断 (注释了表示关闭中断)
                    | SysTick_CTRL_CLKSOURCE_Msk      //时钟源选择 (core clk)
                );
    while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//等待时间到
}