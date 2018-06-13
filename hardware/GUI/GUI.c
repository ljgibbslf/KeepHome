/*************************************************
// �ļ�˵��:      ���ļ�Ϊ������ͼ����ʾ����������
//                �������ڵײ������ļ�֮�ϣ��û�����������Ӧ��ͼ�ι���
//                ��������ĺ����ǻ��㺯���������Ľ����ڴ˺���֮�ϣ����������ֲ
// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/
#include  "gui.h"
#include  "lcd_drive.h"
#include  "w25q64.h" 
#include  <string.h>


/************************************************************************
// �� �� ��:      char  Get_HextoASC_Disp(char hexdig)
// ������������:  ��1��ʮ��������ת��Ϊ��ʮ�����Ƶķ�ʽ��ʾ����
// ��������:      char hexdig:ʮ����������,   
// �� �� ֵ:      char:       
// ����ֵ����:    ʮ����������
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     �����û���--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
************************************************************************/
uint8_t  Get_HextoASC(uint8_t hexdig)
{
    uint8_t   tmp;
    
    tmp  = hexdig;
    tmp &= 0x0f;    
    if(tmp == 0x0a)      {  tmp  = 'a';  }
    else if(tmp == 0x0b) {  tmp  = 'b';  }
    else if(tmp == 0x0c) {  tmp  = 'c';  }
    else if(tmp == 0x0d) {  tmp  = 'd';  }
    else if(tmp == 0x0e) {  tmp  = 'e';  }
    else if(tmp == 0x0f) {  tmp  = 'f';  }
    else                 {  tmp += 0x30; } 
    
    return  tmp;
}

