/*************************************************
// �ļ�˵��:      ���ļ�Ϊ�ײ�Ӳ���ӿڼ���Ӧ����ĳ�ʼ��
//                һ���·ͼ����ʾ��ѡ��������������ݾͶ��ˣ�����Ҫ�޸�
// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/

#include  "lcd_drive.h"

/**********************************************
Lcd�������ų�ʼ��
***********************************************/
void  LCD_CTRL_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    // LCD�ĸ�λ���ų�ʼ��
    LCD_RST_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin  = LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LCD_RST_GPIOx, &GPIO_InitStruct);
    LCD_RST_OFF();
    
    // LCD�ı������ų�ʼ��
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
Lcd���Ÿ�λ
***********************************************/
static void LCD_Rst(void)
{   
    LCD_RST_ON();  
    LCD_delay(10); 
    LCD_RST_OFF(); 
    LCD_delay(2);  
}

/**********************************************
Lcdд����
***********************************************/
 void WriteComm(uint16_t lcd_cmd)
{   
    *(__IO uint16_t *) (Bank1_LCD_C) = lcd_cmd;
}
/**********************************************
Lcdд����
***********************************************/
 void WriteData(uint16_t lcd_data)
{   
    *(__IO uint16_t *) (Bank1_LCD_D) = lcd_data;
}


/**********************************************
Lcd��ʼ���������������ų�ʼ��, Ӳ����λ, �����ʼ��������
***********************************************/
void LCD_init(void)
{   
    LCD_CTRL_GPIO_Init();     // ��λ���źͱ������ŵĳ�ʼ��
    LCD_Rst();                // ��λ���Ų�����λ�ź�
    
    //************* Start Initial Sequence **********//
    WriteComm(0xFF); // EXTC Command Set enable register ��չ����ʹ��
    WriteData(0xFF); 
    WriteData(0x98); 
    WriteData(0x06); // ʹ��EXTC Command; !=06ʱ �ر� "EXTC Command" 

    WriteComm(0xBC); // GIP 1: �ֲ���û����ʾʲô���ܣ�����һ��Ҫ, ����ȱʧ��ָ��
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

    WriteComm(0xBD); // GIP 2: �ֲ���û����ʾʲô���ܣ�����һ��Ҫ, ����ȱʧ��ָ�� 
    WriteData(0x01); 
    WriteData(0x23); 
    WriteData(0x45); 
    WriteData(0x67); 
    WriteData(0x01); 
    WriteData(0x23); 
    WriteData(0x45); 
    WriteData(0x67); 

    WriteComm(0xBE); // GIP 3: �ֲ���û����ʾʲô���ܣ�����һ��Ҫ, ����ȱʧ��ָ�� 
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
    WriteData(0x0F);  // ʹ�� VGMP/VGMN/VGSP/VGSN

    WriteComm(0xC0); // Power Control 1
    WriteData(0xC7); // C:AVDD=+5V  7:AVEE=-5V    //WriteData(0xE3);
    WriteData(0x0B); // �̶�
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
	
	
     
	
    WriteComm(0xF7); // �ֱ���
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

    WriteComm(0x36); // �Դ�ӿڿ��ƣ����ƺ��� ���� ����
    #ifdef USE_HORIZONTAL//��������˺��� 
        WriteData(0xA0); // ����
    #else
        WriteData(0x00); // ����
    #endif
    
    WriteComm(0x3A); // 
    WriteData(0x55); // RGB�ӿڸ�ʽ16bit/pixel  MCU�ӿڸ�ʽ16bit/pixel
	
	//WriteComm(0xB9); // horizontal flip 
    //WriteData(0x00); 
    //WriteData(0x02); 
	
    WriteComm(0x11); // Exit Sleep 
    LCD_delay(120); 
    WriteComm(0x29); // Display On 
    LCD_delay(10);
    LCD_BKLED_ON();  // ����ƿ�

    Lcd_Clear_All(BK_COLOR);
	//BLUE_2_4
}
/******************************************
��������Lcdд�����
���ܣ���Lcdָ��λ��д��Ӧ�����������
��ڲ�����Index ҪѰַ�ļĴ�����ַ
          ConfigTemp д������ݻ�����ֵ
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
// �� �� ��:      GetPoint( uint16_t x, uint16_t y)
// ������������:  ��ȡX,Y���������ɫֵ
// ��������:      uint16_t x, uint16_t y: ���� 
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ������ܲ�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
��������Lcd��ѡ����
���ܣ�ѡ��Lcd��ָ���ľ�������

ע�⣺xStart�� yStart������Ļ����ת���ı䣬λ���Ǿ��ο���ĸ���

��ڲ�����xStart x�������ʼ��
          ySrart y�������ֹ��
          xLong  Ҫѡ�����ε�x���򳤶�
          yLong  Ҫѡ�����ε�y���򳤶�
����ֵ����
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
��������Lcdͼ�����100*100
���ܣ���Lcdָ��λ�����ͼ��
��ڲ�����Index ҪѰַ�ļĴ�����ַ
          ConfigTemp д������ݻ�����ֵ
******************************************/
//void LCD_Fill_Pic(uint16_t x, uint16_t y, uint16_t pic_H, uint16_t pic_V, const unsigned char* pic)
//{
//    uint32_t  i;
//    uint16_t  j;

////  WriteComm(0x3600);  //Set_address_mode
////  WriteData(0x00);    //�����������½ǿ�ʼ�������ң����µ���
//    BlockWrite(x, x+pic_H-1, y, y+pic_V-1);
//    for (i = 0; i < pic_H*pic_V*2; i+=2)
//    {
//        j=pic[i];
//        j=j<<8;
//        j=j+pic[i+1];
//        *(__IO uint16_t *) (Bank1_LCD_D) = j;
//    }
//}

//��ָ�������ϴ�һ����
//void DrawPixel(uint16_t x, uint16_t y, uint16_t Color)
//{
//    BlockWrite(x, x, y, y);
//    *(__IO uint16_t *) (Bank1_LCD_D) = Color;
//}


/*************************************************
// �� �� ��:      Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
// ������������:  ����lcd��ʾ��ʼ��
// ��������:      u16 Xpos, u16 Ypos: ���� 
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ������ܲ�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      Lcd_SetRegion(uint16_t xStart, uint16_t yStart,uint16_t xEnd,uint16_t yEnd)
// ������������:  ����lcd��ʾ�����ڴ�����д�������Զ�����
// ��������:      u16 xStar, u16 yStar,u16 xEnd,u16 yEnd: ����յ����� 
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ������ܲ�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      Lcd_Clear(u16 color)
// ������������:  ȫ����������
// ��������:      u16 color: �����ɫ
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      Lcd_Clear_Some_Area(uint16_t stx,uint16_t sty,uint16_t endx,uint16_t endy,uint16_t color)
// ������������:  ����������������
// ��������:      u16 stx,u16 sty,u16 endx,u16 endy: �������������յ�����; u16 color: �����ɫ
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      Lcd_Clear_Some_Area_sim(uint16_t stx,uint16_t sty,uint16_t length,uint16_t width,uint16_t color)
// ������������:  ����������������
// ��������:      u16 stx,u16 sty,u16 endx,u16 endy: �������������յ�����; u16 color: �����ɫ
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     lf
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/

void Lcd_Clear_Some_Area_sim(uint16_t stx,uint16_t sty,uint16_t length,uint16_t width,uint16_t color)
{
		Lcd_Clear_Some_Area(stx,sty,stx+length,sty+width,color);
}
