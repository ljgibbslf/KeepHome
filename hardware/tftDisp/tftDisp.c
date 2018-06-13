/*************************************************
// 文件说明:      此文件为针对用户层面的函数集
//                建立在在底层驱动文件和基本显示函数之上，用户可以增加相应的显示功能
//                因为这里的文件是针对用户层面的，所以软件有很强的移植性
// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/

/* --------------------------Includes ---------------------------------------------*/
#include "tftDisp.h"
#include <string.h>


/* ----------------------End of Includes ---------------------------------------------*/
extern struTimerTask      tim_task;
/************************************************************************
// 函 数 名:      LCD_Digital_U16_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
// 函数功能描述:  显示十进制5位数字, 24*24点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景  
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_U16_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[7];
    
    memset(dig,'\0',6);
    dig[0] = (char)(digital / 10000) + 0x30;           // 取出万位数
    dig[1] = (char)( (digital % 10000) / 1000) + 0x30; // 取出千位数
    dig[2] = (char)( (digital % 1000 ) / 100 ) + 0x30; // 取出百位数
    dig[3] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[4] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}


/************************************************************************
// 函 数 名:      void LCD_Digital_U16_Asc16(u16 x, u16 y, u16 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  显示十进制5位数字, 16*16点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景  
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_U16_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[7];
    
    memset(dig,'\0',6);
    dig[0] = (char)(digital / 10000) + 0x30;           // 取出万位数
    dig[1] = (char)( (digital % 10000) / 1000) + 0x30; // 取出千位数
    dig[2] = (char)( (digital % 1000 ) / 100 ) + 0x30; // 取出百位数
    dig[3] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[4] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}


/************************************************************************
// 函 数 名:      LCD_Digital_U8_Asc24(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  显示十进制3位数字, 24*24点阵
// 参数描述:      x,y 坐标; u8 digital:0-255; forcolor:前景; bkcolor:背景  
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_U8_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[5];
    
    memset(dig,'\0',4);
    dig[0] = (char)( digital / 100)       + 0x30; // 取出百位数
    dig[1] = (char)((digital % 100) / 10) + 0x30; // 取出十位数
    dig[2] = (char)( digital % 10 )       + 0x30; // 取出个位数
    
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      LCD_Digital_U8_Asc16(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  显示十进制3位数字, 16*16点阵
// 参数描述:      x,y 坐标; u8 digital:0-255; forcolor:前景; bkcolor:背景  
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_U8_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[5];
    
    memset(dig,'\0',4);
    dig[0] = (char)( digital / 100)       + 0x30; // 取出百位数
    dig[1] = (char)((digital % 100) / 10) + 0x30; // 取出十位数
    dig[2] = (char)( digital % 10 )       + 0x30; // 取出个位数
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      char  Get_HextoASC_Disp(char hexdig)
// 函数功能描述:  将1个十六进制数转换为按十六进制的方式显示出来
// 参数描述:      char hexdig:十六进制数据   
// 返 回 值:      char:       
// 返回值描述:    十六进制文字
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
char  Get_HextoASC_Disp(char hexdig)
{
    char   tmp;
    
    tmp  = hexdig;
    tmp &= 0x0f;    
    if(tmp < 0x0a)       {  tmp += 0x30; } 
    else if(tmp == 0x0a) {  tmp  = 'a';  }
    else if(tmp == 0x0b) {  tmp  = 'b';  }
    else if(tmp == 0x0c) {  tmp  = 'c';  }
    else if(tmp == 0x0d) {  tmp  = 'd';  }
    else if(tmp == 0x0e) {  tmp  = 'e';  }
    else                 {  tmp  = 'f';  }
    
    return  tmp;
}

/************************************************************************
// 函 数 名:      void LCD_DigHex_U8_Asc24(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将1个字节的十六进制数按十六进制的方式显示出来 , 24*24点阵
// 参数描述:      x,y 坐标; u8 digital:0-ff; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_DigHex_U8_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[4];
    uint8_t    tmp;
    
    memset(dig,'\0',3);
    tmp = digital;
    tmp >>= 4; 
    dig[0] = Get_HextoASC_Disp(tmp);  // 取出高四位数, 转换为显示ASCII
    
    tmp = digital;
    tmp  &= 0x0f; 
    dig[1] = Get_HextoASC_Disp(tmp);  // 取出高四位数, 转换为显示ASCII 

    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_DigHex_U8_Asc16(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将1个字节的十六进制数按十六进制的方式显示出来 , 16*16点阵
// 参数描述:      x,y 坐标; u8 digital:0-ff; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_DigHex_U8_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[4];
    uint8_t    tmp;
    
    memset(dig,'\0',3);
    tmp = digital;
    tmp >>= 4; 
    dig[0] = Get_HextoASC_Disp(tmp);  // 取出高四位数, 转换为显示ASCII
    
    tmp = digital;
    tmp  &= 0x0f; 
    dig[1] = Get_HextoASC_Disp(tmp);  // 取出高四位数, 转换为显示ASCII 

    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_DigHex_U16_Asc24(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十六进制的方式显示出来 , 24*24点阵
// 参数描述:      x,y 坐标; u16 digital:0-ffff; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_DigHex_U16_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t     dig[6];
    uint16_t    tmp;
    uint8_t     tmp8;
    
    memset(dig,'\0',6);
    tmp = digital;
    tmp8 = (char)(tmp >>= 12); 
    dig[0] = Get_HextoASC_Disp(tmp8);  // 取出b15,b14,b13,b12位数, 转换为显示ASCII

    tmp = digital;
    tmp8 = (char)( (tmp >>= 8) & 0x000f);   
    dig[1] = Get_HextoASC_Disp(tmp8);  // 取出b11,b10,b9,b8位数, 转换为显示ASCII
    
    tmp = digital;
    tmp8 = (char)( (tmp >>= 4) & 0x000f);   
    dig[2] = Get_HextoASC_Disp(tmp8);  // 取出b7,b6,b5,b4 位数, 转换为显示ASCII

    tmp8 = (char)( digital  & 0x000f);  
    dig[3] = Get_HextoASC_Disp(tmp8);  // 取出b3,b2,b1,b0 位数, 转换为显示ASCII
    
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_DigHex_U16_Asc16(u16 x, u16 y, u8 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十六进制的方式显示出来 , 16*16点阵
// 参数描述:      x,y 坐标; u16 digital:0-ffff; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_DigHex_U16_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t     dig[6];
    uint16_t    tmp;
    uint8_t     tmp8;
    
    memset(dig,'\0',6);
    tmp = digital;
    tmp8 = (char)(tmp >>= 12); 
    dig[0] = Get_HextoASC_Disp(tmp8);  // 取出b15,b14,b13,b12位数, 转换为显示ASCII

    tmp = digital;
    tmp8 = (char)( (tmp >>= 8) & 0x000f);   
    dig[1] = Get_HextoASC_Disp(tmp8);  // 取出b11,b10,b9,b8位数, 转换为显示ASCII
    
    tmp = digital;
    tmp8 = (char)( (tmp >>= 4) & 0x000f);   
    dig[2] = Get_HextoASC_Disp(tmp8);  // 取出b7,b6,b5,b4 位数, 转换为显示ASCII

    tmp8 = (char)( digital  & 0x000f);  
    dig[3] = Get_HextoASC_Disp(tmp8);  // 取出b3,b2,b1,b0 位数, 转换为显示ASCII
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_Digital_4_Asc24(u16 x, u16 y, u16 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十进制的方式显示出来低四位 , 24*24点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_4_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[6];
    
    memset(dig,'\0',5);
    dig[0] = (char)( (digital % 10000) / 1000) + 0x30; // 取出千位数
    dig[1] = (char)( (digital % 1000 ) / 100 ) + 0x30; // 取出百位数
    dig[2] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[3] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_Digital_4_Asc16(u16 x, u16 y, u16 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十进制的方式显示出来低四位 , 16*16点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_4_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[6];
    
    memset(dig,'\0',5);
    dig[0] = (char)( (digital % 10000) / 1000) + 0x30; // 取出千位数
    dig[1] = (char)( (digital % 1000 ) / 100 ) + 0x30; // 取出百位数
    dig[2] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[3] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_Digital_2_Asc16(u16 x, u16 y, u16 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十进制的方式显示出来低2位 , 24*24点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_2_Asc24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[4];
    
    memset(dig,'\0',3);
    dig[0] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[1] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      void LCD_Digital_2_Asc16(u16 x, u16 y, u16 digital, u16 forcolor, u16 bkcolor)
// 函数功能描述:  将2个字节的十六进制数按十进制的方式显示出来低2位 , 16*16点阵
// 参数描述:      x,y 坐标; u16 digital:0-65535; forcolor:前景; bkcolor:背景    
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void LCD_Digital_2_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[4];
    
    memset(dig,'\0',3);
    dig[0] = (char)( (digital % 100  ) / 10  ) + 0x30; // 取出十位数
    dig[1] = (char)(  digital % 10   )         + 0x30; // 取出个位数
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

/************************************************************************
// 函 数 名:      tftDisp_Touch_XY(struCTPxy *cptxy, struCTPxy *lastxy)
// 函数功能描述:  显示XY的坐标值
// 参数描述:      x,y 坐标;  forcolor:前景; bkcolor:背景; char *string:显示的字符串   
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
static  struTouch  cptxylast={0,0,NO_TOUCH,X_NO_MOVING,Y_NO_MOVING,};
void  tftDisp_Touch_XY(struTouch *cptxynow)
{
    if(cptxynow->ctpxy.ctp_x != cptxylast.ctpxy.ctp_x) // 当数值变化后, 显示, 不变则不显示维持原状态
    {
        if(cptxynow->ctpxy.ctp_x == 0x0fff)   // 没有触摸到
        {
            Gui_Draw_Asc24_Hzk24(X_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, (uint8_t*)"-----");
        }
        else
        {
            LCD_Digital_U16_Asc24(X_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, cptxynow->ctpxy.ctp_x);
        }
    }
    
    if(cptxynow->ctpxy.ctp_y != cptxylast.ctpxy.ctp_y)  // 当数值变化后, 显示, 不变则不显示维持原状态
    {
        if(cptxynow->ctpxy.ctp_y == 0x0fff)   // 没有触摸到
        {
            Gui_Draw_Asc24_Hzk24(Y_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, (uint8_t*)"-----");
        }
        else
        {
            LCD_Digital_U16_Asc24(Y_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, cptxynow->ctpxy.ctp_y);
        }
    }
    
    cptxylast.ctpxy.ctp_x = cptxynow->ctpxy.ctp_x;
    cptxylast.ctpxy.ctp_y = cptxynow->ctpxy.ctp_y;
}



/************************************************************************
// 函 数 名:      tftDisp_Test_Val(uint16_t val_x, uint16_t val_y)
// 函数功能描述:  显示 valueX valueY 的值
// 参数描述:      x,y 坐标;  forcolor:前景; bkcolor:背景; char *string:显示的字符串   
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
static  uint8_t x_last=0,y_last=0;
void  tftDisp_Test_Val(uint16_t val_x, uint16_t val_y)
{
    if(val_x != x_last) // 当数值变化后, 显示, 不变则不显示维持原状态
    { 
        LCD_Digital_U16_Asc24(VALUE_X_X1, VALUE_X_Y0, VAL_X_FORCOLOR, VAL_X_BKCOLOR, val_x); 
        x_last = val_x;
    }
    
    if(val_y != y_last) // 当数值变化后, 显示, 不变则不显示维持原状态
    { 
        LCD_Digital_U16_Asc24(VALUE_Y_X1, VALUE_X_Y0, VAL_X_FORCOLOR, VAL_X_BKCOLOR, val_y); 
        y_last = val_y;
    }
}    



void  tftDisp_AllDataTime(struRTC  nowrtc)
{
    LCD_DigHex_U8_Asc24(YEAR_X0, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.yearH);
    LCD_DigHex_U8_Asc24(YEAR_X1, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.yearL);
    Gui_Draw_Asc24_Hzk24((YEAR_X1+FONT_CLR*2+4), DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, (uint8_t*)"/");
    
    LCD_DigHex_U8_Asc24(MONTH_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.month);
    Gui_Draw_Asc24_Hzk24((MONTH_X+FONT_CLR*2+4), DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, (uint8_t*)"/");
    
    LCD_DigHex_U8_Asc24(DATA_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.data);
    Gui_Draw_Asc24_Hzk24((DATA_X+FONT_CLR*2+4), DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, (uint8_t*)" ");
    
    LCD_DigHex_U8_Asc24(HOUR_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.hour);
    Gui_Draw_Asc24_Hzk24((HOUR_X+FONT_CLR*2+4), DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, (uint8_t*)":");
    
    LCD_DigHex_U8_Asc24(MINUTE_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.minute);
    Gui_Draw_Asc24_Hzk24((MINUTE_X+FONT_CLR*2+4), DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, (uint8_t*)":"); 

    LCD_DigHex_U8_Asc24(SECOND_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.second);
}
/************************************************************************
// 函 数 名:      tftDisp_DataTime(struRTC  nowrtc)
// 函数功能描述:  显示 现在的日期和时间 
// 参数描述:      struRTC  nowrtc: 日期和时间 
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void  tftDisp_DataTime(struRTC  nowrtc)
{
    if(nowrtc.second == 0x00)
    {
        tftDisp_AllDataTime(nowrtc);   // 仅显示秒
    }
    else
    {
        LCD_DigHex_U8_Asc24(SECOND_X, DATA_TIME_Y, DATA_TIME_FORCOLOR, DATA_TIME__BKCOLOR, nowrtc.second);
    }
}


/************************************************************************
// 函 数 名:      tftDisp_Main(struWin * win_now)
// 函数功能描述:  显示固定的主界面
// 参数描述:      
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     未完工
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     lf
// 日期：         2018-1-29
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void tftDisp_Main(struWin * win_now)
{
		
	//tftDisp_debug();	
	uint16_t metro_bk_clr;
	
	metro_bk_clr=win_now->show_subdev_data?METRO_4_BK_COL:METRO_1_BK_COL;
	
		
	Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X,METRO_BL_L_1_Y,METRO_LEGHTH,METRO_WIDTH,metro_bk_clr);//微软蓝
	Lcd_Clear_Some_Area_sim(METRO_BL_H_2_X,METRO_BL_L_1_Y,METRO_LEGHTH,METRO_WIDTH,metro_bk_clr);
	Lcd_Clear_Some_Area_sim(METRO_BL_H_3_X,METRO_BL_L_1_Y,METRO_LEGHTH,METRO_WIDTH,metro_bk_clr);
	Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X,METRO_BL_L_2_Y,METRO_LEGHTH_L,METRO_WIDTH,metro_bk_clr);
	
	Gui_Draw_A_Icon(METRO_BL_H_1_X,METRO_BL_L_1_Y,metro_bk_clr,0xFFFF,&icon_pic,2);
	Gui_Draw_A_Icon(METRO_BL_H_2_X,METRO_BL_L_1_Y,metro_bk_clr,0xFFFF,&icon_pic,0);
	Gui_Draw_A_Icon(METRO_BL_H_3_X,METRO_BL_L_1_Y,metro_bk_clr,0xFFFF,&icon_pic,1);
	Gui_Draw_A_Icon(METRO_BL_H_1_X,METRO_BL_L_2_Y,metro_bk_clr,0xFFFF,&icon_pic,3);
	
	//title
	gui_draw_a_title_str(METRO_BL_H_1_X + METRO_X_WORD,METRO_BL_L_1_Y + METRO_y_WORD,0xFFFF,metro_bk_clr,0,2);
	gui_draw_a_title_str(METRO_BL_H_2_X + METRO_X_WORD,METRO_BL_L_1_Y + METRO_y_WORD,0xFFFF,metro_bk_clr,2,2);
	gui_draw_a_title_str(METRO_BL_H_3_X + METRO_X_WORD,METRO_BL_L_1_Y + METRO_y_WORD,0xFFFF,metro_bk_clr,4,2);
	gui_draw_a_str(METRO_BL_H_1_X + METRO_X_WORD,METRO_BL_L_2_Y + METRO_y_WORD,0xFFFF,metro_bk_clr,"PM2.5");
	gui_draw_a_str(METRO_BL_H_1_X + METRO_X_WORD * 3 - 30 ,METRO_BL_L_2_Y + METRO_y_WORD,0xFFFF,metro_bk_clr,"PM10");
	
	//scale
	gui_draw_a_title_str(METRO_BL_H_1_X + METRO_X_SCA,METRO_BL_L_1_Y + METRO_y_SCA,0xFFFF,metro_bk_clr,36,1);
	gui_draw_a_str(METRO_BL_H_2_X + METRO_X_SCA,METRO_BL_L_1_Y + METRO_y_SCA,0xFFFF,metro_bk_clr,"%");
	gui_draw_a_16_str(METRO_BL_H_3_X + METRO_X_SCA,METRO_BL_L_1_Y + METRO_y_SCA,0xFFFF,metro_bk_clr,"ppb");
	gui_draw_a_16_str(METRO_BL_H_2_X + METRO_X_SCA - 100,METRO_BL_L_2_Y + METRO_y_SCA + 30,0xFFFF,metro_bk_clr,"ug/m3");
	
	
	gui_draw_a_str(550,270,YELLOW_3_4,BK_COL,(uint8_t *)"KeepHome");
	gui_draw_a_16_str(580,310,YELLOW_3_4,BK_COL,(uint8_t *)"For Safe & Clear !");
	Gui_Draw_Line(0,  LINE_Y0,    X_MAX_PIXEL-1,  LINE_Y0,    WHITE_4_4); // 显示2条分割白线
    Gui_Draw_Line(0, (LINE_Y0+1), X_MAX_PIXEL-1, (LINE_Y0+1), WHITE_4_4); //
   
	
	//Bottom Button=================================
	Gui_Draw_Rect(BTM_BUTTON_1_X-10,BTM_BUTTON_1_y-10,BTM_BUTTON_1_X+BTM_BUTTON_WEIGHT+20,BTM_BUTTON_1_y+BTM_BUTTON_HEIGHT+10,BTM_BUTTON_REC_COL);
	Gui_Draw_Rect(BTM_BUTTON_2_X-10,BTM_BUTTON_1_y-10,BTM_BUTTON_2_X+BTM_BUTTON_WEIGHT+20,BTM_BUTTON_1_y+BTM_BUTTON_HEIGHT+10,BTM_BUTTON_REC_COL);
	Gui_Draw_Rect(BTM_BUTTON_3_X-10,BTM_BUTTON_1_y-10,BTM_BUTTON_3_X+BTM_BUTTON_WEIGHT+20,BTM_BUTTON_1_y+BTM_BUTTON_HEIGHT+10,BTM_BUTTON_REC_COL);
	gui_draw_a_str(BTM_BUTTON_1_X,BTM_BUTTON_1_y,WHITE_4_4,BK_COL,(uint8_t*)"ABOUT");
	gui_draw_a_str(BTM_BUTTON_2_X,BTM_BUTTON_1_y,WHITE_4_4,BK_COL,(uint8_t*)"LIGHT");
	gui_draw_a_str(BTM_BUTTON_3_X,BTM_BUTTON_1_y,WHITE_4_4,BK_COL,(uint8_t*)"DCONN");


	tftDisp_SensorData(win_now);//display sensors data
	
}


/************************************************************************
// 函 数 名:      tftDisp_SensorData()
// 函数功能描述:  显示传感器数据 数据来自全局变量
// 参数描述:      无
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     未完工
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     lf
// 日期：         2018-1-29
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void  tftDisp_SensorData(struWin * win_now)
{
	if(win_now->mode == WIN_MAIN)
	{
		uint16_t metro_bk_clr;
		metro_bk_clr=win_now->show_subdev_data?METRO_4_BK_COL:METRO_1_BK_COL;
		
		//----------------------------------------------
		//sensor_data_now.data_temp = 123;
		//temp in block 1
		//Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,metro_bk_clr);
		if(!win_now->show_subdev_data)
		{
			Gui_Draw_My_Num(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_temp,TRUE); 
		}
		else//show subdev_id
		{
			Gui_Draw_My_Num(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_sp1_temp,TRUE); 
		}
		//----------------------------------------------
		//humi in block 2
		if(!win_now->show_subdev_data)
		{
			Gui_Draw_My_Num(METRO_BL_H_2_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_humi,TRUE);
		}
		else
		{
			Gui_Draw_My_Num(METRO_BL_H_2_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_sp1_humi,TRUE);
		}
		//----------------------------------------------
		//cho in block 3
		if(sensor_data_now.data_cho >= 999)//can't show num more than 999 show --- if it above 999
		{
			Lcd_Clear_Some_Area_sim(METRO_BL_H_3_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		16*5,48,metro_bk_clr);
			gui_draw_a_str(METRO_BL_H_3_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,"---");// 
		}
		else
		{
			Gui_Draw_My_Num(METRO_BL_H_3_X + METRO_X_DATA,METRO_BL_L_1_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_cho,FALSE);// 
		}
		//----------------------------------------------
		//pm25 in block 4
		if(sensor_data_now.data_pm25>=999)
		{
			Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_2_Y + METRO_Y_DATA,
		16*5,48,metro_bk_clr);
			gui_draw_a_str(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_2_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,"---");
		}
		else
		{
			Gui_Draw_My_Num(METRO_BL_H_1_X + METRO_X_DATA,METRO_BL_L_2_Y + METRO_Y_DATA,
			0xFFFF,metro_bk_clr,sensor_data_now.data_pm25,FALSE);
		}
		//----------------------------------------------
		//pm10 in block 4
		if(sensor_data_now.data_pm10>=999)
		{
			Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X + METRO_X_DATA*3 - 30,METRO_BL_L_2_Y + METRO_Y_DATA,
		16*5,48,metro_bk_clr);
			gui_draw_a_str(METRO_BL_H_1_X + METRO_X_DATA*3 - 30,METRO_BL_L_2_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,"---");
		}
		else
		{
			Gui_Draw_My_Num(METRO_BL_H_1_X + METRO_X_DATA*3 - 30,METRO_BL_L_2_Y + METRO_Y_DATA,
		0xFFFF,metro_bk_clr,sensor_data_now.data_pm10,FALSE);
		}
		//----------------------------------------------
		uint16_t aqi;
		(sensor_data_now.data_pm25 > sensor_data_now.data_pm10)?(aqi=sensor_data_now.data_pm25):\
		(aqi=sensor_data_now.data_pm10);
		
		if(aqi <= AQI_1)
		{
			Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,icon_title.x*4,icon_title.y,metro_bk_clr);
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,10,1);//优
		}
		else if(aqi >= AQI_1 && aqi <= AQI_2)
		{
			Lcd_Clear_Some_Area_sim(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,icon_title.x*4,icon_title.y,metro_bk_clr);
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,11,1);//良
		}
		else if(aqi >= AQI_2 && aqi <= AQI_3)
		{
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,12,1);//轻度污染
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X+32 ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,1,1);
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X+32*2 ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,16,2);
		}
		else if(aqi >= AQI_3 && aqi <= AQI_4)
		{
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,13,1);//重度污染
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X+32 ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,1,1);
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X+32*2 ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,16,2);

		}
		else 
		{
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,14,2);//严重污染
			
			gui_draw_a_title_str(METRO_BL_H_1_X + AQI_X+32*2 ,METRO_BL_L_2_Y + METRO_Y_DATA,0xFFFF,metro_bk_clr,16,2);

		}
	}
}
/************************************************************************
// 函 数 名:      tftDisp_menu_l()
// 函数功能描述:  显示右侧菜单 - 拟设计显示网络连接状况以及 not clear yet
// 参数描述:      无
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     未完工
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     lf
// 日期：         2018-1-29
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void tftDisp_menu_l()
{
	Lcd_Clear_Some_Area(X_MAX_PIXEL-(MENU_WEIGHT >> 1),0,X_MAX_PIXEL,Y_MAX_PIXEL,MENU_BK_COL);
	Delay_ms(1);
	Lcd_Clear_Some_Area(X_MAX_PIXEL-MENU_WEIGHT,0,X_MAX_PIXEL,Y_MAX_PIXEL,MENU_BK_COL);
	
	gui_draw_a_title_str(X_MAX_PIXEL - MENU_WEIGHT + MENU_START_X,MENU_START_Y,MENU_FONT_COL,MENU_BK_COL,18,2);
	struWifi		wifi_c;
	read_Wifi_Config(&wifi_c);
	if(wifi_c.is_NetConf)
	{
		gui_draw_a_16_str(X_MAX_PIXEL - MENU_WEIGHT + MENU_START_X+32,MENU_START_Y+64,WHITE_4_4,MENU_BK_COL,wifi_c.ssid);
	}
	else
	{
		gui_draw_a_16_str(X_MAX_PIXEL - MENU_WEIGHT + MENU_START_X+32,MENU_START_Y+64,WHITE_4_4,MENU_BK_COL,"No Conn!");
	}
}

/************************************************************************
// 函 数 名:      tftDisp_fresh(struWin * win_now)
// 函数功能描述:  刷新屏幕显示 struWin
// 参数描述:      窗体结构体
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     未完工
// 函数层次：     面向用户的--软件功能层

// 创 建 人：     lf
// 日期：         2018-1-29
// 修 改 人：                     
// 修改日期：     201x-xx-xx
************************************************************************/
void tftDisp_fresh(struWin * win_now)
{
	if(win_now->mode == WIN_WELCOME && win_now->old_mode != WIN_WELCOME)
	{
		tftDisp_welcome();//显示开机画面窗体
	}
	if(win_now->mode == WIN_MAIN)
	{
		//从不同类型的窗体切换为主窗体显示
		if(win_now->old_mode == WIN_MENU)
		{
			Lcd_Clear_Some_Area(X_MAX_PIXEL-200,0,X_MAX_PIXEL,Y_MAX_PIXEL,BK_COL);
			tftDisp_Main(win_now);
		}
		if(win_now->old_mode == WIN_ABOUT || win_now->old_mode == WIN_DEMO || win_now->old_mode == WIN_ALARM
			|| win_now->old_mode == WIN_MESS)
		{
			Lcd_Clear_Some_Area_sim(WIN_ABT_X,WIN_ABT_Y,WIN_ABT_W,WIN_ABT_H,BK_COL);
			Lcd_Clear_Some_Area_sim(WIN_DEMO_X,WIN_DEMO_Y,WIN_DEMO_W,WIN_DEMO_H,BK_COL);
			tftDisp_Main(win_now);
		}
		if(win_now->old_mode == WIN_WELCOME)
		{
			Lcd_Clear_Some_Area(0,0,X_MAX_PIXEL,Y_MAX_PIXEL,BK_COL);
		}
		if(win_now->old_mode != WIN_MAIN)
		{
			tftDisp_Main(win_now);
		}
	}
	else if(win_now->mode == WIN_MENU)
	{

		if(win_now->old_mode != WIN_MENU)
			tftDisp_menu_l();// draw fix win
	}
	else if(win_now->mode == WIN_ABOUT)
	{
		if(win_now->old_mode != WIN_ABOUT)
			tftDisp_about();
	}
	else if(win_now->mode == WIN_DEMO)
	{
		if(win_now->old_mode != WIN_DEMO)
			tftDisp_demo();
	}
	else if(win_now->mode == WIN_ALARM)
	{
		if(win_now->old_mode != WIN_ALARM)
			tftDisp_alarm(win_now->is_rev);
	}
	else if(win_now->mode == WIN_MESS)
	{
		if(win_now->old_mode != WIN_MESS)
		{
			tftDisp_mess("");
			win_now->mode = WIN_MESS;
		}
	}
	win_now->old_mode = win_now->mode;
}
/************************************************************************
//Func Name:	tftDisp_about()
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void tftDisp_about()
{
	tim_task.enable_win_count = ENABLE;
	tim_task.win_count = 3;
	Lcd_Clear_Some_Area_sim(WIN_ABT_X,WIN_ABT_Y,WIN_ABT_W,WIN_ABT_H,WIN_ABT_COL);
	//words
	//gui_draw_about(WIN_ABT_FONT_X, WIN_ABT_FONT_X, 0xFFFF, WIN_ABT_COL);
	Gui_Draw_A_Icon(WIN_ABT_X,WIN_ABT_Y,WIN_ABT_COL,WHITE_4_4,&icon_pic,6);//smeil
	Gui_Draw_A_Icon(METRO_BL_H_1_X+20,METRO_BL_L_2_Y+90,0x0,0xFFFF,&icon_pic,4);//home
	gui_draw_a_icon_str(WIN_ABT_FONT_X, WIN_ABT_FONT_Y, 0xFFFF, WIN_ABT_COL,&icon_about,0,7);
	gui_draw_a_icon_str(WIN_ABT_FONT_X, WIN_ABT_FONT_Y + 32, 0xFFFF, WIN_ABT_COL,&icon_about,8,17);
	gui_draw_a_icon_str(WIN_ABT_FONT_X, WIN_ABT_FONT_Y + 32*2, 0xFFFF, WIN_ABT_COL,&icon_about,18,25);
	gui_draw_a_icon_str(WIN_ABT_FONT_X, WIN_ABT_FONT_Y + 32*3, 0xFFFF, WIN_ABT_COL,&icon_about,26,30);
	gui_draw_a_icon_str(WIN_ABT_FONT_X, WIN_ABT_FONT_Y + 32*4, 0xFFFF, WIN_ABT_COL,&icon_about,31,37);
}
/************************************************************************
//Func Name:	tftDisp_demo()
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void tftDisp_demo()
{
	tim_task.enable_win_count = ENABLE;
	tim_task.win_count = 3;
	Gui_Draw_A_Icon(METRO_BL_H_1_X+20,METRO_BL_L_2_Y+90,0x0,0xFFFF,&icon_pic,4);//home
	Lcd_Clear_Some_Area_sim(WIN_DEMO_X,WIN_DEMO_Y,WIN_DEMO_W,WIN_DEMO_H,WIN_DEMO_COL);
}
/************************************************************************
//Func Name:	
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void tftDisp_alarm(BOOL is_rev)
{
	uint16_t bk_col,fg_col;
	tim_task.enable_win_count = ENABLE;
	tim_task.win_count = 10;
	if(is_rev){bk_col = WIN_ALM_COL;fg_col = WHITE_4_4;}
	else{bk_col = WHITE_4_4;fg_col = WIN_ALM_COL;}
	Lcd_Clear_Some_Area_sim(WIN_ALM_X,WIN_ALM_Y,WIN_ALM_W,WIN_ALM_H,bk_col);
	Gui_Draw_A_Icon(WIN_ALM_X,WIN_ALM_Y,bk_col,fg_col,&icon_pic,5);//ALM
	gui_draw_a_str(WIN_ALM_FONT_X,WIN_ALM_FONT_Y,fg_col,bk_col,(uint8_t*)"ALARM");
	gui_draw_a_icon_str(WIN_ALM_FONT_X+80,WIN_ALM_FONT_Y+60,fg_col,bk_col,&icon_title,30,35);
	
	Gui_Draw_A_Icon(METRO_BL_H_1_X+20,METRO_BL_L_2_Y+90,0x0,0xFFFF,&icon_pic,4);//home
	
}
/************************************************************************
//Func Name:	tftDisp_debug()
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void tftDisp_debug()
{
	uint16_t x,y;
	for(x = 0;x<=X_MAX_PIXEL;x+=10)
	{
		if(x % 100 == 0)
			Gui_Draw_Line(x,0,x,Y_MAX_PIXEL,RED_4_4);
		else
			Gui_Draw_Line(x,0,x,Y_MAX_PIXEL,BLACK);
	}
	for(y = 0;y<=Y_MAX_PIXEL;y+=10)
	{
		if(y % 100 == 0)
			Gui_Draw_Line(0,y,X_MAX_PIXEL,y,RED_4_4);
		else
			Gui_Draw_Line(0,y,X_MAX_PIXEL,y,BLACK);
	}
}
/************************************************************************
//Func Name:	tftDisp_welcome()
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void  tftDisp_welcome()
{
	//tftDisp_bar(800);
	Lcd_Clear_Some_Area(0,0,X_MAX_PIXEL,Y_MAX_PIXEL,WEL_BK_COL);
	Gui_Draw_A_Icon(300,100,RGB888TO565(0x204080),WEL_BK_COL,&icon_xm,0);
	Gui_Draw_A_Icon(30,30,RGB888TO565(0x204080),WEL_BK_COL,&icon_xh,0);
	gui_draw_a_icon_str(270, 300, RGB888TO565(0x204080), WEL_BK_COL,&icon_about,0,16);
	
	
}
/************************************************************************
//Func Name:	void  tftDisp_wifi_flag()
//Func Info:	show wifi flag
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void  tftDisp_wifi_flag(BOOL is_show,BOOL is_con)
{
	if(is_show)
	{
		if(is_con)
		{
			Gui_Draw_A_Icon(FLAG_WIFI_X,FLAG_WIFI_Y,BK_COL,FLAG_WIFI_FON_COL,&icon_pic,7);//wifi
		}
		else
		{
			Gui_Draw_A_Icon(FLAG_WIFI_X,FLAG_WIFI_Y,BK_COL,RED_4_4,&icon_pic,7);//red wifi
		}
	}
	else
	{
		Lcd_Clear_Some_Area(FLAG_WIFI_X,FLAG_WIFI_Y,FLAG_WIFI_X+64,FLAG_WIFI_Y+64,BK_COL);
	}
}
/************************************************************************
//Func Name:	void  tftDisp_btn_init(struButtom ** but_list)
//Func Info:	init the list of buttons
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void  tftDisp_btn_init(struButtom ** but_list)
{
	struButtom      * blist;
	blist = *but_list;
	//buttom 1
	blist->x = MENU_BUTTON_WEIGHT;
	blist->y = MENU_BUTTON_HEIGHT;				
	blist->w = MENU_BUTTON_1_X;					
	blist->h = MENU_BUTTON_1_y;	
	blist->name = MENU_BUTTON_1;
	//buttom 2
	blist++;
	blist->x = MENU_BUTTON_WEIGHT;
	blist->y = MENU_BUTTON_HEIGHT;				
	blist->w = MENU_BUTTON_1_X;					
	blist->h = MENU_BUTTON_2_y;	
	blist->name = MENU_BUTTON_2;
}
/************************************************************************
//Func Name:	void  tftDisp_draw_btn(struButtom ** but_list);
//Func Info:	draw buttons
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void  tftDisp_draw_btn(struButtom ** but_list)
{
	struButtom      * blist;
	blist = *but_list;
	//buttom 1
	Gui_Draw_Rect(blist->x-10,blist->y-10,blist->x+blist->w+20,blist->y+blist->h+10,BTM_BUTTON_REC_COL);
	//buttom 2
	blist++;
	Gui_Draw_Rect(blist->x-10,blist->y-10,blist->x+blist->w+20,blist->y+blist->h+10,BTM_BUTTON_REC_COL);
	
}

/************************************************************************
//Func Name:	
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void tftDisp_mess(const char * mess)
{
	
	Lcd_Clear_Some_Area_sim(WIN_MESS_X,WIN_MESS_Y,WIN_MESS_W,WIN_MESS_H,WIN_MESS_COL);
	
	gui_draw_a_16_str(WIN_MESS_FONT_X,WIN_MESS_FONT_Y,0xFFFF,WIN_MESS_COL,(uint8_t * )"MESSAGE:");
	gui_draw_a_16_str(WIN_MESS_FONT_X+10,WIN_MESS_FONT_Y+80,0xFFFF,WIN_MESS_COL,(uint8_t * )mess);
	Gui_Draw_A_Icon(METRO_BL_H_1_X+20,METRO_BL_L_2_Y+90,0x0,0xFFFF,&icon_pic,4);//home
	
}

void tftDisp_bar(uint16_t leng)
{
	Lcd_Clear_Some_Area_sim(100,400,leng+20,40,RGB888TO565(0x204080));
	if(leng >= 250){gui_draw_a_str(350,405,WEL_BK_COL,RGB888TO565(0x204080),"Loading...");}
}