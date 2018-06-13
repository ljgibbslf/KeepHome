#ifndef __SCCB_H__
#define  __SCCB_H__

#include "common.h"

//////////////////////////////////////////////////////////////////////////////////
#define     SCCB_SCL_PIN                   GPIO_PIN_3
#define     SCCB_SCL_GPIOx                 GPIOD
#define     SCCB_SCL_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()

#define     SCCB_SDA_PIN                   GPIO_PIN_6
#define     SCCB_SDA_GPIOx                 GPIOD
#define     SCCB_SDA_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()


#define     SCCB_SCL_OUT(x)     if(x){ HAL_GPIO_WritePin(SCCB_SCL_GPIOx, SCCB_SCL_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(SCCB_SCL_GPIOx, SCCB_SCL_PIN, GPIO_PIN_RESET); }

#define     SCCB_SDA_OUT(x)     if(x){ HAL_GPIO_WritePin(SCCB_SDA_GPIOx, SCCB_SDA_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(SCCB_SDA_GPIOx, SCCB_SDA_PIN, GPIO_PIN_RESET); }

#define     SCCB_SDA_READ()       HAL_GPIO_ReadPin(SCCB_SDA_GPIOx,SCCB_SDA_PIN)    // ¶ÁSDA¿ÚÏß×´Ì¬ 
                                
#define     NOP()  __ASM("NOP")

#define     SCCB_ADDR          0x
#define     SCCB_READ 		   0x
//////////////////////////////////////////////////////////////////////////////////

void  SCCB_GPIO_Init(void);								
								
void  SCCB_Start(void);
void  SCCB_Stop(void);
void  SCCB_Ack(void);
void  SCCB_NoAck(void);

uint8_t  SCCB_Send_Byte(uint8_t dat);
uint8_t SCCB_Read_Byte();
uint8_t SCCB_WaitAck(void);


#endif