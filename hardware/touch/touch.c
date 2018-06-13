#include  "touch.h"
#include  "lcd_drive.h"
#include  <string.h>

//CTP_Stru    CTP_Dat;
// ������ FT6336оƬ����
void  FT6336_I2C_GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    FT6336_SCL_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin   = FT6336_SCL_PIN | FT6336_SDA_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(FT6336_SCL_GPIOx, &GPIO_InitStruct);
    
    I2C1_SCL_OUT(1);
    I2C1_SDA_OUT(1);
    
    I2C1_Stop();
}


void I2C1_Delay_us(uint16_t cnt)
{
    uint16_t i;
    for(i=0;i<cnt;i++);
	//Delay_us(cnt);
}
    
/************************************************
*	�� �� ��: I2C_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
**************************************************/ 
void I2C1_Start(void)  
{ 
    I2C1_SDA_OUT(1);
    I2C1_SCL_OUT(1);
    I2C1_Delay_us(40);
    I2C1_SDA_OUT(0);
    I2C1_Delay_us(40);
    I2C1_SCL_OUT(0); 
} 

/****************************************************
*	�� �� ��: I2C_Stop
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
****************************************************/
void I2C1_Stop(void)  
{ 
    I2C1_SDA_OUT(0);
    I2C1_SCL_OUT(0);
    I2C1_Delay_us(40);
    I2C1_SDA_OUT(1);
    I2C1_SCL_OUT(1);
    I2C1_Delay_us(40);
}

/************************************** 
*	�� �� ��: I2C_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: �� 
**************************************/
void I2C1_Ack(void) 
{ 
    I2C1_SCL_OUT(0);
    I2C1_SDA_OUT(0);
    I2C1_Delay_us(20);
    I2C1_SCL_OUT(1);
    I2C1_Delay_us(20);
    I2C1_SCL_OUT(0);
} 
/*
*************************************************
*	�� �� ��: I2C_NoAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*************************************************
*/
void I2C1_NoAck(void)
{
    I2C1_SCL_OUT(0);
    I2C1_SDA_OUT(1);
    I2C1_Delay_us(20);
    I2C1_SCL_OUT(1);
    I2C1_Delay_us(20);
    I2C1_SCL_OUT(0);    
}
/*************************************************************
*	�� �� ��: I2C_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*************************************************************/
uint8_t I2C1_WaitAck(void)
{ 
    __IO uint16_t t = 0;
    I2C1_SDA_OUT(1);  
    I2C1_Delay_us(10);
    I2C1_SCL_OUT(1);
    I2C1_Delay_us(10);
    
    while(I2C1_SDA_IN())
    {
        t++;
        if(t>30)
        {
            I2C1_Stop();
            return 1;
        }   
    }

    I2C1_SCL_OUT(0);
    return 0; 
}

void I2C1_Send_Byte(uint8_t dat)
{
    __IO uint8_t i;

    I2C1_SCL_OUT(0);

    for(i=0; i<8; i++)
    {   
        if(dat & 0x80) { I2C1_SDA_OUT(1); }
        else           { I2C1_SDA_OUT(0); }

        I2C1_Delay_us(20);
        I2C1_SCL_OUT(1);    
        I2C1_Delay_us(20);
        I2C1_SCL_OUT(0);
        I2C1_Delay_us(20);
        dat <<= 1;  
    }
}

/************************************************
*	�� �� ��: I2C_Read_Byte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*************************************************/
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t I2C1_Read_Byte(uint8_t ack)
{
    uint8_t  i,receive=0;
    
    I2C1_SDA_OUT(1);
    for(i=0;i<8;i++ )
    {
        I2C1_SCL_OUT(0); 
        I2C1_Delay_us(20);
        I2C1_SCL_OUT(1);
        receive<<=1;
        if(I2C1_SDA_IN()) { receive++; }  
        I2C1_Delay_us(20); 
    }    
    if (!ack) { I2C1_NoAck(); } //����nACK
    else      { I2C1_Ack();   } //����ACK   
    
    return receive;
}

/****************************************************************************************
    ������ FT6336оƬ����
***************************************************************************************/
uint8_t FT6206_Read_Reg(uint8_t *pbuf,uint32_t len)
{
    int8_t i=0;

    I2C1_Start();
    I2C1_Send_Byte(FT6206_ADDR);
    I2C1_WaitAck(); 
    
    I2C1_Send_Byte(0);
    I2C1_WaitAck(); 
    I2C1_Stop();
  
    I2C1_Start();
    I2C1_Send_Byte(FT6206_ADDR+1);
    I2C1_WaitAck(); 
    
    for(i=0;i<len;i++)
    {
        if(i==(len-1))  *(pbuf+i)=I2C1_Read_Byte(0);
        else            *(pbuf+i)=I2C1_Read_Byte(1);
    }   
    I2C1_Stop();
    
    return 0;
}



