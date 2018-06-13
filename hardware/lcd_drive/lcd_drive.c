/*************************************************
// 文件说明:      此文件为底层硬件接口及相应软件的初始化
//                一般电路图和显示屏选定后，这里面的内容就定了，不需要修改
// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/

#include  "lcd_drive.h"

/**********************************************
Lcd控制引脚初始化
***********************************************/
void  LCD_CTRL_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    // LCD的复位引脚初始化
    LCD_RST_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin  = LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LCD_RST_GPIOx, &GPIO_InitStruct);
    LCD_RST_OFF();
    
    // LCD的背光引脚初始化
    LCD_BKLED_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin  = LCD_BKLED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LCD_BKLED_GPIOx, &GPIO_InitStruct);
    LCD_BKLED_OFF();
}


void LCD_delay(uint8_t j)
{
    __IO  uint16_t i;    
    while(j--)
    {
        for(i=7200;i>0;i--);
    }
}

/**********************************************
Lcd引脚复位
***********************************************/
static void LCD_Rst(void)
{   
    LCD_RST_ON();  
    LCD_delay(10); 
    LCD_RST_OFF(); 
    LCD_delay(2);  
}

/**********************************************
Lcd写命令
***********************************************/
 void WriteComm(uint16_t lcd_cmd)
{   
    *(__IO uint16_t *) (Bank1_LCD_C) = lcd_cmd;
}
/**********************************************
Lcd写数据
***********************************************/
 void WriteData(uint16_t lcd_data)
{   
    *(__IO uint16_t *) (Bank1_LCD_D) = lcd_data;
}


