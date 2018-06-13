#ifndef __TOUCH_H__
#define __TOUCH_H__ 
////////////////////////////////////////////////////////////////////////////////// 
#include "stm32f4xx_hal.h"
#include "GUI.h"
// ������ FT6336оƬ����
//////////////////////////////////////////////////////////////////////////////////
#define     FT6336_SCL_PIN                   GPIO_PIN_0
#define     FT6336_SCL_GPIOx                 GPIOB
#define     FT6336_SCL_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define     FT6336_SDA_PIN                   GPIO_PIN_1
#define     FT6336_SDA_GPIOx                 GPIOB
#define     FT6336_SDA_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()


#define     I2C1_SCL_OUT(x)     if(x){ HAL_GPIO_WritePin(FT6336_SCL_GPIOx, FT6336_SCL_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(FT6336_SCL_GPIOx, FT6336_SCL_PIN, GPIO_PIN_RESET); }

#define     I2C1_SDA_OUT(x)     if(x){ HAL_GPIO_WritePin(FT6336_SDA_GPIOx, FT6336_SDA_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(FT6336_SDA_GPIOx, FT6336_SDA_PIN, GPIO_PIN_RESET); }

#define     I2C1_SDA_IN()       HAL_GPIO_ReadPin(FT6336_SDA_GPIOx,FT6336_SDA_PIN)    // ��SDA����״̬ 
                                
#define     NOP()  __ASM("NOP")

#define     FT6206_ADDR         0x70
//////////////////////////////////////////////////////////////////////////////////
//#define     DXY_MAX             1
//#define     DXY_MIN            (-DXY_MAX)
                                
                                
typedef  enum{
    NO_TOUCH   = 0,    // ������û�а���
    JUST_TOUCH    ,    // �������հ���
    TOUCHED       ,    // �������Ѿ���������
    JUST_POP      ,    // �������յ���
}TouchMainStatus;

typedef  enum{  
    Y_NO_MOVING=0 ,
    UP_MOVING     ,   // �������Ѿ����£����������ƶ�
    DOWN_MOVING   ,   // �������Ѿ����£����������ƶ�
}YSubStatus;

typedef  enum{ 
    X_NO_MOVING=0 ,
    LEFT_MOVING   ,   // �������Ѿ����£����������ƶ�
    RIGHT_MOVING  ,   // �������Ѿ����£����������ƶ�
}XSubStatus;

typedef struct 
{
    uint16_t ctp_x;                  // ��������X����ֵ
    uint16_t ctp_y;                  // ��������Y����ֵ
}struCTPxy;

typedef  struct
{
    struCTPxy       ctpxy;           // ������������XY
    TouchMainStatus ctpmainstatus;   // ����������Ҫ״̬
    XSubStatus      xmove;           // X������ƶ�״̬
    YSubStatus      ymove;           // Y������ƶ�״̬
    int16_t         dx;              // X�����ƶ������� +ֵ:��ʾ�����ƶ�; -ֵ:��ʾ�����ƶ�
    int16_t         dy;              // Y�����ƶ������� +ֵ:��ʾ�����ƶ�; -ֵ:��ʾ�����ƶ�
}struTouch;
//////////////////////////////////////////////////////////////////////////////////

void  I2C1_Start(void);
void  I2C1_Stop(void);
void  I2C1_Ack(void);
void  I2C1_NoAck(void);

void  I2C1_Send_Byte(uint8_t dat);
uint8_t I2C1_Read_Byte(uint8_t ack);
uint8_t I2C1_WaitAck(void);

void  I2C1_Delay_us(uint16_t cnt);

void  FT6336_I2C_GPIO_init(void);
void  ReadCTP(struTouch *);
void  Get_Test_Val(struTouch, uint16_t *, uint16_t *);
void  Touch_Test(struTouch);
BOOL is_touch_area(struTouch  nowctp,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t margin);
#endif