static  struTouch  ctplast={0,0,NO_TOUCH,X_NO_MOVING,Y_NO_MOVING,};
void  ReadCTP(struTouch *nowctp)
{
    uint8_t    ctpbuf[10];

    ctplast.ctpxy.ctp_x   = nowctp->ctpxy.ctp_x;
    ctplast.ctpxy.ctp_y   = nowctp->ctpxy.ctp_y;
    ctplast.ctpmainstatus = nowctp->ctpmainstatus;
    ctplast.dx            = nowctp->dx;
    ctplast.dy            = nowctp->dy;

    // ��ȡ���ڵ�����ֵ
    FT6206_Read_Reg(ctpbuf, 7);
    if ((ctpbuf[2]&0x0f) == 1)
    {
        //����������λ480*800
        nowctp->ctpxy.ctp_x   = (ctpbuf[3] & 0x0f);
        nowctp->ctpxy.ctp_x <<= 8;
        nowctp->ctpxy.ctp_x  += ctpbuf[4];
        if(nowctp->ctpxy.ctp_x < X_MAX_PIXEL ) { nowctp->ctpxy.ctp_x = X_MAX_PIXEL - nowctp->ctpxy.ctp_x - 1; } 
        else                                   { nowctp->ctpxy.ctp_x = 0; }

        nowctp->ctpxy.ctp_y   = (ctpbuf[5] & 0x0f);
        nowctp->ctpxy.ctp_y <<= 8;
        nowctp->ctpxy.ctp_y  += ctpbuf[6];
        if(nowctp->ctpxy.ctp_y < Y_MAX_PIXEL ) { nowctp->ctpxy.ctp_y = Y_MAX_PIXEL - nowctp->ctpxy.ctp_y - 1; }
        else                                   { nowctp->ctpxy.ctp_y = 0; }
    }
    else
    {
        nowctp->ctpxy.ctp_x = 0xFFF;
        nowctp->ctpxy.ctp_y = 0xFFF;
    }
    
    // ������һ�ε�״̬�����ڵ�����ֵ�ж����ڵ���Ҫ״̬
    if(ctplast.ctpmainstatus == NO_TOUCH)        // ��һ��û�д���
    {
        if( (nowctp->ctpxy.ctp_x == 0xFFF) && (nowctp->ctpxy.ctp_y == 0xFFF)) { nowctp->ctpmainstatus = NO_TOUCH;  }// ����Ҳû�д��� 
        else                                                                  { nowctp->ctpmainstatus = JUST_TOUCH;}// ���ڸմ���  
    }
    else if((ctplast.ctpmainstatus == JUST_TOUCH) || (ctplast.ctpmainstatus == TOUCHED))   // ��һ�θմ��� �� �Ѿ���������
    {
        if( (nowctp->ctpxy.ctp_x == 0xFFF) && (nowctp->ctpxy.ctp_y == 0xFFF)) { nowctp->ctpmainstatus = JUST_POP;}  // �յ��� 
        else                                                                  { nowctp->ctpmainstatus = TOUCHED; }  // �Ѿ����� 
    }
    else if(ctplast.ctpmainstatus == JUST_POP)
    {
        if( (nowctp->ctpxy.ctp_x == 0xFFF) && (nowctp->ctpxy.ctp_y == 0xFFF)) { nowctp->ctpmainstatus = NO_TOUCH;  }// û�а���  
        else                                                                  { nowctp->ctpmainstatus = JUST_TOUCH;}// 
    }
    
    // �����ڵ���Ҫ״̬���ڰ���ʱ�����ж��ƶ����
    if(nowctp->ctpmainstatus == TOUCHED)
    {
        nowctp->dx = (int16_t)nowctp->ctpxy.ctp_x - (int16_t)ctplast.ctpxy.ctp_x;
        if(nowctp->dx == 0)     { nowctp->xmove = X_NO_MOVING;  }
        else if(nowctp->dx > 0) { nowctp->xmove = RIGHT_MOVING; }
        else if(nowctp->dx < 0) { nowctp->xmove = LEFT_MOVING;  }
        
        nowctp->dy = (int16_t)nowctp->ctpxy.ctp_y - (int16_t)ctplast.ctpxy.ctp_y;
        if(nowctp->dy == 0)     { nowctp->ymove = Y_NO_MOVING;  }
        else if(nowctp->dy > 0) { nowctp->ymove = DOWN_MOVING;  }
        else if(nowctp->dy < 0) { nowctp->ymove = UP_MOVING;    }
    }
    else
    {
        nowctp->xmove = X_NO_MOVING;
        nowctp->ymove = Y_NO_MOVING;
        nowctp->dx = 0;
        nowctp->dy = 0;
    }
}



void  Get_Test_Val(struTouch  nowctp, uint16_t *val_x, uint16_t *val_y)
{
    int    tmp;

    if(nowctp.ctpmainstatus == TOUCHED)
    {    
        tmp  = (int)(*val_x);
        tmp += nowctp.dx;          // �����ƶ�����/�ƶ���ֵ/ ; �����ƶ�,��/�ƶ���ֵ/
        if(tmp < 0) tmp = 65535;
        if(tmp > 65535) tmp = 0;
        *val_x = (uint16_t)tmp;
        
        tmp  = (int)(*val_y);
        tmp -= nowctp.dy;          // �����ƶ�����/�ƶ���ֵ/ ; �����ƶ�,��/�ƶ���ֵ/
        if(tmp < 0) tmp = 65535;
        if(tmp > 65535) tmp = 0;
        *val_y = (uint16_t)tmp;
    }
}

void Touch_Test(struTouch  nowctp)
{
	if(nowctp.ctpmainstatus == JUST_POP)
    {    
        
    }
}

BOOL is_touch_area(struTouch  nowctp,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t margin)
{
	return nowctp.ctpmainstatus == TOUCHED 
		&& nowctp.ctpxy.ctp_x >= x - margin 
		&& nowctp.ctpxy.ctp_x <= x + w + margin 
		&& nowctp.ctpxy.ctp_y >= y - margin 
		&& nowctp.ctpxy.ctp_y <= y + h + margin;
}