/**********************************************
Lcd初始化函数，包括引脚初始化, 硬件复位, 软件初始化及设置
***********************************************/
void LCD_init(void)
{   
    LCD_CTRL_GPIO_Init();     // 复位引脚和背光引脚的初始化
    LCD_Rst();                // 复位引脚产生复位信号
    
    //************* Start Initial Sequence **********//
    WriteComm(0xFF); // EXTC Command Set enable register 扩展命令使能
    WriteData(0xFF); 
    WriteData(0x98); 
    WriteData(0x06); // 使能EXTC Command; !=06时 关闭 "EXTC Command" 

    WriteComm(0xBC); // GIP 1: 手册上没有显示什么功能，但是一定要, 不能缺失该指令
    WriteData(0x03); 
    WriteData(0x0F); 
    WriteData(0x63); 
    WriteData(0x69); 
    WriteData(0x01); 
    WriteData(0x01); 
    WriteData(0x1B); 
    WriteData(0x11); 
    WriteData(0x70); 
    WriteData(0x73); 
    WriteData(0xFF); 
    WriteData(0xFF); 
    WriteData(0x08); 
    WriteData(0x09); 
    WriteData(0x05); 
    WriteData(0x00);
    WriteData(0xEE); 
    WriteData(0xE2); 
    WriteData(0x01); 
    WriteData(0x00);
    WriteData(0xC1); 

    WriteComm(0xBD); // GIP 2: 手册上没有显示什么功能，但是一定要, 不能缺失该指令 
    WriteData(0x01); 
    WriteData(0x23); 
    WriteData(0x45); 
    WriteData(0x67); 
    WriteData(0x01); 
    WriteData(0x23); 
    WriteData(0x45); 
    WriteData(0x67); 

    WriteComm(0xBE); // GIP 3: 手册上没有显示什么功能，但是一定要, 不能缺失该指令 
    WriteData(0x00); 
    WriteData(0x22); 
    WriteData(0x27); 
    WriteData(0x6A); 
    WriteData(0xBC); 
    WriteData(0xD8); 
    WriteData(0x92); 
    WriteData(0x22); 
    WriteData(0x22); 

///////////////////
    WriteComm(0xC7); // Vcom    WriteData(0x1E);
    WriteData(0x8F);
    WriteData(0x80);
// 
    WriteComm(0xED);  // EN_volt_reg 
    WriteData(0x7F); 
    WriteData(0x0F);  // 使能 VGMP/VGMN/VGSP/VGSN

    WriteComm(0xC0); // Power Control 1
    WriteData(0xC7); // C:AVDD=+5V  7:AVEE=-5V    //WriteData(0xE3);
    WriteData(0x0B); // 固定
    WriteData(0x02); // 
    WriteData(0x00); // 
    WriteData(0x00); // 
    WriteData(0x88); // 
    WriteData(0x2c); // 
    WriteData(0x50); // 
    WriteData(0x00); // 
    WriteData(0x00); //
    WriteData(0x00); // 
    WriteData(0x00); //
    WriteData(0xff); // 
 
    WriteComm(0xFC);
    WriteData(0x04); // VGL=-6V            // WriteData(0x08); VGL=-10V

    WriteComm(0xDF); // Engineering Setting 
    WriteData(0x00); 
    WriteData(0x00); 
    WriteData(0x00); 
    WriteData(0x00); 
    WriteData(0x00); 
    WriteData(0x20); // FREQ=MIPI PCLK            WriteData(0x02);

    WriteComm(0xF3); // DVDD Voltage Setting 
    WriteData(0x74); // DVDD=1.6V

    WriteComm(0xB4); // Display Inversion Control 
    WriteData(0x00); 
    WriteData(0x00); 
    WriteData(0x00); 
	
	
     
	
    WriteComm(0xF7); // 分辨率
    WriteData(0x81); // 480x854

    WriteComm(0xB1); // Frame Rate 
    WriteData(0x00); // Fosc
    WriteData(0x10); // 15 clocks/line
    WriteData(0x14); // frame 68.03hz

    WriteComm(0xF1); // Panel Timing Control 
    WriteData(0x29); 
    WriteData(0x8A); // 1 line chopper
    WriteData(0x07); 

    WriteComm(0xF2); // Panel Timing Control 
    WriteData(0x40); 
    WriteData(0xD2); 
    WriteData(0x50); 
    WriteData(0x28); 

    WriteComm(0xC1); // Power Control 2 
    WriteData(0x17);
    WriteData(0X85); 
    WriteData(0x85); 
    WriteData(0x20); 

    WriteComm(0xE0); // gamma+
    WriteData(0x00); //P1 
    WriteData(0x0C); //P2 
    WriteData(0x15); //P3 
    WriteData(0x0D); //P4 
    WriteData(0x0F); //P5 
    WriteData(0x0C); //P6 
    WriteData(0x07); //P7 
    WriteData(0x05); //P8 
    WriteData(0x07); //P9 
    WriteData(0x0B); //P10 
    WriteData(0x10); //P11 
    WriteData(0x10); //P12 
    WriteData(0x0D); //P13 
    WriteData(0x17); //P14 
    WriteData(0x0F); //P15 
    WriteData(0x00); //P16 

    WriteComm(0xE1); // gamma-
    WriteData(0x00); //P1 
    WriteData(0x0D); //P2 
    WriteData(0x15); //P3 
    WriteData(0x0E); //P4 
    WriteData(0x10); //P5 
    WriteData(0x0D); //P6 
    WriteData(0x08); //P7 
    WriteData(0x06); //P8 
    WriteData(0x07); //P9 
    WriteData(0x0C); //P10 
    WriteData(0x11); //P11 
    WriteData(0x11); //P12 
    WriteData(0x0E); //P13 
    WriteData(0x17); //P14 
    WriteData(0x0F); //P15 
    WriteData(0x00); //P16

    WriteComm(0x35); //Tearing Effect ON 
    WriteData(0x00); 

    WriteComm(0x36); // 显存接口控制，控制横屏 或则 竖屏
    #ifdef USE_HORIZONTAL//如果定义了横屏 
        WriteData(0xA0); // 横屏
    #else
        WriteData(0x00); // 竖屏
    #endif
    
    WriteComm(0x3A); // 
    WriteData(0x55); // RGB接口格式16bit/pixel  MCU接口格式16bit/pixel
	
	//WriteComm(0xB9); // horizontal flip 
    //WriteData(0x00); 
    //WriteData(0x02); 
	
    WriteComm(0x11); // Exit Sleep 
    LCD_delay(120); 
    WriteComm(0x29); // Display On 
    LCD_delay(10);
    LCD_BKLED_ON();  // 背光灯开

    Lcd_Clear_All(BK_COLOR);
	//BLUE_2_4
}
/******************************************
函数名：Lcd写命令函数
功能：向Lcd指定位置写入应有命令或数据
入口参数：Index 要寻址的寄存器地址
          ConfigTemp 写入的数据或命令值
******************************************/
//void LCD_WR_REG(uint16_t Index,uint16_t CongfigTemp)
//{
//    *(__IO uint16_t *) (Bank1_LCD_C) = Index;   
//    *(__IO uint16_t *) (Bank1_LCD_D) = CongfigTemp;
//}

