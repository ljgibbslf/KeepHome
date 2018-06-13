#ifndef __TOUCH_H__
#define __TOUCH_H__ 
////////////////////////////////////////////////////////////////////////////////// 
#include "stm32f4xx_hal.h"
#include "GUI.h"
// 电容屏 FT6336芯片驱动
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

#define     I2C1_SDA_IN()       HAL_GPIO_ReadPin(FT6336_SDA_GPIOx,FT6336_SDA_PIN)    // 读SDA口线状态 
                                
#define     NOP()  __ASM("NOP")

#define     FT6206_ADDR         0x70
//////////////////////////////////////////////////////////////////////////////////
//#define     DXY_MAX             1
//#define     DXY_MIN            (-DXY_MAX)
                                
                                
typedef  enum{
    NO_TOUCH   = 0,    // 触摸屏没有按下
    JUST_TOUCH    ,    // 触摸屏刚按下
    TOUCHED       ,    // 触摸屏已经触摸到了
    JUST_POP      ,    // 触摸屏刚弹出
}TouchMainStatus;

typedef  enum{  
    Y_NO_MOVING=0 ,
    UP_MOVING     ,   // 触摸屏已经按下，并且向上移动
    DOWN_MOVING   ,   // 触摸屏已经按下，并且向下移动
}YSubStatus;

typedef  enum{ 
    X_NO_MOVING=0 ,
    LEFT_MOVING   ,   // 触摸屏已经按下，并且向左移动
    RIGHT_MOVING  ,   // 触摸屏已经按下，并且向右移动
}XSubStatus;

typedef struct 
{
    uint16_t ctp_x;                  // 触摸屏的X坐标值
    uint16_t ctp_y;                  // 触摸屏的Y坐标值
}struCTPxy;

typedef  struct
{
    struCTPxy       ctpxy;           // 触摸屏的坐标XY
    TouchMainStatus ctpmainstatus;   // 触摸屏的主要状态
    XSubStatus      xmove;           // X方向的移动状态
    YSubStatus      ymove;           // Y方向的移动状态
    int16_t         dx;              // X方向移动的像素 +值:表示向右移动; -值:表示向左移动
    int16_t         dy;              // Y方向移动的像素 +值:表示向下移动; -值:表示向上移动
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