/*************************************************
// �� �� ��:      Gui_Draw_aPixel(uint16_t x,uint16_t y,uint16_t color)
// ������������:  ��һ����. �˺���Ϊ���º����Ļ���, Ҳ���Թ�ΪӲ���ӿڲ�ĺ���
// ��������:      u16 x,u16 y: ����; u16 color: ��ɫ����
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
void Gui_Draw_aPixel(uint16_t x,uint16_t y,uint16_t color)
{
    Lcd_Set_XY(x,y);
    *(__IO uint16_t *) (Bank1_LCD_D) = color;
}  

/****************************************************************************
// �� �� ��:      Gui_Circle(u16 X0,u16 Y0,u16 R,u16 fc)
// ������������:  Bresenham�㷨 ��Բ
// ��������:      u16 X0,u16 Y0:��ɫ����; u16 R:�뾶; u16 fc:��ɫֵ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Circle(uint16_t X0,uint16_t Y0,uint16_t R,uint16_t fc) 
{ 
    int  x, y, d; 

    x = 0; 
    y = R; 
    d = 3-2*R;     // ���߳�ʼֵ
    while (x < y) 
    { 
        Gui_Draw_aPixel(X0+x,Y0+y,fc);     //        7 �Գƻ���8����
        Gui_Draw_aPixel(X0-x,Y0+y,fc);     //        6 
        Gui_Draw_aPixel(X0+x,Y0-y,fc);     //        2 
        Gui_Draw_aPixel(X0-x,Y0-y,fc);     //        3 
        Gui_Draw_aPixel(X0+y,Y0+x,fc);     //        8 
        Gui_Draw_aPixel(X0-y,Y0+x,fc);     //        5 
        Gui_Draw_aPixel(X0+y,Y0-x,fc);     //        1 
        Gui_Draw_aPixel(X0-y,Y0-x,fc);     //        4 

        if(d < 0) 
        {
            d = d + 4*x + 6; 
        }
        else 
        { 
            d = d + 4*(x-y) + 10; 
            y--; 
        } 
        x++; 
    } 
    
    if (x == y) 
    { 
        Gui_Draw_aPixel(X0+x,Y0+y,fc);     //  �Գƻ���8����
        Gui_Draw_aPixel(X0-x,Y0+y,fc); 
        Gui_Draw_aPixel(X0+x,Y0-y,fc); 
        Gui_Draw_aPixel(X0-x,Y0-y,fc); 
        Gui_Draw_aPixel(X0+y,Y0+x,fc); 
        Gui_Draw_aPixel(X0-y,Y0+x,fc); 
        Gui_Draw_aPixel(X0+y,Y0-x,fc); 
        Gui_Draw_aPixel(X0-y,Y0-x,fc); 
    } 
} 

/****************************************************************************
// �� �� ��:      Gui_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color) 
// ������������:  ���ߺ�����ʹ��Bresenham ��ֱ���㷨
//0=<k<1, p0=2*dy - dx; �� pk<0 ʱ ��һ��������Ϊ (xk + 1,yk), pk+1 = pk+2*dy; �� pk>=0 ʱ��һ��������Ϊ (xk + 1,yk + 1), pk+1= pk + 2*dy - 2��dx; 
//-1<k<0, p0=2*dy + dx; �� pk>0 ʱ ��һ��������Ϊ (xk + 1,yk), pk+1 = pk+2*dy; �� pk<=0 ʱ��һ��������Ϊ (xk + 1,yk - 1), pk+1= pk + 2*dy + 2��dx; 
// ��������:      u16 x0, u16 y0, u16 x1, u16 y1:����յ�����; u16 Color:��ɫֵ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color)   
{
    int  dx, dy, dx2, dy2, x_inc, y_inc, error, index, xx0, yy0;
                 
    xx0 = x0;
    yy0 = y0;   
    
    Lcd_Set_XY(x0,y0);
    dx = x1 - x0;        //����x����
    dy = y1 - y0;        //����y����

    if (dx >= 0)
    {
        x_inc = 1;
    }
    else
    {
        x_inc = -1;
        dx    = -dx;  
    } 
    
    if (dy >= 0)
    {
        y_inc = 1;
    } 
    else
    {
        y_inc = -1;
        dy    = -dy; 
    } 

    dx2 = dx << 1;
    dy2 = dy << 1;

    if(dx > dy) //x�������y���룬��ôÿ��x����ֻ��һ���㣬ÿ��y���������ɸ��� //���ߵĵ�������x���룬��x���������
    { 
        error = dy2 - dx; 
        for (index=0; index <= dx; index++)//Ҫ���ĵ������ᳬ��x����
        {
            Gui_Draw_aPixel(xx0,yy0,Color);  //����
            if(error >= 0)                 //�Ƿ���Ҫ����y����ֵ
            {
                error -= dx2;
                yy0   += y_inc;            //����y����ֵ
            } 
            error += dy2;                  // adjust the error term
            xx0   += x_inc;                //x����ֵÿ�λ���󶼵���1 // move to the next pixel
        }  
    } 
    else  //y�����x�ᣬ��ÿ��y����ֻ��һ���㣬x�����ɸ���  //��y��Ϊ��������
    { 
        error = dx2 - dy; // initialize error term
        for (index=0; index <= dy; index++)  // draw the line
        {   
            Gui_Draw_aPixel(xx0,yy0,Color);    // set the pixel
            if (error >= 0)                  // test if error overflowed
            {
                error -= dy2;
                xx0   += x_inc;              // move to next line
            }               
            error += dx2;     
            yy0   += y_inc;     
        } 
    }  
}


/****************************************************************************
// �� �� ��:      Gui_Draw_Rect(u16 x0, u16 y0, u16 x1, u16 y1, u16 linecolor) 
// ������������:  ������
// ��������:      (x0,y0) ���Ͻǵ������,  (x1,y1) ���½ǵ������; u16 linecolor: �߽���ɫ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t linecolor)
{
    Gui_Draw_Line(x0, y0, x1, y0, linecolor);
    Gui_Draw_Line(x0, y0, x0, y1, linecolor);
    Gui_Draw_Line(x0, y1, x1, y1, linecolor);
    Gui_Draw_Line(x1, y0, x1, y1, linecolor);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_Asc16_Hzk16(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д16��16����ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc16_Hzk16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
    uint32_t  i,j, ch1;
    uint8_t   str[HZK16_nByte+1], tmp;
    uint16_t  x0,y0;
    
    x0 = x;
    y0 = y;
   
    while(*string) 
    {   
        if((*string) < 0x80) 
        {
            ch1 = (uint32_t)(*string++);
            Read_aAsc16_Dot(ch1, str);
            Lcd_Set_Region(x0,y0,(x0+7),(y0+ASC16_nLINE-1));
            for(i=0;i<ASC16_nLINE;i++)
            {
                tmp = str[i];
                for(j=0;j<8;j++)
                {
                    if(tmp & 0x80)  {  *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
                    else            {  *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
                    tmp <<= 1; 
                }
            }
            x0 += 8;
        }
        else 
        {
            ch1 = (uint32_t)(*string++);
            ch1 <<= 8;
            ch1  |= *string++; 
            Read_aWord_Hzk16_Dot(ch1, str);
            Lcd_Set_Region(x0,y0,(x0+15),(y0+ASC16_nLINE-1));
            for(i=0;i<HZK16_nLINE;i++)
            {
                tmp = str[2*i];
                for(j=0;j<8;j++)
                {
                    if(tmp & 0x80)  {  *(__IO uint16_t *)(Bank1_LCD_D) = forcolor;  }
                    else            {  *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;   }
                    tmp <<= 1; 
                }
                tmp = str[2*i+1];
                for(j=0;j<8;j++)
                {
                    if(tmp & 0x80)  {  *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
                    else            {  *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
                    tmp <<= 1; 
                }   
            }   
            x0+=16;
        } 
    }
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_A_Asc16(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 chr) 
// ������������:  д8��16���һ��ASCII�ַ�
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 chr:�ַ� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void  Gui_Draw_A_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t chr)
{
    uint32_t  i,j;
    uint8_t   str[HZK16_nByte+1], tmp;
   
    Read_aAsc16_Dot(chr, str);
    Lcd_Set_Region(x,y,(x+7),(y+ASC16_nLINE-1));
    for(i=0;i<ASC16_nLINE;i++)
    {
        tmp = str[i];
        for(j=0;j<8;j++)
        {
            if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
            else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
            tmp <<= 1; 
        }
    }
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_Asc24_Hzk24(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д24��24�����Ӣ���ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc24_Hzk24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
	gui_draw_a_str( x,  y,  forcolor,  bkcolor, string);
	
//    uint32_t  i,j, ch1;
//    uint8_t   str[HZK24_nByte+1], tmp;
//    uint16_t  x0,y0;
//    
//    x0 = x;
//    y0 = y;
//   
//    while(*string) 
//    {   
//        if((*string) < 0x80) 
//        {
//            ch1 = (uint32_t)(*string);
//            string++;
//            Read_aAsc24_Dot(ch1, str);
//            Lcd_Set_Region(x0,y0,(x0+11),(y0+ASC24_nLINE-1));
//            for(i=0;i<ASC24_nLINE;i++)
//            {
//                tmp = str[2*i];
//                for(j=0;j<8;j++)
//                {
//                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
//                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
//                    tmp <<= 1; 
//                }
//                tmp = str[2*i+1];
//                for(j=0;j<4;j++)
//                {
//                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
//                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
//                    tmp <<= 1; 
//                }   
//            }
//            x0 += 12;
//        }
//        else 
//        {
//            ch1 = (uint32_t)(*string);
//            string++;
//            ch1 <<= 8;
//            ch1  |= *string;
//            string++;   
//            Read_aWord_Hzk24_Dot(ch1, str);
//            Lcd_Set_Region(x0,y0,(x0+23),(y0+HZK24_nLINE-1));
//            for(i=0;i<HZK24_nLINE;i++)
//            {
//                tmp = str[3*i];
//                for(j=0;j<8;j++)
//                {
//                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
//                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
//                    tmp <<= 1; 
//                }
//        
//                tmp = str[3*i+1];
//                for(j=0;j<8;j++)
//                {
//                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
//                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
//                    tmp <<= 1; 
//                }
//                tmp = str[3*i+2];
//                for(j=0;j<8;j++)
//                {
//                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
//                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
//                    tmp <<= 1; 
//                }   
//            }   
//            x0+=24;
//        } 
//    }
//    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}


/****************************************************************************
// �� �� ��:      Gui_Draw_Asc32_String(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д32��32���Ӣ���ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc32_String(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
    uint32_t  i,j, ch1;
    uint8_t   str[ASC32_nByte+1], tmp;
    uint16_t  x0,y0;
    
    x0 = x;
    y0 = y;
   
    while(*string) 
    {   
        if((*string) < 0x80) 
        {
            ch1 = (uint32_t)(*string);
            string++;
            Read_aAsc32_Dot(ch1, str);
            Lcd_Set_Region(x0,y0,(x0+15),(y0+ASC32_nLINE-1));
            for(i=0;i<ASC32_nLINE;i++)
            {
                tmp = str[2*i];
                for(j=0;j<8;j++)
                {
                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
                    tmp <<= 1; 
                }
                tmp = str[2*i+1];
                for(j=0;j<8;j++)
                {
                    if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
                    else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
                    tmp <<= 1; 
                }   
            }
            x0 += 16;
        }
    }
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}



//////////////////////////////////////////////////////////////////////////
// ��24��������ִ�С��ʮ������ʾ2���ֽڵ�������
void Gui_Draw_24_Dig_U16_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[6];
    
    dig[0] = (char)(  digital / 10000) + 0x30;         // ȡ����λ��
    dig[1] = (char)( (digital % 10000) / 1000) + 0x30; // ȡ��ǧλ��
    dig[2] = (char)( (digital % 1000 ) / 100 ) + 0x30; // ȡ����λ��
    dig[3] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[4] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[5] = 0;
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

// ��16��������ִ�С��ʮ������ʾ2���ֽڵ�������
void Gui_Draw_16_Dig_U16_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[6];
    
    dig[0] = (char)(  digital / 10000) + 0x30;         // ȡ����λ��
    dig[1] = (char)( (digital % 10000) / 1000) + 0x30; // ȡ��ǧλ��
    dig[2] = (char)( (digital % 1000 ) / 100 ) + 0x30; // ȡ����λ��
    dig[3] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[4] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[5] = 0;
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

// ��32��������ִ�С��ʮ������ʾ2���ֽڵ�������
void Gui_Draw_32_Dig_U16_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[6];
    
    dig[0] = (char)(  digital / 10000) + 0x30;         // ȡ����λ��
    dig[1] = (char)( (digital % 10000) / 1000) + 0x30; // ȡ��ǧλ��
    dig[2] = (char)( (digital % 1000 ) / 100 ) + 0x30; // ȡ����λ��
    dig[3] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[4] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[5] = 0;
    Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_24_Dig_U16_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[5];
    uint8_t  tmp8;
    
    tmp8   = (uint8_t)(digital >> 12);
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);
    
    tmp8   = (uint8_t)(digital >> 8);
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)(digital >> 4);
    tmp8  &= 0x0f;
    dig[2] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)digital;
    tmp8  &= 0x0f;
    dig[3] =  Get_HextoASC(tmp8);

    dig[4] = 0;

    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_16_Dig_U16_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[5];
    uint8_t  tmp8;
    
    tmp8   = (uint8_t)(digital >> 12);
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);
    
    tmp8   = (uint8_t)(digital >> 8);
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)(digital >> 4);
    tmp8  &= 0x0f;
    dig[2] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)digital;
    tmp8  &= 0x0f;
    dig[3] =  Get_HextoASC(tmp8);

    dig[4] = 0;

    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_32_Dig_U16_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital)
{
    uint8_t  dig[5];
    uint8_t  tmp8;
    
    tmp8   = (uint8_t)(digital >> 12);
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);
    
    tmp8   = (uint8_t)(digital >> 8);
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)(digital >> 4);
    tmp8  &= 0x0f;
    dig[2] =  Get_HextoASC(tmp8);

    tmp8   = (uint8_t)digital;
    tmp8  &= 0x0f;
    dig[3] =  Get_HextoASC(tmp8);

    dig[4] = 0;

    Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, dig);
}

//////////////////////////////////////////////////////////////////////////
// ��24��������ִ�С��ʮ������ʾ1���ֽڵ�������
void Gui_Draw_24_Dig_U8_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[4];
    
    dig[0] = (char)(  digital / 100) + 0x30;           // ȡ����λ��
    dig[1] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[2] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[3] = 0;
    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

// ��16��������ִ�С��ʮ������ʾ2���ֽڵ�������
void Gui_Draw_16_Dig_U8_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[4];
    
    dig[0] = (char)(  digital / 100) + 0x30;           // ȡ����λ��
    dig[1] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[2] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[3] = 0;
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

// ��32��������ִ�С��ʮ������ʾ2���ֽڵ�������
void Gui_Draw_32_Dig_U8_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[4];
    
    dig[0] = (char)(  digital / 100) + 0x30;           // ȡ����λ��
    dig[1] = (char)( (digital % 100  ) / 10  ) + 0x30; // ȡ��ʮλ��
    dig[2] = (char)(  digital % 10   )         + 0x30; // ȡ����λ��
    dig[3] = 0;
    Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_24_Dig_U8_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[3];
    uint8_t  tmp8;

    tmp8   = digital >> 4;
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);

    tmp8   = digital;
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    dig[2] = 0;

    Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_16_Dig_U8_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[3];
    uint8_t  tmp8;

    tmp8   = digital >> 4;
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);

    tmp8   = digital;
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    dig[2] = 0;
    
    Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, dig);
}

// ��24��������ִ�С��ʮ��������ʾ2���ֽڵ�������
void Gui_Draw_32_Dig_U8_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital)
{
    uint8_t  dig[3];
    uint8_t  tmp8;

    tmp8   = digital >> 4;
    tmp8  &= 0x0f;
    dig[0] =  Get_HextoASC(tmp8);

    tmp8   = digital;
    tmp8  &= 0x0f;
    dig[1] =  Get_HextoASC(tmp8);

    dig[2] = 0;

    Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, dig);
}
//temporary test func
void Gui_Draw_x_y_Pic()
{
//	uint32_t  i,j;

//    Lcd_Set_Region(100,100,100+95,100+95);
//    for(i=0;i<96;i++)
//    {
//        for(j=0;j<96;j++)
//        {
//			*(__IO uint16_t *)(Bank1_LCD_D) = pic_buffer[i * 96 + j];
//        }
//    }
//    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}
//----------------------------------------------
void Gui_Draw_Pic(struPic * pic,uint16_t x,uint16_t y,uint16_t bkcolor)
{
	uint32_t  i,j;
	uint16_t  temp;
	
	
    Lcd_Set_Region(x,y,x + pic->xSize - 1,y + pic->ySize - 1);
	
	
    for(i=0;i < pic->xSize;i++)
    {
		
        for(j=0;j < pic->ySize;j++)
        {
			
			temp = pic->ptrPic[i * pic->ySize + j];

			if((temp == 0xFFFF) && (pic->is_fill_white == TRUE))
				*(__IO uint16_t *)(Bank1_LCD_D) =  bkcolor;
			else
				*(__IO uint16_t *)(Bank1_LCD_D) =  temp;
        }
    }

    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);//4what?
}
//----------------------------------------------
void Gui_Draw_Pic_Ext(struPic * pic,uint16_t x,uint16_t y,uint16_t bkcolor)
{
	uint32_t  i,j;
	uint16_t  temp;
	uint32_t  addr,pix_num;
	
	addr = pic->start_sector * 4096;
	pix_num = pic->xSize * pic->ySize * 2;
	
    Lcd_Set_Region(x,y,x + pic->xSize - 1,y + pic->ySize - 1);
	
	uint8_t buf[1000];

	for(i=0;i < pic->xSize;i++)
    {
		W25Q64_Read(buf,addr + i * 2 * pic->ySize,pic->ySize * 2);
        for(j=0;j < pic->ySize;j++)
        {
			temp = buf[j * 2];
			temp = temp << 8 | buf[j * 2 + 1];
			
			if((temp == 0xFFFF) && (pic->is_fill_white == TRUE))
				*(__IO uint16_t *)(Bank1_LCD_D) =  bkcolor;
			else
				*(__IO uint16_t *)(Bank1_LCD_D) =  temp;
			
        }
		
    }
	
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);//4what?
}

/****************************************************************************
// �� �� ��:      Gui_Draw_A_Hz(u16 x, u16 y, u16 forcolor, u16 bkcolor,const u8 buffer) 
// ������������:  дHZ_X*HZ_Y���һ��hanzi�ַ�
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void  Gui_Draw_A_Hz(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,const uint8_t * buff)
{
    uint32_t  i,j;
    uint8_t   tmp;
	uint16_t bytes = (HZ_X * HZ_Y ) >> 3;
    
    Lcd_Set_Region(x,y,(HZ_X + x - 1),(y+ HZ_Y -1));
    for(i=0;i < bytes;i++)
    {
        tmp = *buff;
        for(j=0;j<8;j++)
        {
            if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
            else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
            tmp <<= 1; 
        }
		buff++;
    }
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}
/************************************************************************
//Func Name:	Gui_Draw_A_Icon(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t index )
//Func Info:	draw a icon from my zm 
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void  Gui_Draw_A_Icon(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t index )
{
    uint32_t  i,j;
    uint8_t   tmp;
	uint32_t bytes = (icon->x * icon->y ) >> 3;
    
    Lcd_Set_Region(x,y,(icon->x + x - 1),(y+ icon->y -1));
	
    for(i=index * bytes;i < (index + 1 ) * bytes;i++)
    {
        tmp = icon->buf[i];
        for(j=0;j<8;j++)
        {
            if(tmp & 0x80) { *(__IO uint16_t *)(Bank1_LCD_D) = forcolor; }
            else           { *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;  }
            tmp <<= 1; 
        }
    }
    Lcd_Set_Region(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
}
/************************************************************************
//Func Name:	void gui_draw_a_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index )
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_a_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index )
{
	Gui_Draw_A_Icon(x,y,forcolor,bkcolor,&icon_ascii,(index-0x21));
}
/************************************************************************
//Func Name:	void gui_draw_a_16_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index )
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_a_16_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index )
{
	Gui_Draw_A_Icon(x,y,forcolor,bkcolor,&icon_ascii_16_32,(index-0x21));
}
/************************************************************************
//Func Name:	void gui_draw_a_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str)
//Func Info:	draw a string with my own ascii zm
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_a_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str)
{
	uint8_t count = 0;
	while(* str != '\0')
	{
		if(* str != ' ')
		{
			gui_draw_a_Ascii(x + count * icon_ascii.x,y,forcolor,bkcolor,(uint8_t)*str);
		}
		count++;
		str++;
	}
}
/************************************************************************
//Func Name:	void gui_draw_a_16_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str)
//Func Info:	draw a string with my own ascii zm
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_a_16_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str)
{
	uint8_t count = 0;
	while(* str != '\0')
	{
		if(* str != ' ')
		{
			gui_draw_a_16_Ascii(x + count * icon_ascii_16_32.x,y,forcolor,bkcolor,(uint8_t)*str);
		}
		count++;
		str++;
	}
}
//make a wheel to print a u8
void Gui_Draw_My_Num(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint16_t dig,BOOL is_dot)
{
	//clear area first
	Lcd_Clear_Some_Area_sim(x,y,icon_num.x*4,icon_num.y,bkcolor);
	if((dig / 100) != 0)
		Gui_Draw_A_Icon(x,y,forcolor,bkcolor,&icon_num,dig / 100);
	if(((dig % 100) / 10) != 0 || (dig / 100) != 0)
		Gui_Draw_A_Icon(x + icon_num.x * 1,y,forcolor,bkcolor,&icon_num,(dig % 100) / 10);
	if(is_dot)
	{
		//Gui_Draw_Asc32_String(x + icon_num.x * 2,y,forcolor,bkcolor,".");
		Gui_Draw_A_Icon(x + icon_num.x * 2,y,forcolor,bkcolor,&icon_num,10);
		Gui_Draw_A_Icon(x + icon_num.x * 3,y,forcolor,bkcolor,&icon_num,(dig % 10));
	}
	else
		Gui_Draw_A_Icon(x + icon_num.x * 2,y,forcolor,bkcolor,&icon_num,(dig % 10));
}

/************************************************************************
//Func Name:	gui_draw_slogan(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon)
//Func Info:	print about info on screen
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_slogan(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor)
{
	//XXXXXXX
	//	 XXXXXXX
	uint8_t x_clr = 10;
	uint8_t y_clr = y + 10;
	uint8_t x1_num = 7;//num of XXX in row 1
	uint8_t i;
	for(i=0;i<=x1_num;i++)
	{
		Gui_Draw_A_Icon(x + x_clr * i,y,forcolor,bkcolor,&icon_slogan,i);
	}
	for(i=x1_num + 1;i < icon_slogan.icon_num;i++)
	{
		Gui_Draw_A_Icon(x + x_clr * ( i - x1_num + 3),y + y_clr,forcolor,bkcolor,&icon_slogan,i);
	}
}

/************************************************************************
//Func Name:	void gui_draw_about(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon)
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_about(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor)
{
	//XXXXXXXXXXXXXXX
	uint8_t x_clr = 10;
	uint8_t i;
	for(i = 0;i < icon_about.icon_num;i++)
	{
		Gui_Draw_A_Icon(x + icon_about.x * i,y,forcolor,bkcolor,&icon_about,i);
	}
}

/************************************************************************
//Func Name:	
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
void gui_draw_a_title_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t first_index,uint8_t count)
{
	uint8_t i =0;
	while(count-- != 0)
	{
		Gui_Draw_A_Icon(x + icon_title.x * i,y,forcolor,bkcolor,&icon_title,first_index+i);
		i++;
	}
}

/************************************************************************
//Func Name:	gui_draw_a_icon_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t first_index,uint8_t last_index)
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/

void  gui_draw_a_icon_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t first_index,uint8_t last_index)
{
	uint8_t i =0;
	uint8_t num = last_index - first_index + 1;
	while(num-- != 0)
	{
		Gui_Draw_A_Icon(x + icon_title.x * i,y,forcolor,bkcolor,icon,first_index+i);
		i++;
	}
}

/************************************************************************
//Func Name:	void rgb8882565(uint32_t color)
//Func Info:
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
uint16_t rgb8882565(uint32_t color)
{
	uint8_t red = (color >> 19) & 0x1f;
	uint8_t green = (color >> 10) & 0x3f;
	uint8_t blue = (color >> 3) & 0x1f;
	return (((((color) >> 19) & 0x1f) << 11) |((((color) >> 10& 0x3f) << 5)|(((color) >> 3) & 0x1f)));
}