//void BlockWrite(uint16_t Xstart,uint16_t Xend,uint16_t Ystart,uint16_t Yend) 
//{
//    WriteComm(0x2a);   
//    WriteData(Xstart>>8);
//    WriteData(Xstart&0xff);
//    WriteData(Xend>>8);
//    WriteData(Xend&0xff);

//    WriteComm(0x2b);   
//    WriteData(Ystart>>8);
//    WriteData(Ystart&0xff);
//    WriteData(Yend>>8);
//    WriteData(Yend&0xff);
//    
//    WriteComm(0x2c);
//}
/*************************************************
// 函 数 名:      GetPoint( uint16_t x, uint16_t y)
// 函数功能描述:  读取X,Y点的像素颜色值
// 参数描述:      uint16_t x, uint16_t y: 坐标 
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件功能层

// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/
 uint16_t GetPoint( uint16_t x, uint16_t y)
{
    WriteComm(0x2a);   
    WriteData(x>>8);
    WriteData(x);
    WriteData(x>>8);
    WriteData(x);

    WriteComm(0x2b);   
    WriteData(y>>8);
    WriteData(y);
    WriteData(y>>8);
    WriteData(y);

    WriteComm(0x2e);
    
    x = *(__IO uint16_t *) (Bank1_LCD_D);
//    x=1;
//    while(--x);
    x = *(__IO uint16_t *) (Bank1_LCD_D);
    y = *(__IO uint16_t *) (Bank1_LCD_D);

    return (x&0xf800)|((x&0x00fc)<<3)|(y>>11);
}
/**********************************************
函数名：Lcd块选函数
功能：选定Lcd上指定的矩形区域

注意：xStart和 yStart随着屏幕的旋转而改变，位置是矩形框的四个角

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong  要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
返回值：无
***********************************************/
//void Lcd_ColorBox(uint16_t xStart, uint16_t yStart, uint16_t xLong, uint16_t yLong, uint16_t color)
//{
//    uint32_t temp;

//    BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
//    for (temp=0; temp<xLong*yLong; temp++)
//    {
//        *(__IO uint16_t *) (Bank1_LCD_D) = color;
//    }
//}

/******************************************
函数名：Lcd图像填充100*100
功能：向Lcd指定位置填充图像
入口参数：Index 要寻址的寄存器地址
          ConfigTemp 写入的数据或命令值
******************************************/
//void LCD_Fill_Pic(uint16_t x, uint16_t y, uint16_t pic_H, uint16_t pic_V, const unsigned char* pic)
//{
//    uint32_t  i;
//    uint16_t  j;

////  WriteComm(0x3600);  //Set_address_mode
////  WriteData(0x00);    //横屏，从左下角开始，从左到右，从下到上
//    BlockWrite(x, x+pic_H-1, y, y+pic_V-1);
//    for (i = 0; i < pic_H*pic_V*2; i+=2)
//    {
//        j=pic[i];
//        j=j<<8;
//        j=j+pic[i+1];
//        *(__IO uint16_t *) (Bank1_LCD_D) = j;
//    }
//}

//在指定座标上打一个点
//void DrawPixel(uint16_t x, uint16_t y, uint16_t Color)
//{
//    BlockWrite(x, x, y, y);
//    *(__IO uint16_t *) (Bank1_LCD_D) = Color;
//}


