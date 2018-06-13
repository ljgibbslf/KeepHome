/*************************************************
//File name:	common.c
//File info:	inclueding common function
//Author:		fan Li
//Date:
*************************************************/
#include  "common.h"
//该文件防置常用函数
//----------------------------------------------
// 可以精确延迟
void  Delay_ms(uint32_t myms)
{
    uint32_t delaytime;
    delaytime = HAL_GetTick();
    while( (HAL_GetTick()-delaytime) < myms);
}

//----------------------------------------------
// 此延迟无法精确定时
void Delay(volatile uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
//----------------------------------------------
void  Delay_10us(volatile uint32_t n)
{
	Delay_us(10 * n);
}
//----------------------------------------------
// accurate delay with systick
void  Delay_us(volatile uint32_t n)
{
	uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload = SysTick->LOAD; /* 读取每次的装填值LOAD */
                 
    ticks = n * 168 ;                  /*计算所需要的节拍数*/               
    tcnt = 0;
    told = SysTick->VAL;             /* load now value of systick*/

    while(1)
    {
        tnow = SysTick->VAL;   
        if(tnow != told)
        {   
            /* notice: systick keep decling*/   
            if(tnow < told)
            {
                tcnt += told - tnow;   
            }
            /* this case: the systick was roloaded*/
            else
            {
                tcnt += reload - tnow + told;   
            }        
            told = tnow;

            /*delay end*/
            if(tcnt >= ticks) break;
        }  
    }
}

// 四位十进制数 转换为 四位BCD码 表示的数 2字节
uint16_t  Digital4_BCD4(uint16_t dat16)
{
    uint16_t  retval, tmp16;
    uint16_t  thousand, hundred, ten, unitsdig;
    
    tmp16    = dat16 % 10000;
    thousand = (uint16_t)(tmp16 / 1000);         // 获得千位数
    hundred  = (uint16_t)((tmp16 % 1000) / 100); // 获得百位数数 
    ten      = (uint16_t)((tmp16 % 100) / 10);   // 获得百位数数 
    unitsdig = (uint16_t)(tmp16 % 10);           // 个位数
    
    retval   = (thousand << 12) + (hundred << 8) + (ten << 4) + unitsdig;
    return   retval;
}

// 6位十进制数 转换为 6位BCD码 表示的数 3字节
uint32_t  Digital6_BCD6(uint32_t dat32)
{
    uint32_t  retval, tmp32;
    uint32_t  th100, th10, thousand, hundred, ten, unitsdig;
    
    tmp32    = dat32 % 1000000;
    th100    = (uint32_t)(tmp32 / 100000);
    th10     = (uint32_t)((tmp32 % 100000) / 10000);// 获得千位数
    thousand = (uint32_t)((tmp32 % 10000) / 1000);  // 获得千位数
    hundred  = (uint32_t)((tmp32 % 1000) / 100);    // 获得百位数数 
    ten      = (uint32_t)((tmp32 % 100) / 10);      // 获得百位数数 
    unitsdig = (uint32_t)(tmp32 % 10);              // 个位数
    
    retval   = (th100 << 20) + (th10 << 16) + (thousand << 12) + (hundred << 8) + (ten << 4) + unitsdig;
    return   retval;
}

// 8位十进制数 转换为 8位BCD码 表示的数 4字节
uint32_t  Digital8_BCD8(uint32_t dat32)
{
    uint32_t  retval, tmp32;
    uint32_t  th10000, th1000,th100, th10, thousand, hundred, ten, unitsdig;
    
    tmp32    = dat32 % 100000000;
    th10000  = (uint32_t)(tmp32  / 10000000);            // 获得千万位数
    th1000   = (uint32_t)((tmp32 % 10000000) / 1000000);// 获得百万位数
    th100    = (uint32_t)((tmp32 % 1000000) / 100000);  // 获得十万位数
    th10     = (uint32_t)((tmp32 % 100000) / 10000);// 获得万位数
    thousand = (uint32_t)((tmp32 % 10000) / 1000);  // 获得千位数
    hundred  = (uint32_t)((tmp32 % 1000) / 100);    // 获得百位数数 
    ten      = (uint32_t)((tmp32 % 100) / 10);      // 获得百位数数 
    unitsdig = (uint32_t)(tmp32  % 10);              // 个位数
    
    retval   = (th10000 << 28) + (th1000 << 24) + (th100 << 20) + (th10 << 16) + (thousand << 12) + (hundred << 8) + (ten << 4) + unitsdig;
    return   retval;
}

// 交换一个字节中的高低位
uint8_t  Swap_bit7_bit0(uint8_t inbyte)
{
    uniBit8Byte  in, ret;
    in.abyte = inbyte;
    ret.bits8.b0 = in.bits8.b7;
    ret.bits8.b1 = in.bits8.b6;
    ret.bits8.b2 = in.bits8.b5;
    ret.bits8.b3 = in.bits8.b4;
    ret.bits8.b4 = in.bits8.b3;
    ret.bits8.b5 = in.bits8.b2;
    ret.bits8.b6 = in.bits8.b1;
    ret.bits8.b7 = in.bits8.b0;
    return  ret.abyte;
}