/*************************************************
// 函 数 名:      Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
// 函数功能描述:  设置lcd显示起始点
// 参数描述:      u16 Xpos, u16 Ypos: 坐标 
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件功能层

// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/
void Lcd_Set_XY(uint16_t Xpos, uint16_t Ypos)
{   
    WriteComm(0x2a);   
    WriteData(Xpos>>8);
    WriteData(Xpos&0xff);

    WriteComm(0x2b);   
    WriteData(Ypos>>8);
    WriteData(Ypos&0xff);
    
    WriteComm(0x2c);  
} 

/*************************************************
// 函 数 名:      Lcd_SetRegion(uint16_t xStart, uint16_t yStart,uint16_t xEnd,uint16_t yEnd)
// 函数功能描述:  设置lcd显示区域，在此区域写点数据自动换行
// 参数描述:      u16 xStar, u16 yStar,u16 xEnd,u16 yEnd: 起点终点坐标 
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件功能层

// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/
void Lcd_Set_Region(uint16_t xStart, uint16_t yStart,uint16_t xEnd,uint16_t yEnd)
{
    uint16_t  xstart, xend, ystart, yend;
    
    
    if(xStart <= xEnd) { xstart = xStart;  xend = xEnd;    }
    else               { xstart = xEnd;    xend = xStart;  }

    if(yStart <= yEnd) { ystart = yStart;  yend = yEnd;    }
    else               { ystart = yEnd;    yend = yStart;  }
    
    WriteComm(0x2a);   
    WriteData(xstart>>8);
    WriteData(xstart&0xff);
    WriteData(xend>>8);
    WriteData(xend&0xff);

    WriteComm(0x2b);   
    WriteData(ystart>>8);
    WriteData(ystart&0xff);
    WriteData(yend>>8);
    WriteData(yend&0xff);
    
    WriteComm(0x2c);
}
    
/*************************************************
// 函 数 名:      Lcd_Clear(u16 color)
// 函数功能描述:  全屏清屏函数
// 参数描述:      u16 color: 填充颜色
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/
void Lcd_Clear_All(uint16_t color)               
{   
    uint16_t  i,m;
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
    for(i=0;i<X_MAX_PIXEL;i++)
    {
        for(m=0;m<Y_MAX_PIXEL;m++)
        {   
            *(__IO uint16_t *) (Bank1_LCD_D) = color;
        }  
    }   
}

/*************************************************
// 函 数 名:      Lcd_Clear_Some_Area(uint16_t stx,uint16_t sty,uint16_t endx,uint16_t endy,uint16_t color)
// 函数功能描述:  部分区域清屏函数
// 参数描述:      u16 stx,u16 sty,u16 endx,u16 endy: 矩形区域启点终点坐标; u16 color: 填充颜色
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     ZHAOWL
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/
void  Lcd_Clear_Some_Area(uint16_t stx,uint16_t sty,uint16_t endx,uint16_t endy,uint16_t color)
{
    uint16_t  i, m, dx, dy;
    
    
    if(stx < endx) { dx = endx - stx;   }
    else           { dx = stx  - endx;  }

    if(sty < endy) { dy = endy - sty;   }
    else           { dy = sty  - endy;  }
    
    Lcd_Set_Region(stx,sty,endx-1,endy-1);
    for(i=0; i<dx; i++)
    {
        for(m=0; m<dy; m++)
        {   
            *(__IO uint16_t *) (Bank1_LCD_D) = color;
        }  
    }   
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}
/*************************************************
// 函 数 名:      Lcd_Clear_Some_Area_sim(uint16_t stx,uint16_t sty,uint16_t length,uint16_t width,uint16_t color)
// 函数功能描述:  部分区域清屏函数
// 参数描述:      u16 stx,u16 sty,u16 endx,u16 endy: 矩形区域启点终点坐标; u16 color: 填充颜色
// 返 回 值:      无       
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     lf
// 日期：         2017-5-10
// 修 改 人：                     
// 修改日期：     201x-xx-xx
*************************************************/

void Lcd_Clear_Some_Area_sim(uint16_t stx,uint16_t sty,uint16_t length,uint16_t width,uint16_t color)
{
		Lcd_Clear_Some_Area(stx,sty,stx+length,sty+width,color);
}
